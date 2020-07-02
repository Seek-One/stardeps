//
// Created by ebeuque on 02/07/2020.
//

#include "ConnectorSVN.h"

ConnectorSVN::ConnectorSVN(const Environment& env) : AbstractConnector(env)
{

}

ConnectorSVN::~ConnectorSVN()
{

}

bool ConnectorSVN::svn_checkout(const QString& szURL, const QDir& dirWorkingDirectory)
{
    QStringList listArgs;
    qDebug("[svn] Checkout sources to version %s", qPrintable(szURL));
    listArgs.append("checkout");
    listArgs.append(szURL);
    listArgs.append(dirWorkingDirectory.path());
    return m_shell.runCommand(m_env.getSVNExe(), listArgs);
}

bool ConnectorSVN::svn_update(const QDir& dirWorkingDirectory)
{
    QStringList listArgs;
    qDebug("[svn] Updating sources");
    listArgs.append("update");
    return m_shell.runCommand(m_env.getSVNExe(), listArgs, dirWorkingDirectory);
}