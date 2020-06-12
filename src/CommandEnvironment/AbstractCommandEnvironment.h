/*
 * AbstractCommandEnvironment.h
 *
 *  Created on: 12 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDENVIRONMENT_ABSTRACTCOMMANDENVIRONMENT_H_
#define SRC_COMMANDENVIRONMENT_ABSTRACTCOMMANDENVIRONMENT_H_

#include <QDir>

#include "Environment/Environment.h"

class AbstractCommandEnvironment
{
public:
	AbstractCommandEnvironment();
	virtual ~AbstractCommandEnvironment();

// Data access
public:
	Environment& getEnv();

	void setVirtualEnvironmentPath(const QDir& dir);
	const QDir& getVirtualEnvironmentPath() const;

// Initialization
public:
	bool init(int argc, char**argv);
	void dispose();

// Prepare
public:
	bool load();

protected:
	virtual bool doProcessArgument(int i, const QString& szArg);
	virtual bool doLoad();

	void setNeedEnvVars(bool bNeed);

private:
	virtual bool doLoadEnv();

private:
	Environment m_env;
	bool m_bNeedEnvVars;

};

#endif /* SRC_COMMANDENVIRONMENT_ABSTRACTCOMMANDENVIRONMENT_H_ */
