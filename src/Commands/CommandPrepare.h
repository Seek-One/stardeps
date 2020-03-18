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
	void setVersion(const QString& szVersion);
	void setScmBranchVersion(const QString& szVersion);
	void setScmTagVersion(const QString& szVersion);

protected:
	bool doExecute();

private:
	bool prepareSources(const QSharedPointer<Formula>& pFormula, const QDir& dirWorkingCopy);
	bool configureVersion(const QSharedPointer<Formula>& pFormula, const QDir& dirWorkingCopy);
	const QString& getConfigureVersion() const;

private:
	QString m_szPackageName;
	QString m_szVersion;
	QString m_szScmBranchVersion;
	QString m_szScmTagVersion;
};

#endif /* SRC_COMMANDS_COMMANDPREPARE_H_ */
