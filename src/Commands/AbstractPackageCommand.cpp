/*
 * AbstractPackageCommand.cpp
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#include "Environment/EnvironmentDefs.h"

#include "CommandEnvironment/PackageCommandEnvironment.h"

#include "AbstractPackageCommand.h"

AbstractPackageCommand::AbstractPackageCommand(const QString& szLabel) : AbstractCommand(szLabel)
{

}

AbstractPackageCommand::~AbstractPackageCommand()
{

}


const QString& AbstractPackageCommand::getPackageName() const
{
	return getPackageCommandEnvironment()->getPackageName();
}

const QString& AbstractPackageCommand::getPackageVersion() const
{
	return getPackageCommandEnvironment()->getPackageVersion();
}

const QStringList& AbstractPackageCommand::getPackageOptions() const
{
	return getPackageCommandEnvironment()->getPackageOptions();
}

QString AbstractPackageCommand::getPackageNameVersion() const
{
	return getPackageCommandEnvironment()->getPackageNameVersion();
}

QDir AbstractPackageCommand::getRootPackageDir() const
{
	Environment& env = getEnv();
	return env.getVirtualEnvironmentPath().filePath(getPackageNameVersion());
}

QDir AbstractPackageCommand::getSourcePackageDir() const
{
	Environment& env = getEnv();
	if(env.isPerPackageMode()){
		return getRootPackageDir().filePath("src");
	}else{
		return env.getVirtualEnvironmentSourceDir().filePath(getPackageNameVersion());
	}
}

QDir AbstractPackageCommand::getBuildPackageDir() const
{
	Environment& env = getEnv();
	if(env.isPerPackageMode()){
		return getRootPackageDir().filePath("build");
	}else{
		return env.getVirtualEnvironmentBuildDir().filePath(getPackageNameVersion());
	}
}

QDir AbstractPackageCommand::getReleasePackageDir() const
{
	Environment& env = getEnv();
	if(env.isPerPackageMode()){
		return getRootPackageDir().filePath("release");
	}else{
		return env.getVirtualEnvironmentReleaseDir().filePath(getPackageNameVersion());
	}
}

bool AbstractPackageCommand::doRunCommand(const QString& szCmd, const QDir& dirWorkingDirectory)
{
	bool bRes;

	QString szCmdBind;
	bRes = doPrepareCommand(szCmd, szCmdBind);

	if(bRes){
		qDebug("[%s] %s", qPrintable(m_szLabel), qPrintable(szCmdBind));
		QStringList tokens = szCmdBind.split(' ');
		QString szCommand = tokens[0];

		// Rebuild cmd
		int i = 0;
		QStringList listArgs;
		QStringList::const_iterator iter;
		for(iter = tokens.constBegin(); iter != tokens.constEnd(); ++iter)
		{
			const QString& szArg = (*iter);
			if(i > 0 && !szArg.isEmpty()){
				listArgs.append(szArg);
			}
			i++;
		}

		if(!dirWorkingDirectory.exists()){
			qDebug("[%s] create directory: %s", qPrintable(m_szLabel), qPrintable(dirWorkingDirectory.path()));
			bRes = dirWorkingDirectory.mkpath(".");
		}
		bRes = m_shell.runCommand(tokens[0], listArgs, dirWorkingDirectory);
	}

	return bRes;
}

bool AbstractPackageCommand::doPrepareCommand(const QString& szCmd, QString& szCmdOut)
{
	szCmdOut = szCmd;

	QMap<QString, QString> dictVars;

	Environment& env = getEnv();

	// Tools
	dictVars.insert("${TOOL::GIT}", env.getEnvVar(VE_VAR_GIT));
	dictVars.insert("${TOOL::MAKE}", env.getEnvVar(VE_VAR_MAKE));
	dictVars.insert("${TOOL::RSYNC}", env.getEnvVar(VE_VAR_RSYNC));
	dictVars.insert("${TOOL::COMPILER}", env.getEnvVar(VE_VAR_COMPILER));

	// Package infos
	dictVars.insert("${PACKAGE_VERSION}", getPackageNameVersion());
	dictVars.insert("${PACKAGE_SRC_PATH}", getSourcePackageDir().absolutePath());
	dictVars.insert("${PACKAGE_BUILD_PATH}", getBuildPackageDir().absolutePath());
	dictVars.insert("${PACKAGE_PREFIX_PATH}", getReleasePackageDir().absolutePath());

	// Configure
	dictVars.insert("${CONFIGURE_OPTIONS}", QString());
    
    // Options
    /**
     TODO: make sure that formula's options are previously prepared if necessary (step is missing for now)
     */
    doPrepareCommandOptions(dictVars);
    
	QMap<QString, QString>::const_iterator iter;
	for(iter = dictVars.constBegin(); iter != dictVars.constEnd(); ++iter)
	{
		szCmdOut = szCmdOut.replace(iter.key(), iter.value());
	}

    // Last step, remove non-referenced optional values
    szCmdOut = szCmdOut.remove(QRegExp("\\$\\{.*\\}"));

	return true;
}

bool AbstractPackageCommand::doPrepareCommandOptions(QMap<QString, QString>& dictVars) const
{
    if(!getPackageOptions().isEmpty() && getFormula()){
        FormulaOptionList::const_iterator formulaOptionIter;
        FormulaVariableList::const_iterator formulaVariableIter;
        
        QStringList packagesOptions = getPackageOptions();
        QStringList::const_iterator packageOptionIter = packagesOptions.constBegin();
        for(; packageOptionIter != packagesOptions.constEnd(); ++packageOptionIter){
            formulaOptionIter = getFormula()->getOptions().constBegin();
            
            for(; formulaOptionIter != getFormula()->getOptions().constEnd(); ++formulaOptionIter){
                if(formulaOptionIter->getOptionName() == *packageOptionIter){
                    formulaVariableIter = formulaOptionIter->getVariableList().constBegin();
                    
                    for(; formulaVariableIter != formulaOptionIter->getVariableList().constEnd(); ++formulaVariableIter) {
                        dictVars.insert(QString("${%0}").arg(formulaVariableIter.key()), formulaVariableIter.value());
                    }
                    
                    continue;
                }
            }
        }
    }
    
    return true;
}

bool AbstractPackageCommand::doProcessArgument(int i, const QString& szArg)
{
	return AbstractCommand::doProcessArgument(i, szArg);
}

PackageCommandEnvironment* AbstractPackageCommand::getPackageCommandEnvironment() const
{
	return (PackageCommandEnvironment*)getCommandEnvironment();
}

const QSharedPointer<Formula>& AbstractPackageCommand::getFormula() const
{
	return getPackageCommandEnvironment()->getFormula();
}

Environment& AbstractPackageCommand::getEnv() const
{
	return m_pCommandEnvironment->getEnv();
}
