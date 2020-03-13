/*
 * CommandPrepare.h
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_COMMANDPREPARE_H_
#define SRC_COMMANDS_COMMANDPREPARE_H_

#include <QString>

class CommandPrepare {
public:
	CommandPrepare();
	virtual ~CommandPrepare();

	static bool execute(const QString& szVEPath, const QString& szPackage);
};

#endif /* SRC_COMMANDS_COMMANDPREPARE_H_ */
