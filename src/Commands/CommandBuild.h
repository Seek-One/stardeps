/*
 * CommandBuild.h
 *
 *  Created on: 20 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_COMMANDBUILD_H_
#define SRC_COMMANDS_COMMANDBUILD_H_

#include "AbstractPackageCommand.h"

class CommandBuild : public AbstractPackageCommand {
public:
	CommandBuild();
	virtual ~CommandBuild();

protected:
	bool doExecute();
};

#endif /* SRC_COMMANDS_COMMANDBUILD_H_ */
