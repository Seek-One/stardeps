/*
 * CommandConfigure.h
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_COMMANDCONFIGURE_H_
#define SRC_COMMANDS_COMMANDCONFIGURE_H_

#include "AbstractCommand.h"

class CommandConfigure : public AbstractCommand {
public:
	CommandConfigure();
	virtual ~CommandConfigure();



	static bool execute(const QString& szVEPath, const QString& szPlatform);
};

#endif /* SRC_COMMANDS_COMMANDCONFIGURE_H_ */
