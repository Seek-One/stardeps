/*
 * CommandPrepare.h
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_COMMANDPREPARE_H_
#define SRC_COMMANDS_COMMANDPREPARE_H_

#include <QString>
#include <QSharedPointer>

#include "Formulas/Formula.h"

#include "AbstractCommand.h"

class CommandPrepare : public AbstractCommand {
public:
	CommandPrepare();
	virtual ~CommandPrepare();

	void setPackageName(const QString& szPackageName);

	bool execute();

private:
	bool prepareSources(const QSharedPointer<Formula>& pFormula);

private:
	QString m_szPackageName;
};

#endif /* SRC_COMMANDS_COMMANDPREPARE_H_ */
