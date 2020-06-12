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

#include "Platform/Platform.h"
#include "Environment/EnvironmentDefs.h"

#include "CommandCreateEnv.h"

CommandCreateEnv::CommandCreateEnv() : AbstractCommand("createenv")
{

}

CommandCreateEnv::~CommandCreateEnv()
{

}

void CommandCreateEnv::setTargetPlatform(const QString& szTargetPlatform)
{
	m_szTargetPlatform = szTargetPlatform;
}


bool CommandCreateEnv::doProcessArgument(int i, const QString& szArg)
{
	if(i == 0){
		setTargetPlatform(szArg);
	}
	return AbstractCommand::doProcessArgument(i, szArg);
}

bool CommandCreateEnv::doExecute()
{
	bool bRes = true;

	QString szHost;
	QString szArch;

	Environment env;
	env.setEnvVar(VE_VAR_TARGET_PLATFORM, m_szTargetPlatform);
	Platform::Type iPlateformType = Platform::fromString(m_szTargetPlatform);
	env.setPlatformType(iPlateformType);

	if(bRes){
		bRes = findGit(env);
	}
	if(bRes){
		bRes = findMake(env);
	}
	if(bRes){
		bRes = findRSync(env);
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
#ifdef WIN32
	if(QFile::exists("/usr/bin/git")){
		env.setEnvVar(VE_VAR_GIT, "/usr/bin/git");
	}else{
		qWarning("[env] git is not found");
	}
#else
	if(QFile::exists("/usr/bin/git")){
		env.setEnvVar(VE_VAR_GIT, "/usr/bin/git");
	}else{
		env.setEnvVar(VE_VAR_GIT, "/usr/bin/git");
	}
#endif
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
	if(QFile::exists("/usr/bin/gcc")){
		env.setEnvVar(VE_VAR_COMPILER, "/usr/bin/gcc");
	}else{
		env.setEnvVar(VE_VAR_COMPILER, "gcc");
	}
#endif
	return true;
}

bool CommandCreateEnv::findMake(Environment& env)
{
	if(QFile::exists("/usr/bin/make")){
		env.setEnvVar(VE_VAR_MAKE, "/usr/bin/make");
	}else{
		env.setEnvVar(VE_VAR_MAKE, "make");
	}
	return true;
}

bool CommandCreateEnv::findRSync(Environment& env)
{
	if(QFile::exists("/usr/bin/rsync")){
		env.setEnvVar(VE_VAR_RSYNC, "/usr/bin/rsync");
	}else{
		env.setEnvVar(VE_VAR_RSYNC, "rsync");
	}
	return true;
}
