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
#include "Variable/VariableList.h"

class AbstractCommandEnvironment
{
public:
	AbstractCommandEnvironment();
	virtual ~AbstractCommandEnvironment();

// Data access
public:
	Environment& getEnv();
	const Environment& getEnv() const;

	void setVirtualEnvironmentPath(const QDir& dir);
	const QDir& getVirtualEnvironmentPath() const;

    QDir getFormulasDir() const;


// Initialization
public:
	bool init(int argc, char**argv);
	void dispose();

// Prepare
public:
	bool load();

	const VariableList& getVariableList() const;

protected:
	virtual bool doProcessArgument(int i, const QString& szArg);
	virtual bool doLoad();

	void setNeedEnvVars(bool bNeed);

	void addVariable(const QString& szName, const QString& szValue);

private:
	virtual bool doLoadEnv();

private:
	Environment m_env;
	bool m_bNeedEnvVars;
	VariableList m_listCmdEnvVars;
};

#endif /* SRC_COMMANDENVIRONMENT_ABSTRACTCOMMANDENVIRONMENT_H_ */
