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

QDir AbstractPackageCommand::getSourceArchivePackageDir() const
{
    Environment& env = getEnv();
    if(env.isPerPackageMode()){
        return getRootPackageDir();
    }else{
        return getRootPackageDir();
    }
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

        QStringList tokens;
        parseCommand(szCmdBind, tokens);

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

bool AbstractPackageCommand::doInitDictVars(VariableList& dictVars)
{
	Environment& env = getEnv();

	const QSharedPointer<Formula>& pFormula = getFormula();
	const FormulaOptionList& listFormulaOptions = pFormula->getOptions();

	// Add envirnoment variable
	 const EnvironmentVars& environmentVars = env.getVars();
	EnvironmentVars::const_iterator iter_env;
	for(iter_env = environmentVars.constBegin(); iter_env != environmentVars.constEnd(); ++iter_env){
	dictVars.insert(iter_env.key(), iter_env.value());
	}

	// Get command environement variables
	const VariableList& listCmdEndVars = getCommandEnvironment()->getVariableList();
	VariableList::const_iterator iter_var;
	for(iter_var = listCmdEndVars.constBegin(); iter_var != listCmdEndVars.constEnd(); ++iter_var)
	{
		dictVars.insert(iter_var.key(), iter_var.value());
	}

	// Package infos
	dictVars.insert("PACKAGE_VERSION", getPackageNameVersion());
	dictVars.insert("PACKAGE_SRC_PATH", getSourcePackageDir().absolutePath());
	dictVars.insert("PACKAGE_BUILD_PATH", getBuildPackageDir().absolutePath());
	dictVars.insert("PACKAGE_PREFIX_PATH", getReleasePackageDir().absolutePath());

	// Formula options variable
	const QStringList& listOptions = getPackageOptions();
	QStringList::const_iterator iter;
	for(iter = listOptions.constBegin(); iter != listOptions.constEnd(); ++iter)
	{
		const FormulaOption& formulaOption = listFormulaOptions.getOptionByName(*iter);
		if(!formulaOption.isNull()){
			const FormulaVariableList& listOptionsVars = formulaOption.getVariableList();
			FormulaVariableList::const_iterator iter_var;
			for(iter_var = listOptionsVars.constBegin(); iter_var != listOptionsVars.constEnd(); ++iter_var)
			{
				QString szNewValue;
				doReplaceVariable(iter_var.value(), dictVars, szNewValue);
				dictVars.insert(iter_var.key(), szNewValue);
			}
		}
	}

	return true;
}

bool AbstractPackageCommand::doReplaceVariable(const QString& szText, const VariableList& dictVars, QString& szTextOut)
{
	szTextOut = szText;

	VariableList::const_iterator iter;
	for(iter = dictVars.constBegin(); iter != dictVars.constEnd(); ++iter)
	{
		QString szKey = "${" + iter.key() + "}";
		szTextOut = szTextOut.replace(szKey, iter.value());
	}

	// Last step, remove non-referenced optional values
	szTextOut = szTextOut.remove(QRegExp("\\$\\{.*\\}"));

	return true;
}

bool AbstractPackageCommand::doPrepareCommand(const QString& szCmd, QString& szCmdOut)
{
	bool bRes;

	szCmdOut = szCmd;

	VariableList dictVars;

	bRes = doInitDictVars(dictVars);

    //dictVars.print();

	if(bRes){
		bRes = doReplaceVariable(szCmd, dictVars, szCmdOut);
	}

	return bRes;
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

void AbstractPackageCommand::parseCommand(const QString& szCmd, QStringList& outTokens) const
{
    QString szTmp;
    QStringList list = szCmd.split(' ');
    QStringList::const_iterator iter = list.constBegin();
    for(; iter != list.constEnd(); ++iter){
        if(!iter->startsWith("\"") && szTmp.isEmpty()){
            outTokens.append(*iter);
            continue;
        }else{
            if(szTmp.isEmpty()){
                szTmp = *iter;
            }else{
                szTmp += " " + *iter;
            }
        }
        
        if(iter->endsWith("\"")){
            outTokens.append(szTmp);
            szTmp = QString();
        }
    }
}
