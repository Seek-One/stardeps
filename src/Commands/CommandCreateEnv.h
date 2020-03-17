/*
 * CommandCreateEnv.h
 *
 *  Created on: 11 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_COMMANDCREATEENV_H_
#define SRC_COMMANDS_COMMANDCREATEENV_H_

#include <QString>

class CommandCreateEnv {
public:
	CommandCreateEnv();
	virtual ~CommandCreateEnv();

	static bool execute(const QString& szVEPath, const QString& szPlatform);
};

#endif /* SRC_COMMANDS_COMMANDCREATEENV_H_ */
