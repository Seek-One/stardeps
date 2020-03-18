/*
 * AbstractCommand.h
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_ABSTRACTCOMMAND_H_
#define SRC_COMMANDS_ABSTRACTCOMMAND_H_

#include <QDir>

#include "Environment/Environment.h"
#include "Shell/ShellExecutor.h"

class AbstractCommand
{
public:
	AbstractCommand();
	virtual ~AbstractCommand();

	void setVirtualEnvironmentPath(const QDir& dir);
	const QDir& getVirtualEnvironmentPath() const;

	bool execute();

protected:
	virtual bool doInitEnv();
	virtual bool doExecute() = 0;

protected:
	Environment m_env;
	bool m_bNeedEnvVars;
	ShellExecutor m_shell;
};

#endif /* SRC_COMMANDS_ABSTRACTCOMMAND_H_ */
