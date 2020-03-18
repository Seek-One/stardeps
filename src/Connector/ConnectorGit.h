/*
 * ConnectorGit.h
 *
 *  Created on: 17 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_CONNECTOR_CONNECTORGIT_H_
#define SRC_CONNECTOR_CONNECTORGIT_H_

#include "AbstractConnector.h"

class ConnectorGit : public AbstractConnector {
public:
	ConnectorGit(const Environment& env);
	virtual ~ConnectorGit();

	void setGitCmd(const QString& szCmd);

	bool git_clone(const QString& szURL, const QDir& dirWorkingDirectory);
	bool git_pull(const QDir& dirWorkingDirectory);
	bool git_checkout(const QString& szVersion, const QDir& dirWorkingDirectory);

private:
	QString m_szGitCmd;
};

#endif /* SRC_CONNECTOR_CONNECTORGIT_H_ */
