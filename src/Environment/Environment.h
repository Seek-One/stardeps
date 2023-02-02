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

#include "Platform/Platform.h"
#include "Variable/VariableList.h"

typedef	VariableList EnvironmentVars;

class Environment {
public:
	Environment();
	virtual ~Environment();

	// Virtual environment path
	void setVirtualEnvironmentPath(const QDir& dir);
	const QDir& getVirtualEnvironmentPath() const;

	bool isPerPackageMode() const;

	QDir getVirtualEnvironmentSourceDir() const;
	QDir getVirtualEnvironmentBuildDir() const;
	QDir getVirtualEnvironmentReleaseDir() const;

	// Platform type
	void setPlatformType(Platform::Type iPlatformType);
	Platform::Type getPlatformType() const;
	QString getPlatformTypeName() const;

	// Env vars
	void setEnvVar(const QString& szName, const QString& szValue);
	QString getEnvVar(const QString& szName, const QString& szDefaultValue = QString()) const;
	void removeEnvVar(const QString& szName);
	const EnvironmentVars& getVars() const;

	// Get some var
	QString getGitExe() const;
	QString getHgExe() const;
    QString getSVNExe() const;

	void print();

private:
	QDir m_dirVE;

	Platform::Type m_iPlatformType;

	EnvironmentVars m_listVars;
};

#endif /* SRC_ENVIRONMENT_ENVIRONMENT_H_ */
