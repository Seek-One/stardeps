/*
 * AbstractPackageCommand.h
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_ABSTRACTPACKAGECOMMAND_H_
#define SRC_COMMANDS_ABSTRACTPACKAGECOMMAND_H_

#include <QDir>

#include "Variable/VariableList.h"

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
	QDir getSourceArchivePackageDir() const;
	QDir getSourcePackageDir() const;
	QDir getBuildPackageDir() const;
	QDir getReleasePackageDir() const;

protected:
	bool doInitDictVars(VariableList& dictVars);
	bool doReplaceVariable(const QString& szText, const VariableList& dictVars, QString& szTextOut);
	bool doReplaceVariable(const QString& szText, const VariableList& dictVars1, const VariableList& dictVars2, QString& szTextOut);
	bool doPrepareCommand(const QString& szCmd, QString& szCmdOut);
	bool doRunCommand(const QString& szCmd, const QDir& dirWorkingDirectory);
	bool doRunCommands(const QStringList& listCmd, const QDir& dirWorkingDirectory);
	bool doChangeDirectoryAction(const QString& szDirectory);
	bool doCopyFilesAction(const QStringList& listSources, const QString& szDestination);
	bool doCopyFilesAction(const QString& szSource, const QString& szDestination);
	bool doCopyFilesAction(const QDir& dirSource, const QString& szPattern, const QDir& dirDestination);

	bool doExecuteStep(const QString& szStep, const QDir& dirWorkingDirectory);

	virtual bool doProcessArgument(int i, const QString& szArg);

	PackageCommandEnvironment* getPackageCommandEnvironment() const;
	const QSharedPointer<Formula>& getFormula() const;

	Environment& getEnv() const;
    
private:
    void parseCommand(const QString& szCmd, QStringList& listOutTokens) const;
};

#endif /* SRC_COMMANDS_ABSTRACTPACKAGECOMMAND_H_ */
