/*
 * AbstractCommand.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include "CommandEnvironment/AbstractCommandEnvironment.h"

#include "AbstractCommand.h"

AbstractCommand::AbstractCommand(const QString& szLabel)
{
	m_szLabel = szLabel;
	m_pCommandEnvironment = NULL;
}

AbstractCommand::~AbstractCommand()
{

}

void AbstractCommand::setCommandEnvironment(AbstractCommandEnvironment* pCmdEnd)
{
	m_pCommandEnvironment = pCmdEnd;
}

AbstractCommandEnvironment* AbstractCommand::getCommandEnvironment() const
{
	return m_pCommandEnvironment;
}

const QDir& AbstractCommand::getVirtualEnvironmentPath() const
{
	return getCommandEnvironment()->getVirtualEnvironmentPath();
}

bool AbstractCommand::init(int argc, char**argv)
{
	bool bRes = true;

	QString szArg;

	for(int i=0; i<argc; i++)
	{
		szArg = argv[i];
		bRes = doProcessArgument(i, szArg);
		if(!bRes){
			break;
		}
	}

	return bRes;
}

bool AbstractCommand::doProcessArgument(int i, const QString& szArg)
{
	return true;
}

bool AbstractCommand::execute()
{
	bool bRes;

	bRes = doExecute();

	return bRes;
}
