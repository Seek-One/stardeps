/*
 * CommandInstall.h
 *
 *  Created on: 11 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_COMMANDINSTALL_H_
#define SRC_COMMANDS_COMMANDINSTALL_H_

#include <QString>

class CommandInstall {
public:
	CommandInstall();
	virtual ~CommandInstall();

	static bool execute(const QString& szVEPath, const QString& szPackage);
};

#endif /* SRC_COMMANDS_COMMANDINSTALL_H_ */
