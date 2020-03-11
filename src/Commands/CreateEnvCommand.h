/*
 * CreateEnvCommand.h
 *
 *  Created on: 11 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_CREATEENVCOMMAND_H_
#define SRC_COMMANDS_CREATEENVCOMMAND_H_

#include <QString>

class CreateEnvCommand {
public:
	CreateEnvCommand();
	virtual ~CreateEnvCommand();

	static bool execute(const QString& szVEPath, const QString& szPlatform);
};

#endif /* SRC_COMMANDS_CREATEENVCOMMAND_H_ */
