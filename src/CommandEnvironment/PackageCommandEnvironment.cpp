/*
 * PackageCommandEnvironment.cpp
 *
 *  Created on: 12 juin 2020
 *      Author: ebeuque
 */

#include "Global/QApplicationSettings.h"

#include "Version/VersionHelper.h"

#include "Environment/EnvironmentDefs.h"

#include "Formulas/FormulaParser.h"

#include "PackageCommandEnvironment.h"

PackageCommandEnvironment::PackageCommandEnvironment()
{
	setNeedEnvVars(true);
	m_szPkgConfigMode = "";
}

PackageCommandEnvironment::~PackageCommandEnvironment()
{

}

void PackageCommandEnvironment::setPackageName(const QString& szPackageName)
{
	m_szPackageName = szPackageName;
}

const QString& PackageCommandEnvironment::getPackageName() const
{
	return m_szPackageName;
}

void PackageCommandEnvironment::setPackageVersion(const QString& szVersion)
{
	m_szPackageVersion = szVersion;
}

const QString& PackageCommandEnvironment::getPackageVersion() const
{
	return m_szPackageVersion;
}

QString PackageCommandEnvironment::getPackageNameVersion() const
{
	return getPackageNameVersion(m_szPackageName, m_szPackageVersion);
}

QString PackageCommandEnvironment::getPackageNameVersion(const QString& szPackageName, const QString& szPackageVersion)
{
	QString szVersionName = szPackageName;
	if(!szPackageVersion.isEmpty()){
		szVersionName += "-" + szPackageVersion;
	}
	return szVersionName;
}

void PackageCommandEnvironment::addPackageOption(const QString& szOption)
{
	m_listPackageOptions.append(szOption);
}

const QStringList& PackageCommandEnvironment::getPackageOptions() const
{
	return m_listPackageOptions;
}

const QSharedPointer<Formula>& PackageCommandEnvironment::getFormula() const
{
	return m_pFormula;
}

QDir PackageCommandEnvironment::getRootPackageDir(const QString& szPackageName, const QString& szVersion) const
{
	const Environment& env = getEnv();
	return env.getVirtualEnvironmentPath().filePath(getPackageNameVersion(szPackageName, szVersion));
}

QDir PackageCommandEnvironment::getSourcePackageDir(const QString& szPackageName, const QString& szVersion) const
{
	const Environment& env = getEnv();
	if(env.isPerPackageMode()){
		return getRootPackageDir(szPackageName, szVersion).filePath("src");
	}else{
		return env.getVirtualEnvironmentReleaseDir().filePath(getPackageNameVersion(szPackageName, szVersion));
	}
}

QDir PackageCommandEnvironment::getBuildPackageDir(const QString& szPackageName, const QString& szVersion) const
{
	const Environment& env = getEnv();
	if(env.isPerPackageMode()){
		return getRootPackageDir(szPackageName, szVersion).filePath("build");
	}else{
		return env.getVirtualEnvironmentReleaseDir().filePath(getPackageNameVersion(szPackageName, szVersion));
	}
}

QDir PackageCommandEnvironment::getReleasePackageDir(const QString& szPackageName, const QString& szVersion) const
{
	const Environment& env = getEnv();
	if(env.isPerPackageMode()){
		return getRootPackageDir(szPackageName, szVersion).filePath("release");
	}else{
		return env.getVirtualEnvironmentReleaseDir().filePath(getPackageNameVersion(szPackageName, szVersion));
	}
}

bool PackageCommandEnvironment::doProcessArgument(int i, const QString& szArg)
{
	if(i == 0){
		setPackageName(szArg);
		return true;
	}

	if(szArg.startsWith("--pkg-version=")){
		setPackageVersion(szArg.mid(14));
		return true;
	}

	if(szArg.startsWith("--pkg-option=")){
		addPackageOption(szArg.mid(13));
		return true;
	}

	if(szArg.startsWith("--pkg-config-mode=")){
		m_szPkgConfigMode = szArg.mid(18);
		return true;
	}

	return AbstractCommandEnvironment::doProcessArgument(i, szArg);
}

bool PackageCommandEnvironment::doFinalizeEnv(Environment& env)
{
	// Handle pkg-config mode
	if(!m_szPkgConfigMode.isEmpty())
	{
		QDir pathPkgConfig = getVirtualEnvironmentPath().filePath(".pkgconfig-files");
		if(pathPkgConfig.exists()){
			if (m_szPkgConfigMode == "default") {
				env.removeEnvVar(VE_VAR_PKG_CONFIG_PATH);
				env.removeEnvVar(VE_VAR_PKG_CONFIG_LIBDIR);
				env.setEnvVar(VE_VAR_PKG_CONFIG_PATH, pathPkgConfig.absolutePath());
			} else if (m_szPkgConfigMode == "environment") {
				env.removeEnvVar(VE_VAR_PKG_CONFIG_PATH);
				env.removeEnvVar(VE_VAR_PKG_CONFIG_LIBDIR);
				env.setEnvVar(VE_VAR_PKG_CONFIG_LIBDIR, pathPkgConfig.absolutePath());
			}else if(m_szPkgConfigMode == "system"){
				env.removeEnvVar(VE_VAR_PKG_CONFIG_PATH);
				env.removeEnvVar(VE_VAR_PKG_CONFIG_LIBDIR);
			}
		}
	}
	return true;
}

bool PackageCommandEnvironment::doLoad() {
    bool bRes = true;

    // Setup version
    if (getPackageVersion().isEmpty()) {
        qDebug("[load-env] Auto detect version");
        QList<QString> listVersions;
        bRes = findPackageVersions(m_szPackageName, FindSource, listVersions);
        if(listVersions.isEmpty()){
            qCritical("[load-env] No version found for package %s", qPrintable(m_szPackageName));
            bRes = false;
        }else{
            if(listVersions.count() > 1){
                qWarning("[load-env] Multiple version found for package %s. Please use one of the following options", qPrintable(m_szPackageName));
                QList<QString>::const_iterator iter;
                for(iter = listVersions.constBegin(); iter != listVersions.constEnd(); ++iter){
                    qWarning("[load-env]   --pkg-version=%s", qPrintable(*iter));
                }
                bRes = false;
            }else{
                QString szVersion = listVersions.first();
                setPackageVersion(szVersion);
                qDebug("[load-env] Auto-selecting version %s for package %s", qPrintable(szVersion), qPrintable(m_szPackageName));
            }
        }
    }

    // Load formula
    if (bRes) {
        bRes = loadFormula(m_szPackageName, m_pFormula);
    }

	if(bRes){
		bRes = checkDependencies(m_pFormula);
	}

	return bRes;
}

bool PackageCommandEnvironment::loadFormula(const QString& szPackageName, QSharedPointer<Formula>& pFormula)
{
    bool bRes = false;

    QDir dir = getFormulasDir().filePath(szPackageName);
    QString szFileName = QString("%0.json").arg(szPackageName);
    QString szFilePath = dir.filePath(szFileName);

    if (dir.exists(szFileName)) {
        qDebug("[load-env] Loading formula from file %s", qPrintable(szFilePath));

        FormulaParser parser(getEnv().getPlatformTypeName());
        parser.setPackageVersion(getPackageVersion());
        bRes = parser.parse(szFilePath);
        if (bRes) {
            pFormula = parser.getFormula();
        }
    }else {
        qCritical("[load-env] Cannot find formula file %s", qPrintable(szFilePath));
    }

	return bRes;
}

bool PackageCommandEnvironment::checkDependencies(const QSharedPointer<Formula>& pFormula)
{
	bool bRes = true;

	qDebug("[load-env] checking dependencies");

	QString szVersion = getPackageNameVersion();
	const QStringList& listOptions = getPackageOptions();
	FormulaDependenciesList listDependencies = pFormula->getDependenciesListForOptions(listOptions);

	QString szDepsVersion = listDependencies.getBestDependenciesVersion(szVersion);

	if(!szDepsVersion.isEmpty()){
		qDebug("[load-env] using dependencies rules for version '%s'", qPrintable(szDepsVersion));

		const FormulaDependencies& deps = listDependencies.value(szDepsVersion);

		const PackageDependencyList& depsList = deps.getList();
		PackageDependencyList::const_iterator iter;

		for(iter = depsList.constBegin(); iter != depsList.constEnd(); ++iter)
		{
			const PackageDependency& dependency = (*iter);
			qWarning("[load-env] checking dependency %s", qPrintable(dependency.toString()));

			QDir dirFoundPath;
			QString szFoundVersion;
			bRes = checkDependencyPresent(dependency, dirFoundPath, szFoundVersion);
			if(bRes){
				qDebug("[load-env] required dependency is found %s", qPrintable(szFoundVersion));
				QString szBaseVar = "DEPENDENCY::" + dependency.getPackage().toUpper() + "::";
				addVariable(szBaseVar + "ROOTPATH", dirFoundPath.absolutePath());
				addVariable(szBaseVar + "VERSION", szFoundVersion);
			}else{
				qWarning("[load-env] required dependency is not found");
			}

			if(!bRes){
				break;
			}
		}
	}

	return bRes;
}

bool PackageCommandEnvironment::checkDependencyPresent(const PackageDependency& dependency, QDir& pathOut, QString& szOutVersion)
{
    bool bRes = false;

    QString szDependencyPackage = dependency.getPackage();

    QList<QString> listVersions;
    bRes = findPackageVersions(szDependencyPackage, FindRelease, listVersions);
    if(bRes) {
        bRes = false;
        QList<QString>::const_iterator iter;
        for (iter = listVersions.constBegin(); iter != listVersions.constEnd(); ++iter) {
            const QString &szVersion = (*iter);
            if (VersionHelper::checkVersion(szVersion, dependency.getVersionMin(), dependency.getVersionMax())) {
                bRes = true;
                pathOut = getReleasePackageDir(dependency.getPackage(), szVersion);
                szOutVersion = szVersion;
            }
        }
    }

    return bRes;
}

bool PackageCommandEnvironment::findPackageVersions(const QString& szPackageName, FindMode iMode, QList<QString>& listVersions)
{
    bool bRes = true;

    QDir dirSearchPackage;

    Environment& env = getEnv();
    if(env.isPerPackageMode()){
        dirSearchPackage = env.getVirtualEnvironmentPath();
    }else{
        if(iMode == FindSource){
            dirSearchPackage = env.getVirtualEnvironmentSourceDir();
        }else{
            dirSearchPackage = env.getVirtualEnvironmentReleaseDir();
        }
    }

    QStringList listFilters;
    listFilters << QString("%0*").arg(szPackageName);
    QFileInfoList listFiles = dirSearchPackage.entryInfoList(listFilters, QDir::Dirs, QDir::Name);

    QFileInfoList::const_iterator iter;
    for(iter = listFiles.constBegin(); iter != listFiles.constEnd(); ++iter) {
        const QFileInfo &fileInfo = (*iter);
        QString szVersion = fileInfo.fileName().remove(szPackageName + "-");
        listVersions.append(szVersion);
    }

    return bRes;
}
