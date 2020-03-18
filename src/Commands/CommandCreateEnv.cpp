/*
 * CommandCreateEnv.cpp
 *
 *  Created on: 11 mars 2020
 *      Author: ebeuque
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QFile>

#include "Global/QApplicationSettings.h"

#include <Commands/CommandCreateEnv.h>

CommandCreateEnv::CommandCreateEnv()
{
	m_bNeedEnvVars = false;
}

CommandCreateEnv::~CommandCreateEnv()
{

}

bool CommandCreateEnv::doExecute()
{
	bool bRes = true;

	QString szHost;
	QString szArch;

	Environment env;

	if(bRes){
		bRes = findGit(env);
	}

	if(bRes){
		bRes = findCompiler(env);
	}

	QDir dirVE = getVirtualEnvironmentPath();
	QString szFilePath = dirVE.filePath("ve.env");

	QDir dstPath = getVirtualEnvironmentPath();

	QString szLine;
	QFile file(szFilePath);
	if(!file.exists()){
		bRes = file.open(QIODevice::WriteOnly);
		if(bRes){
			const EnvironmentVars& listVars = env.getVars();
			EnvironmentVars::const_iterator iter;
			for(iter = listVars.constBegin(); iter != listVars.constEnd(); ++iter){
				szLine = QString("%0=%1\n").arg(iter.key()).arg(iter.value());
				file.write(szLine.toUtf8());
			}
			file.close();
		}else{
			qCritical("[createenv] Unable to create environment file");
		}
	}else{
		qCritical("[createenv] Environment file already exists");
	}

	return bRes;
}

bool CommandCreateEnv::findGit(Environment& env)
{
	env.setEnvVar("GIT", "git");
	return true;
}

bool CommandCreateEnv::findCompiler(Environment& env)
{
	QString szCompiler;

	// Detect compiler
#ifdef WIN32
	szCompiler = "msbuild.exe";
#elif defined(APPLE)
	szCompiler = "xcodebuild";
#else
	szCompiler = "gcc";
#endif

	env.setEnvVar("COMPILER", szCompiler);
	return true;
}
