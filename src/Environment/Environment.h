/*
 * Environment.h
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_ENVIRONMENT_ENVIRONMENT_H_
#define SRC_ENVIRONMENT_ENVIRONMENT_H_

#include <QString>
#include <QDir>
#include <QMap>

#define VE_FILE "ve.env"

typedef	QMap<QString, QString> EnvironmentVars;

class Environment {
public:
	Environment();
	virtual ~Environment();

	// Virtual environment path
	void setVirtualEnvironmentPath(const QDir& dir);
	const QDir& getVirtualEnvironmentPath() const;

	// Env vars
	void setEnvVar(const QString& szName, const QString& szValue);
	QString getEnvVar(const QString& szName, const QString& szDefaultValue = QString()) const;
	const EnvironmentVars& getVars() const;

	// Get some var
	QString getGitExe() const;

	void print();

private:
	QDir m_dirVE;

	EnvironmentVars m_listVars;
};

#endif /* SRC_ENVIRONMENT_ENVIRONMENT_H_ */
