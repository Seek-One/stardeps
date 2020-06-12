/*
 * CommandsExecutor.cpp
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#include "CommandEnvironment/AbstractCommandEnvironment.h"
#include "CommandEnvironment/DefaultCommandEnvironment.h"
#include "CommandEnvironment/PackageCommandEnvironment.h"

#include "Commands/CommandCreateEnv.h"
#include "Commands/CommandPrepare.h"
#include "Commands/CommandConfigure.h"
#include "Commands/CommandBuild.h"
#include "Commands/CommandInstall.h"

#include "CommandsExecutor.h"

CommandsExecutor::CommandsExecutor()
{
	m_pCommandEnv = NULL;
}

CommandsExecutor::~CommandsExecutor()
{
	AbstractCommand* pCommand;
	while(!m_listCommands.isEmpty()){
		pCommand = m_listCommands.takeFirst();
		delete pCommand;
	}

	if(m_pCommandEnv){
		delete m_pCommandEnv;
		m_pCommandEnv = NULL;
	}
}

bool CommandsExecutor::prepareCommands(const QString& szCommand, int argc, char** argv)
{
	bool bRes = false;

	AbstractCommand* pCommand = NULL;

	bool bPackageCommand = false;

	// Check command
	if(szCommand == "createenv"){
		pCommand = new CommandCreateEnv();
    }else if(szCommand == "prepare"){
		pCommand = new CommandPrepare();
		bPackageCommand = true;
    }else if(szCommand == "configure"){
		pCommand = new CommandConfigure();
		bPackageCommand = true;
    }else if(szCommand == "build"){
		pCommand = new CommandBuild();
		bPackageCommand = true;
    }else if(szCommand == "install"){
		pCommand = new CommandInstall();
		bPackageCommand = true;
    }

	if(pCommand){
		bRes = true;

		// Initialize commands env
		if(bPackageCommand){
			m_pCommandEnv = new PackageCommandEnvironment();
		}else{
			m_pCommandEnv = new DefaultCommandEnvironment();
		}
		m_pCommandEnv->setVirtualEnvironmentPath(QDir("."));

		bRes = m_pCommandEnv->init(argc, argv);
	}

	// Prepare the commands
	if(bRes){
		pCommand->setCommandEnvironment(m_pCommandEnv);

		bRes = pCommand->init(argc, argv);
	}

	// Append commands to the list
	if(bRes){
		m_listCommands.append(pCommand);
	}

	if(!bRes && pCommand){
		delete pCommand;
		pCommand = NULL;
	}

	return bRes;
}

bool CommandsExecutor::executeCommands()
{
	bool bRes = true;

	QList<AbstractCommand*>::iterator iter;

	// Run
	if(m_pCommandEnv){
		bRes = m_pCommandEnv->load();
	}

	// Execute commands list
	if(bRes){
		for(iter = m_listCommands.begin(); iter != m_listCommands.end(); ++iter)
		{
			AbstractCommand* pCommand = (*iter);
			bRes = pCommand->execute();
			if(!bRes){
				break;
			}
		}
	}

	return bRes;
}
