/*
 * AbstractPackageCommand.h
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_ABSTRACTPACKAGECOMMAND_H_
#define SRC_COMMANDS_ABSTRACTPACKAGECOMMAND_H_

#include <QDir>

#include "AbstractCommand.h"

class PackageCommandEnvironment;

class AbstractPackageCommand : public AbstractCommand
{
public:
	AbstractPackageCommand(const QString& szLabel);
	virtual ~AbstractPackageCommand();

	const QString& getPackageName() const;
	const QString& getPackageVersion() const;
	const QStringList& getPackageOptions() const;
	QString getPackageNameVersion() const;

	QDir getRootPackageDir() const;
	QDir getSourcePackageDir() const;
	QDir getBuildPackageDir() const;
	QDir getReleasePackageDir() const;

protected:
	bool doPrepareCommand(const QString& szCmd, QString& szCmdOut);
	bool doRunCommand(const QString& szCmd, const QDir& dirWorkingDirectory);

	virtual bool doProcessArgument(int i, const QString& szArg);

	PackageCommandEnvironment* getPackageCommandEnvironment() const;
	const QSharedPointer<Formula>& getFormula() const;

	Environment& getEnv() const;
};

#endif /* SRC_COMMANDS_ABSTRACTPACKAGECOMMAND_H_ */
