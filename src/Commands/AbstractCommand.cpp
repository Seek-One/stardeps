/*
 * AbstractCommand.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include "Environment/EnvironmentLoader.h"

#include "AbstractCommand.h"

AbstractCommand::AbstractCommand()
{
	m_bNeedEnvVars = true;
}

AbstractCommand::~AbstractCommand()
{

}

void AbstractCommand::setVirtualEnvironmentPath(const QDir& dir)
{
	m_env.setVirtualEnvironmentPath(dir);
}

const QDir& AbstractCommand::getVirtualEnvironmentPath() const
{
	return m_env.getVirtualEnvironmentPath();
}

bool AbstractCommand::doInitEnv()
{
	bool bRes = true;
	EnvironmentLoader envLoader;
	if(m_bNeedEnvVars){
		bRes = envLoader.loadEnvironmentVars(m_env);
		m_env.print();
	}
	return bRes;
}

bool AbstractCommand::execute()
{
	bool bRes;

	bRes = doInitEnv();
	if(bRes){
		bRes = doExecute();
	}

	return bRes;
}
