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
			if (fileInfo.isSymLink()) {
				bResult = QFile::remove(fileInfo.absoluteFilePath());
				qCritical("[clean] Error while deleting symbolic link file: %s", qPrintable(fileInfo.absoluteFilePath()));
			}else if (fileInfo.isDir()) {
                bResult = removeDir(fileInfo.absoluteFilePath());
            }else{
                bResult = QFile::remove(fileInfo.absoluteFilePath());
				qCritical("[clean] Error while deleting file: %s", qPrintable(fileInfo.absoluteFilePath()));
            }

            if (!bResult) {
                return bResult;
            }
        }
        qDebug("[clean] Cleaning directory %s", qPrintable(dir.path()));
        bResult = dir.rmdir(szDirName);
        if(!bResult){
			qCritical("[clean] Error while deleting directory: %s", qPrintable(szDirName));
        }
    }
    return bResult;
}