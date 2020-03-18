/*
 * CommandCreateEnv.h
 *
 *  Created on: 11 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_COMMANDCREATEENV_H_
#define SRC_COMMANDS_COMMANDCREATEENV_H_

#include "Environment/Environment.h"

#include "AbstractCommand.h"

class CommandCreateEnv : public AbstractCommand
{
public:
	CommandCreateEnv();
	virtual ~CommandCreateEnv();

protected:
	bool doExecute();

private:
	bool findGit(Environment& env);
	bool findCompiler(Environment& env);
};

#endif /* SRC_COMMANDS_COMMANDCREATEENV_H_ */
