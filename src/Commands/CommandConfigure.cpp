/*
 * CommandConfigure.cpp
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#include "CommandConfigure.h"

CommandConfigure::CommandConfigure() : AbstractPackageCommand("configure")
{

}

CommandConfigure::~CommandConfigure()
{

}


bool CommandConfigure::doExecute()
{
	bool bRes;

	// Load formula
	QSharedPointer<Formula> pFormula;
	bRes = loadFormula(m_szPackageName, pFormula);

	// Execute commands
	if(bRes){
		const FormulaConfigureRulesList& listConfigureRules = pFormula->getConfigureRules();
		QString szTargetPlateform = m_env.getPlatformTypeName();
		if(listConfigureRules.contains(szTargetPlateform)){
			const FormulaCommands& listCommands = listConfigureRules.value(szTargetPlateform);
			FormulaCommands::const_iterator iter_cmd;
			for(iter_cmd = listCommands.constBegin(); iter_cmd != listCommands.constEnd(); ++iter_cmd)
			{
				bRes = runCommand((*iter_cmd));
				if(!bRes){
					qCritical("[configure] aborting configure due to error");
					break;
				}
			}
		}
	}

	return bRes;
}

bool CommandConfigure::runCommand(const QString& szCmd)
{
	bool bRes;

	QDir dirBuild = getBuildPackageDir();

	QString szCmdBind;
	bRes = doPrepareCommand(szCmd, szCmdBind);

	if(bRes){
		qDebug("[configure] %s", qPrintable(szCmdBind));
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

		if(!dirBuild.exists()){
			qDebug("[configure] create build directory: %s", qPrintable(dirBuild.path()));
			bRes = dirBuild.mkpath(".");
		}
		bRes = m_shell.runCommand(tokens[0], listArgs, dirBuild);
	}

	return bRes;
}

bool CommandConfigure::doPrepareCommand(const QString& szCmd, QString& szCmdOut)
{
	szCmdOut = szCmd;

	QDir dirSrcPackage = getSourcePackageDir();
	szCmdOut = szCmdOut.replace("${PACKAGE_SRC_PATH}", dirSrcPackage.absolutePath());

	QDir dirReleasePackage = getReleasePackageDir();
	szCmdOut = szCmdOut.replace("${PACKAGE_PREFIX_PATH}", dirReleasePackage.absolutePath());

	szCmdOut = szCmdOut.replace("${CONFIGURE_OPTIONS}", QString());

	return true;
}
