/*
 * EnvironmentLoader.cpp
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#include <QDir>

#include "EnvironmentDefs.h"

#include "EnvironmentLoader.h"

EnvironmentLoader::EnvironmentLoader()
{

}

EnvironmentLoader::~EnvironmentLoader()
{

}

bool EnvironmentLoader::loadEnvironmentVars(Environment& env)
{
	bool bRes;

	QDir dirVE = env.getVirtualEnvironmentPath();
	QString szFilePath = dirVE.filePath(VE_FILE);

	QByteArray readData;
	QString szLine;
	QStringList listTokens;

	qCritical("[env] Loading environment");

	QFile file(szFilePath);
	bRes = file.exists();
	if(bRes){
		bRes = file.open(QIODevice::ReadOnly);
		if(bRes){
			do {
				readData = file.readLine();
				if(readData.size() > 0){
					szLine = QString::fromUtf8(readData);
					listTokens = szLine.split('=');
					if(listTokens.count() == 2){
						env.setEnvVar(listTokens[0], listTokens[1].remove('\n').remove('\r'));
					}else if(listTokens.count() == 2){
						env.setEnvVar(listTokens[0], QString());
					}
				}
			}while(readData.size() != 0);

			file.close();
		}else{
			qCritical("[env] Unable to open environment file");
		}
	}else{
		qCritical("[env] No environment file found");
	}

	// Initialize platform type
	if(bRes){
		QString szTmp = env.getEnvVar(VE_VAR_TARGET_PLATFORM);
		Platform::Type iType = Platform::fromString(szTmp);
		env.setPlatformType(iType);
	}

	return bRes;
}
