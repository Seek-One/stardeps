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

bool ConnectorArchive::archive_download(const QString& szURL, const QDir& dirWorkingDirectory, QString& szOutputFilePath, const QString& szOutputFileName) {
    bool bRes = false;

    QString szFileName;

    if (szOutputFileName.isEmpty()) {
        if (szURL.endsWith("tar.gz") || szURL.endsWith("tar.gz/")) {
            szFileName = "file.tar.gz";
        }
    }else{
        szFileName = szOutputFileName;
    }

    QString szFilePath = dirWorkingDirectory.filePath(szFileName);

    qDebug("[archive] Getting sources: %s to %s", qPrintable(szURL), qPrintable(dirWorkingDirectory.path()));
    QStringList listArgs;
    listArgs.append("-O");
    listArgs.append(szFilePath);
    listArgs.append(szURL);

    bRes = m_shell.runCommand(m_env.getEnvVar(VE_VAR_WGET), listArgs);
    if(bRes) {
        szOutputFilePath = szFilePath;
    }else{
        qCritical("[archive] Unable to get archive from %s", qPrintable(szURL));
    }

    return bRes;
}

bool ConnectorArchive::archive_extract(const QString& szArchiveFile, const QDir& dirWorkingDirectory)
{
    bool bRes = false;

    QString szCommand;
    QStringList listArgs;

    // Tar gz extraction
    if(szArchiveFile.endsWith("tar.gz")) {
        szCommand = m_env.getEnvVar(VE_VAR_TAR);

        listArgs.append("xvzf");
        listArgs.append(szArchiveFile);
        listArgs.append("-C");
        listArgs.append(dirWorkingDirectory.path());
        listArgs.append("--strip-components");
        listArgs.append("1");
    }

    if(!szCommand.isEmpty()) {
        bRes = m_shell.runCommand(szCommand, listArgs);
    }

    return bRes;
}