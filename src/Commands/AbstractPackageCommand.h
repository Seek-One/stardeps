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

class AbstractPackageCommand : public AbstractCommand
{
public:
	AbstractPackageCommand(const QString& szLabel);
	virtual ~AbstractPackageCommand();

	void setPackageName(const QString& szPackageName);
	void setVersion(const QString& szVersion);

	void addOption(const QString& szOption);
	const QStringList& getOptions() const;

	QString getPackageNameVersion() const;
	QDir getRootPackageDir() const;
	QDir getSourcePackageDir() const;
	QDir getBuildPackageDir() const;
	QDir getReleasePackageDir() const;

protected:
	bool doPrepareCommand(const QString& szCmd, QString& szCmdOut);
	bool doRunCommand(const QString& szCmd, const QDir& dirWorkingDirectory);

protected:
	QString m_szPackageName;
	QString m_szVersion;

	QStringList m_listOptions;
};

#endif /* SRC_COMMANDS_ABSTRACTPACKAGECOMMAND_H_ */
