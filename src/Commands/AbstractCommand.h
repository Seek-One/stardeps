/*
 * AbstractCommand.h
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_ABSTRACTCOMMAND_H_
#define SRC_COMMANDS_ABSTRACTCOMMAND_H_

#include "Shell/ShellExecutor.h"

class AbstractCommand
{
public:
	AbstractCommand();
	virtual ~AbstractCommand();

	void setVirtualEnvironmentPath(const QString& szPath);

protected:
	ShellExecutor m_shell;
	QString m_szVEPath;
};

#endif /* SRC_COMMANDS_ABSTRACTCOMMAND_H_ */
