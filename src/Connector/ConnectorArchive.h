/*
 * ConnectorGit.h
 *
 *  Created on: 16 juin 2020
 *      Author: alavier
 */

#ifndef SRC_CONNECTOR_CONNECTORARCHIVE_H_
#define SRC_CONNECTOR_CONNECTORARCHIVE_H_

#include "AbstractConnector.h"

class ConnectorArchive : public AbstractConnector {
public:
    ConnectorArchive(const Environment& env);
    virtual ~ConnectorArchive();

    bool archive_download(const QString& szURL, const QDir& dirWorkingDirectory);

private:
    QString m_szGitCmd;
};

#endif /* SRC_CONNECTOR_CONNECTORARCHIVE_H_ */
