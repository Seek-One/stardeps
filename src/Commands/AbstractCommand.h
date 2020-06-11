/*
 * AbstractCommand.h
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_ABSTRACTCOMMAND_H_
#define SRC_COMMANDS_ABSTRACTCOMMAND_H_

#include <QString>
#include <QDir>
#include <QSharedPointer>

#include "Environment/Environment.h"
#include "Shell/ShellExecutor.h"
#include "Formulas/Formula.h"

class AbstractCommand
{
public:
	AbstractCommand(const QString& szLabel);
	virtual ~AbstractCommand();

	void setVirtualEnvironmentPath(const QDir& dir);
	const QDir& getVirtualEnvironmentPath() const;

	bool prepare(int argc, char**argv);

	bool execute();

protected:
	virtual bool doInitEnv();
	virtual bool doProcessArgument(int i, const QString& szArg);
	virtual bool doExecute() = 0;

	bool loadFormula(const QString& szPackageName, QSharedPointer<Formula>& pFormula);

protected:
	QString m_szLabel;

	Environment m_env;
	bool m_bNeedEnvVars;

	ShellExecutor m_shell;
};

#endif /* SRC_COMMANDS_ABSTRACTCOMMAND_H_ */
