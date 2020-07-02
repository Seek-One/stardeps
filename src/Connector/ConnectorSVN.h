//
// Created by ebeuque on 02/07/2020.
//

#ifndef STARDEPS_CONNECTORSVN_H
#define STARDEPS_CONNECTORSVN_H

#include "AbstractConnector.h"

class ConnectorSVN : public AbstractConnector
{
public:
    ConnectorSVN(const Environment& env);
    virtual ~ConnectorSVN();

    bool svn_checkout(const QString& szURL, const QDir& dirWorkingDirectory);
    bool svn_update(const QDir& dirWorkingDirectory);
};


#endif //STARDEPS_CONNECTORSVN_H
