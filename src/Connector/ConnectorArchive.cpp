/*
* ConnectorGit.cpp
*
*  Created on: 16 juin 2020
*      Author: alavier
*/

#include "ConnectorArchive.h"
#include "Environment/EnvironmentDefs.h"

ConnectorArchive::ConnectorArchive(const Environment& env) : AbstractConnector(env)
{

}

ConnectorArchive::~ConnectorArchive()
{

}

bool ConnectorArchive::archive_download(const QString& szURL, const QDir& dirWorkingDirectory)
{
    bool bRes = false;
    
    QString szFileName;
    QString szDirectoryPath = dirWorkingDirectory.path();
    
    if(!szDirectoryPath.endsWith("/")){
        szDirectoryPath.append("/");
    }

    if(szURL.endsWith("tar.gz") || szURL.endsWith("tar.gz/")){
        szFileName = "file.tar.gz";
    }
    
    QStringList listArgs;
    qDebug("[archive] Getting sources: %s to %s", qPrintable(szURL), qPrintable(dirWorkingDirectory.path()));
    listArgs.append("-O");
    listArgs.append(szDirectoryPath + szFileName);
    listArgs.append(szURL);
    if(m_shell.runCommand(m_env.getEnvVar(VE_VAR_WGET), listArgs)){
        listArgs.clear();
        listArgs.append("xvzf");
        listArgs.append(szDirectoryPath + szFileName);
        listArgs.append("-C");
        listArgs.append(szDirectoryPath);
        listArgs.append("--strip-components");
        listArgs.append("1");
        bRes = m_shell.runCommand(m_env.getEnvVar(VE_VAR_TAR), listArgs);
    }
    return bRes;
}
