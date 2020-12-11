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

	void setTargetPlatform(const QString& szTargetPlatform);

protected:
	bool doProcessArgument(int i, const QString& szArg);
	bool doExecute();

private:
	bool findGit(Environment& env);
	bool findMercurial(Environment& env);
	bool findCompiler(Environment& env);
	bool findMake(Environment& env);
	bool findRSync(Environment& env);
    bool findTar(Environment& env);
    bool findWget(Environment& env);

	QString m_szTargetPlatform;
};

#endif /* SRC_COMMANDS_COMMANDCREATEENV_H_ */
