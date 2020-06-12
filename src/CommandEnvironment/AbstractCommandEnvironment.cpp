/*
 * AbstractCommandEnvironment.cpp
 *
 *  Created on: 12 juin 2020
 *      Author: ebeuque
 */

#include "Environment/EnvironmentLoader.h"

#include "AbstractCommandEnvironment.h"

AbstractCommandEnvironment::AbstractCommandEnvironment()
{
	m_bNeedEnvVars = false;
}

AbstractCommandEnvironment::~AbstractCommandEnvironment()
{

}

Environment& AbstractCommandEnvironment::getEnv()
{
	return m_env;
}

const Environment& AbstractCommandEnvironment::getEnv() const
{
	return m_env;
}

void AbstractCommandEnvironment::setVirtualEnvironmentPath(const QDir& dir)
{
	m_env.setVirtualEnvironmentPath(dir);
}

const QDir& AbstractCommandEnvironment::getVirtualEnvironmentPath() const
{
	return m_env.getVirtualEnvironmentPath();
}

bool AbstractCommandEnvironment::init(int argc, char**argv)
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

void AbstractCommandEnvironment::dispose()
{

}

bool AbstractCommandEnvironment::load()
{
	bool bRes;
	bRes = doLoadEnv();
	if(bRes){
		bRes = doLoad();
	}

	m_listCmdEnvVars.print();

	return bRes;
}

bool AbstractCommandEnvironment::doProcessArgument(int i, const QString& szArg)
{
	return true;
}

bool AbstractCommandEnvironment::doLoad()
{
	return true;
}

bool AbstractCommandEnvironment::doLoadEnv()
{
	bool bRes = true;
	EnvironmentLoader envLoader;
	if(m_bNeedEnvVars){
		bRes = envLoader.loadEnvironmentVars(m_env);
		m_env.print();
	}
	return bRes;
}

void AbstractCommandEnvironment::setNeedEnvVars(bool bNeed)
{
	m_bNeedEnvVars = bNeed;
}

void AbstractCommandEnvironment::addVariable(const QString& szName, const QString& szValue)
{
	m_listCmdEnvVars.insert(szName, szValue);
}

const VariableList& AbstractCommandEnvironment::getVariableList() const
{
	return m_listCmdEnvVars;
}
