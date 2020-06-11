/*
 * CommandsExecutor.cpp
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#include "Commands/CommandCreateEnv.h"
#include "Commands/CommandPrepare.h"
#include "Commands/CommandConfigure.h"
#include "Commands/CommandBuild.h"
#include "Commands/CommandInstall.h"

#include "CommandsExecutor.h"

CommandsExecutor::CommandsExecutor()
{

}

CommandsExecutor::~CommandsExecutor()
{
	AbstractCommand* pCommand;
	while(!m_listCommands.isEmpty()){
		pCommand = m_listCommands.takeFirst();
		delete pCommand;
	}
}

bool CommandsExecutor::prepareCommands(const QString& szCommand, int argc, char** argv)
{
	bool bRes = false;

	AbstractCommand* pCommand = NULL;

	// Check command
	if(szCommand == "createenv"){
		pCommand = new CommandCreateEnv();
    }else if(szCommand == "prepare"){
		pCommand = new CommandPrepare();
    }else if(szCommand == "configure"){
		pCommand = new CommandConfigure();
    }else if(szCommand == "build"){
		pCommand = new CommandBuild();
    }else if(szCommand == "install"){
		pCommand = new CommandInstall();
    }

	if(pCommand){
		bRes = true;

		pCommand->setVirtualEnvironmentPath(QDir("."));
		pCommand->prepare(argc, argv);

		m_listCommands.append(pCommand);
	}

	return bRes;

}


bool CommandsExecutor::executeCommands()
{
	bool bRes;

	QList<AbstractCommand*>::iterator iter;

	for(iter = m_listCommands.begin(); iter != m_listCommands.end(); ++iter)
	{
		AbstractCommand* pCommand = (*iter);
		bRes = pCommand->execute();
		if(!bRes){
			break;
		}
	}

	return bRes;
}
