//
// Created by ebeuque on 11/12/2020.
//

#ifndef STARDEPS_CONNECTORMERCURIAL_H
#define STARDEPS_CONNECTORMERCURIAL_H

#include "AbstractConnector.h"

class ConnectorMercurial : public AbstractConnector
{
public:
	ConnectorMercurial(const Environment& env);
	virtual ~ConnectorMercurial();

	bool hg_clone(const QString& szURL, const QDir& dirWorkingDirectory);
	bool hg_update(const QDir& dirWorkingDirectory);
	bool hg_checkout(const QString& szVersion, const QDir& dirWorkingDirectory);

private:
	QString m_szHgCmd;
};


#endif //STARDEPS_CONNECTORMERCURIAL_H
