/*
 * CreateEnvCommand.cpp
 *
 *  Created on: 11 mars 2020
 *      Author: ebeuque
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QFile>

#include "Global/QApplicationSettings.h"

#include "CreateEnvCommand.h"

CreateEnvCommand::CreateEnvCommand()
{

}

CreateEnvCommand::~CreateEnvCommand()
{

}

bool CreateEnvCommand::execute(const QString& szVEPath, const QString& szPlatform)
{
	bool bRes = true;

	QString szHost;
	QString szCompiler;
	QString szArch;

	// Detect compiler
#ifdef WIN32
	szCompiler = "msbuild.exe";
#elif defined(APPLE)
	szCompiler = "xcodebuild";
#else
	szCompiler = "gcc";
#endif


	QDir dirVE = szVEPath;
	QString szFilePath = dirVE.filePath("ve.env");

	QDir dstPath = szVEPath;

	QFile file(szFilePath);
	if(!file.exists()){
		bRes = file.open(QIODevice::WriteOnly);
		if(bRes){
			file.write(QString("COMPILER=%0\n").arg(szCompiler).toUtf8());
			file.close();
		}else{
			qCritical("[createenv] Unable to create environment file");
		}
	}else{
		qCritical("[createenv] Environment file already exists");
	}

	return bRes;
}
