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

const PackageOptionList& AbstractPackageCommand::getPackageOptions() const
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
		QStringList listCmdEnvVars;
		QString szCmdExecutable;
		QStringList listArgs;
		QStringList::const_iterator iter;
		for(iter = tokens.constBegin(); iter != tokens.constEnd(); ++iter)
		{
			const QString& szArg = (*iter);
			if(!szCmdExecutable.isEmpty()){
				listArgs.append(szArg);
			}else{
				// Support for command given with env variables
				// CC=gcc configure
				if(szArg.contains("=")){
					listCmdEnvVars.append(szArg);
				}else{
					szCmdExecutable = szArg;
				}
			}
		}

		if(!dirWorkingDirectory.exists()){
			qDebug("[%s] create directory: %s", qPrintable(m_szLabel), qPrintable(dirWorkingDirectory.path()));
			bRes = dirWorkingDirectory.mkpath(".");
		}
		if(bRes) {
            bRes = m_shell.runCommand(szCmdExecutable, listArgs, listCmdEnvVars, dirWorkingDirectory);
        }
	}

	return bRes;
}

bool AbstractPackageCommand::doRunCommands(const QStringList& listCmd, const QDir& dirWorkingDirectory)
{
    bool bRes = true;

    QStringList::const_iterator iter;
    for(iter = listCmd.constBegin(); iter != listCmd.constEnd(); ++iter)
    {
        bRes = doRunCommand(*iter, dirWorkingDirectory);
        if(!bRes){
        	break;
        }
    }

    return bRes;
}

bool AbstractPackageCommand::doChangeDirectoryAction(const QString& szDirectory)
{
	bool bRes = true;

	QString szDirectoryBind;
	bRes = doPrepareCommand(szDirectory, szDirectoryBind);
	if(bRes){
		qDebug("[%s] change current directory to %s", qPrintable(m_szLabel), qPrintable(szDirectoryBind));
		m_dirCurrentWorkingDirectory.setPath(szDirectoryBind);
	}

	return bRes;
}

bool AbstractPackageCommand::doCopyFilesAction(const QStringList& listSources, const QString& szDestination)
{
	bool bRes = true;

	QString szDestinationBind;
	bRes = doPrepareCommand(szDestination, szDestinationBind);

	QStringList::const_iterator iter;
	if(bRes){
		for(iter = listSources.constBegin(); iter != listSources.constEnd(); ++iter)
		{
			const QString& szSource = (*iter);
			QString szSourceBind;
			bRes = doPrepareCommand(szSource, szSourceBind);
			if(bRes){
				bRes = doCopyFilesAction(szSourceBind, szDestinationBind);
			}
			if(!bRes){
				break;
			}
		}
	}

	return bRes;
}

bool AbstractPackageCommand::doCopyFilesAction(const QString& szSource, const QString& szDestination)
{
	bool bRes = true;

	// Define sources file depending on pattern
	QFileInfo fileInfoSource(szSource);
	QDir dirSource;
	QString szFileName;
	if(fileInfoSource.isDir()){
		dirSource.setPath(fileInfoSource.path());
	}else{
		dirSource = fileInfoSource.dir();
		szFileName = fileInfoSource.fileName();
	}

	bRes = doCopyFilesAction(dirSource, szFileName, szDestination);

	return bRes;
}

bool AbstractPackageCommand::doCopyFilesAction(const QDir& dirSource, const QString& szPattern, const QDir& dirDestination)
{
	bool bRes = true;

	QDir::Filters filters = QDir::AllEntries | QDir::NoDotAndDotDot;

	// Get file list in dir
	QFileInfoList listFileInfo;
	if(szPattern.isEmpty()){
		listFileInfo = dirSource.entryInfoList(filters);
	}else{
		listFileInfo = dirSource.entryInfoList(QStringList() << szPattern, filters);
	}

	// Create directory
	if(!dirDestination.exists()){
		qDebug("[%s] creating directory %s", qPrintable(m_szLabel), qPrintable(dirDestination.path()));
		bRes = dirDestination.mkdir(".");
		if(!bRes){
			return bRes;
		}
	}

	// Copy each file
	QFileInfoList::const_iterator iter;
	for(iter = listFileInfo.constBegin(); iter != listFileInfo.constEnd(); ++iter)
	{
		const QFileInfo& fileInfo = (*iter);
		const QString szFilePath = fileInfo.filePath();

		QString szFileName = fileInfo.fileName();
		if(fileInfo.isDir()){
			qDebug("[%s] copy directory %s to %s", qPrintable(m_szLabel), qPrintable(szFilePath), qPrintable(dirDestination.path()));
			bRes = doCopyFilesAction(QDir(fileInfo.path()), QString(), dirDestination.filePath(szFileName));
		}else if(fileInfo.isSymLink()){
			qDebug("[%s] copy symlink %s to %s", qPrintable(m_szLabel), qPrintable(szFilePath), qPrintable(dirDestination.path()));

			QString szOutputPath = dirDestination.filePath(szFileName);
			QFile fileSrc(szFilePath);
			QFile fileDst(szOutputPath);
			if(fileDst.exists()){
				bRes = fileDst.remove();
			}
			if(bRes){
				bRes = fileSrc.link(szOutputPath);
			}
		}else{
			qDebug("[%s] copy files %s to %s", qPrintable(m_szLabel), qPrintable(szFilePath), qPrintable(dirDestination.path()));

			QString szOutputPath = dirDestination.filePath(szFileName);
			QFile fileSrc(szFilePath);
			QFile fileDst(szOutputPath);
			if(fileDst.exists()){
				bRes = fileDst.remove();
			}
			if(bRes){
				bRes = fileSrc.copy(szOutputPath);
			}
		}
		if(!bRes){
			break;
		}
	}

	return bRes;
}

bool AbstractPackageCommand::doExecuteStep(const QString& szStep, const QDir& dirWorkingDirectory)
{
	bool bRes = true;

	Environment &env = getEnv();

	const QSharedPointer<Formula>& pFormula = getFormula();
	const QString& szPlatform = env.getPlatformTypeName();
	const FormulaRecipeList& listFormulaRecipes = pFormula->getRecipeList();

	if(listFormulaRecipes.contains(QString())){
		const FormulaRecipe& formulaRecipe = listFormulaRecipes.value(QString());
		FormulaStepActionList listFormulaStepAction;
		listFormulaStepAction = formulaRecipe.getFormulaStepActionList(szStep, szPlatform, getPackageNameVersion(), getPackageOptions());

		FormulaStepActionList::const_iterator iter_action;
		for(iter_action = listFormulaStepAction.constBegin(); iter_action != listFormulaStepAction.constEnd(); ++iter_action)
		{
			QDir dirCurrentWorkingDirectory = getWorkingDirectory(dirWorkingDirectory);

			const FormulaStepAction& formulaStepAction = (*iter_action);
			if(formulaStepAction.getActionType() == FormulaStepAction::ActionCommand)
			{
				bRes = doRunCommands(formulaStepAction.getCommandList(), dirCurrentWorkingDirectory);
			}
			if(formulaStepAction.getActionType() == FormulaStepAction::ActionChangeDirectory)
			{
				bRes = doChangeDirectoryAction(formulaStepAction.getDirectory());
			}
			if(formulaStepAction.getActionType() == FormulaStepAction::ActionCopy)
			{
				bRes = doCopyFilesAction(formulaStepAction.getSources(), formulaStepAction.getDestination());
			}
			if(!bRes){
				break;
			}
		}
	}

	return bRes;
}

bool AbstractPackageCommand::doInitDictVars(VariableList& dictVars)
{
	Environment &env = getEnv();

	const QSharedPointer<Formula> &pFormula = getFormula();
	const FormulaOptionList &listFormulaOptions = pFormula->getOptions();

	// Add envirnoment variable
	const EnvironmentVars &environmentVars = env.getVars();
	dictVars.addVariableList(environmentVars);

	// Get command environement variables
	const VariableList &listCmdEndVars = getCommandEnvironment()->getVariableList();
	dictVars.addVariableList(listCmdEndVars);

	// Package infos
	dictVars.addVariable("PACKAGE_VERSION", getPackageNameVersion());
	dictVars.addVariable("PACKAGE_SRC_PATH", getSourcePackageDir().absolutePath());
	dictVars.addVariable("PACKAGE_BUILD_PATH", getBuildPackageDir().absolutePath());
	dictVars.addVariable("PACKAGE_PREFIX_PATH", getReleasePackageDir().absolutePath());

	// Formula options variable
	const PackageOptionList& listPackageOptions = getPackageOptions();
	FormulaOptionList::const_iterator iter_formula_option;
	for (iter_formula_option = listFormulaOptions.constBegin(); iter_formula_option != listFormulaOptions.constEnd(); ++iter_formula_option) {
		const FormulaOption &formulaOption = *iter_formula_option;

		// Option state
		bool bIsOptionEnabled = false;
		QString szOptionName = formulaOption.getOptionName();
		bIsOptionEnabled = formulaOption.getDefaultState();
		QStringList listOptionModes;
		if (listPackageOptions.contains(szOptionName)) {
			bIsOptionEnabled = true;
			listOptionModes = listPackageOptions.getModes(szOptionName);
		}

		// Get rules
		FormulaVariableList listOptionsVars = formulaOption.getVariableListForState(bIsOptionEnabled, listOptionModes);
		FormulaVariableList::const_iterator iter_var;
		for (iter_var = listOptionsVars.constBegin(); iter_var != listOptionsVars.constEnd(); ++iter_var) {
			QString szNewValue;
			doReplaceVariable(iter_var->getValue(), dictVars, szNewValue);
			dictVars.addVariable(iter_var->getName(), szNewValue);
		}
	}

	// Global formulas vars
	{
		const FormulaVariableList &listGlobalVars = pFormula->getGlobalVariables();
		FormulaVariableList::const_iterator iter_var;
		for (iter_var = listGlobalVars.constBegin(); iter_var != listGlobalVars.constEnd(); ++iter_var) {
			QString szNewValue;
			VariableList dictVarsTmp = listGlobalVars;
			dictVarsTmp.setValues(dictVars);
			doReplaceVariable(iter_var->getValue(), dictVarsTmp, szNewValue);
			dictVars.addVariable(iter_var->getName(), szNewValue);
		}
	}

	//dictVars.print();

	return true;
}

bool AbstractPackageCommand::doReplaceVariable(const QString& szText, const VariableList& dictVars, QString& szTextOut)
{
	szTextOut = szText;

	VariableList::const_iterator iter;
	for(iter = dictVars.constBegin(); iter != dictVars.constEnd(); ++iter)
	{
		QString szKey = "${" + iter->getName() + "}";
		szTextOut = szTextOut.replace(szKey, iter->getValue());
	}

	// Last step, remove non-referenced optional values
	szTextOut = szTextOut.remove(QRegExp("\\$\\{[^\\}]+\\}"));

	return true;
}

bool AbstractPackageCommand::doReplaceVariable(const QString& szText, const VariableList& dictVars1, const VariableList& dictVars2, QString& szTextOut)
{
	szTextOut = szText;

	VariableList::const_iterator iter;
	
	// Replace with the current dict first
	for(iter = dictVars1.constBegin(); iter != dictVars1.constEnd(); ++iter)
	{
		QString szKey = "${" + iter->getName() + "}";
		szTextOut = szTextOut.replace(szKey, iter->getValue());
	}

	// Replace with the current list
	for(iter = dictVars2.constBegin(); iter != dictVars2.constEnd(); ++iter)
	{
		QString szKey = "${" + iter->getName() + "}";
		szTextOut = szTextOut.replace(szKey, iter->getValue());
	}

	// Last step, remove non-referenced optional values
	szTextOut = szTextOut.remove(QRegExp("\\$\\{[^\\}]+\\}"));

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

enum ParseCommandState { Idle, Arg, QuotedArg };

void AbstractPackageCommand::parseCommand(const QString& szCmd, QStringList& listOutTokens) const
{
    QString szArg;
    bool bEscape = false;
    ParseCommandState iState = Idle;

    QChar curArgQuote;

    QString::const_iterator iter;
    for(iter = szCmd.constBegin(); iter != szCmd.constEnd(); ++iter){
        const QChar& c = (*iter);

        if (!bEscape && c == '\\') {
            bEscape = true;
            continue;
        }

        switch (iState) {
            case Idle:
                if (!bEscape && (c == '"' || c == '\'')){
                    iState = QuotedArg;
                    curArgQuote = c;
                } else if (bEscape || !c.isSpace()) {
                    szArg += c; iState = Arg;
                }
                break;
            case Arg:
                if (!bEscape && (c == '"' || c == '\'')){
                    iState = QuotedArg;
                    curArgQuote = c;
                } else if (bEscape || !c.isSpace()){
                    szArg += c;
                } else {
                    listOutTokens << szArg;
                    szArg.clear();
                    iState = Idle;
                }
                break;
            case QuotedArg:
                if (!bEscape && (c == curArgQuote)){
                    iState = (szArg.isEmpty() ? Idle : Arg);
                    curArgQuote = QChar();
                } else {
                    szArg += c;
                }
                break;
        }
        bEscape = false;
    }
    if (!szArg.isEmpty()){
        listOutTokens << szArg;
    }
}
