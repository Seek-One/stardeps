/*
 * PackageCommandEnvironment.cpp
 *
 *  Created on: 12 juin 2020
 *      Author: ebeuque
 */

#include "Global/QApplicationSettings.h"

#include "Version/VersionHelper.h"

#include "Formulas/FormulaParser.h"

#include "PackageCommandEnvironment.h"

PackageCommandEnvironment::PackageCommandEnvironment()
{
	setNeedEnvVars(true);
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
	QString szVersionName = m_szPackageName;
	if(!m_szPackageVersion.isEmpty()){
		szVersionName += "-" + m_szPackageVersion;
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

bool PackageCommandEnvironment::doProcessArgument(int i, const QString& szArg)
{
	if(i == 0){
		setPackageName(szArg);
		return true;
	}

	if(szArg.startsWith("--version=")){
		setPackageVersion(szArg.mid(10));
		return true;
	}

	if(szArg.startsWith("--option=")){
		addPackageOption(szArg.mid(9));
		return true;
	}

	return AbstractCommandEnvironment::doProcessArgument(i, szArg);
}

bool PackageCommandEnvironment::doLoad()
{
	bool bRes;

	// Load formula
	bRes = loadFormula(m_szPackageName, m_pFormula);

	if(bRes){
		bRes = checkDependencies(m_pFormula);
	}

	return bRes;
}

bool PackageCommandEnvironment::loadFormula(const QString& szPackageName, QSharedPointer<Formula>& pFormula)
{
	bool bRes;

	QDir dir = QApplicationSettings::applicationFormulasPath().filePath(szPackageName);
	QString szFilePath = dir.filePath(QString("%0.json").arg(szPackageName));
	qDebug("[load-env] Loading formula from file %s", qPrintable(szFilePath));

	FormulaParser parser;
	bRes = parser.parse(szFilePath);
	if(bRes){
		pFormula = parser.getFormula();
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

			QString szFoundVersion;
			bRes = checkDependencyPresent(dependency, szFoundVersion);
			if(bRes){
				qDebug("[load-env] required dependency is found %s", qPrintable(szFoundVersion));
			}else{
				qWarning("[load-env] required dependency is not found");
			}

			if(!bRes){
				break;
			}
		}

		return bRes;
	}

	return bRes;
}

bool PackageCommandEnvironment::checkDependencyPresent(const PackageDependency& dependency, QString& szOutVersion)
{
	bool bRes = false;

	QDir dirSearchPackage;

	Environment& env = getEnv();
	if(env.isPerPackageMode()){
		dirSearchPackage = env.getVirtualEnvironmentPath();
	}else{
		dirSearchPackage = env.getVirtualEnvironmentReleaseDir();
	}

	QStringList listFilters;
	listFilters << QString("%0*").arg(dependency.getPackage());
	QFileInfoList listFiles = dirSearchPackage.entryInfoList(listFilters, QDir::Dirs, QDir::Name);

	QFileInfoList::const_iterator iter;
	for(iter = listFiles.constBegin(); iter != listFiles.constEnd(); ++iter)
	{
		const QFileInfo& fileInfo = (*iter);
		QString szVersion = fileInfo.fileName().remove(dependency.getPackage() + "-");
		if(VersionHelper::checkVersion(szVersion, dependency.getVersionMin(), dependency.getVersionMax())){
			bRes = true;
			szOutVersion = szVersion;
		}
	}

	return bRes;
}
