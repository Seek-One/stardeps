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
	ConnectorGit();
	virtual ~ConnectorGit();

	bool git_clone(const QString& szURL, const QDir& dirWorkingDirectory);
	bool git_pull(const QDir& dirWorkingDirectory);
};

#endif /* SRC_CONNECTOR_CONNECTORGIT_H_ */
