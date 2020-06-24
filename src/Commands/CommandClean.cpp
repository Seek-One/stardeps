//
// Created by ebeuque on 24/06/2020.
//

#include "CommandClean.h"

CommandClean::CommandClean() : AbstractPackageCommand("clean")
{

}

CommandClean::~CommandClean()
{

}

bool CommandClean::doExecute()
{
    bool bRes;

    // Execute steps
    bRes = doExecuteStep("clean", getRootPackageDir());

    if(bRes){
        bRes = removeDir(getRootPackageDir().absolutePath());
        if(!bRes){
            qCritical("[clean] Error while cleaning directory");
        }
    }

    return bRes;
}

bool CommandClean::removeDir(const QString& szDirName)
{
    bool bResult = true;

    QDir dir(szDirName);
    if (dir.exists(szDirName)){
        QFileInfoList fileInfoList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
        QFileInfoList::const_iterator iter;
        for(iter = fileInfoList.constBegin(); iter != fileInfoList.constEnd(); ++iter){
            const QFileInfo& fileInfo = (*iter);
            if (fileInfo.isDir()) {
                bResult = removeDir(fileInfo.absoluteFilePath());
            }else{
                bResult = QFile::remove(fileInfo.absoluteFilePath());
            }

            if (!bResult) {
                return bResult;
            }
        }
        qDebug("[clean] Cleaning directory %s", qPrintable(dir.path()));
        bResult = dir.rmdir(szDirName);
    }
    return bResult;
}