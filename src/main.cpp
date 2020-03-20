/*
 * main.cpp
 *
 *  Created on: 11 march 2020
 *      Author: ebeuque
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_VERSION_H
#include <version.h>
#endif

#include <QCoreApplication>
#include <QDir>

#include "Global/QApplicationSettings.h"

#include <Commands/CommandCreateEnv.h>
#include "Commands/CommandPrepare.h"
#include "Commands/CommandConfigure.h"
#include "Commands/CommandBuild.h"
#include "Commands/CommandInstall.h"

static int processCommandVersion();
static int processCommandCreateEnv(int argc, char **argv);
static int processCommandPrepare(int argc, char **argv);
static int processCommandConfigure(int argc, char **argv);
static int processCommandBuild(int argc, char **argv);
static int processCommandInstall(int argc, char **argv);

int main(int argc, char **argv)
{
	int iRes = 0;

	QCoreApplication::setApplicationName(APPLICATION_NAME);
	QCoreApplication::setApplicationVersion(APPLICATION_VERSION);

	QCoreApplication a(argc, argv);

	// Application directory
#if defined(WIN32) //For windows in debug mode or not
	QString szApplicationDir = QCoreApplication::applicationDirPath();
#else // For Linux in debug mode or not
	QString szApplicationDir = QCoreApplication::applicationDirPath() + "/../share/" + APPLICATION_PACKAGE_NAME; // Add from the binary directory
	QDir dataDir = QDir(szApplicationDir);
	if(!dataDir.exists()) { //For dev environment
		szApplicationDir = QCoreApplication::applicationDirPath();
	}
#endif
	QApplicationSettings::setApplicationDir(QDir(szApplicationDir));

	// Application data directory
	QDir dirApplicationData = QDir(".");
	// If data directory exists in current directory
	if(dirApplicationData.exists("data")){
		dirApplicationData = QDir("./data");
	}else{
#ifdef WIN32
		dirApplicationData = QCoreApplication::applicationDirPath();
#else
		// For Linux in debug mode or not
		dirApplicationData = QCoreApplication::applicationDirPath() + "/../share/" + APPLICATION_PACKAGE_NAME; // Add from the binary directory
#endif
	}
	QApplicationSettings::setApplicationDataDir(dirApplicationData);

    bool bShowUsage = false;

	if(argc < 2){
        bShowUsage = true;
	}

    if(!bShowUsage){
        QString szCommand = argv[1];
        if(szCommand == "version"){
            iRes = processCommandVersion();
        }else if(szCommand == "help"){
            bShowUsage = true;
        }else if(szCommand == "createenv"){
            iRes = processCommandCreateEnv(argc, argv);
        }else if(szCommand == "prepare"){
            iRes = processCommandPrepare(argc, argv);
        }else if(szCommand == "configure"){
            iRes = processCommandConfigure(argc, argv);
        }else if(szCommand == "build"){
            iRes = processCommandBuild(argc, argv);
        }else if(szCommand == "install"){
            iRes = processCommandInstall(argc, argv);
        }else{
            bShowUsage = true;
        }
    }

    // Show help
    if(bShowUsage){
		qDebug("Usage: %s command [args]", argv[0]);
		qDebug("       createenv TARGET_PLATFORM");
		qDebug("       listenv");
		qDebug("       prepare PACKAGE_NAME [--version=[VERSION]]");
		qDebug("       configure PACKAGE_NAME [--version=[VERSION]]");
		qDebug("       install PACKAGE_NAME");
		qDebug("       version");
    }

	return iRes;
}

static int processCommandVersion()
{
    qDebug("%s", APPLICATION_VERSION);
    return 0;
}

static int processCommandCreateEnv(int argc, char **argv)
{
	if(argc < 3){
		qCritical("[main] Missing TARGET_PLATFORM argument");
		return -1;
	}

	CommandCreateEnv cmd;
	cmd.setVirtualEnvironmentPath(QDir("."));
	cmd.setTargetPlatform(argv[2]);
	bool bRes = cmd.execute();
	if(!bRes){
		return -1;
	}
	return 0;
}

static int processCommandPrepare(int argc, char **argv)
{
	if(argc < 3){
		qCritical("[main] Missing PACKAGE_NAME argument");
		return -1;
	}

	CommandPrepare cmd;
	cmd.setVirtualEnvironmentPath(QDir("."));
	cmd.setPackageName(argv[2]);

	for(int i=3; i<argc; i++)
	{
		QString szArg = argv[i];
		if(szArg.startsWith("--version=")){
			cmd.setVersion(szArg.mid(10));
		}else if(szArg.startsWith("--scm-branch-version=")){
			cmd.setScmBranchVersion(szArg.mid(21));
		}else if(szArg.startsWith("--scm-tag-version=")){
			cmd.setScmTagVersion(szArg.mid(18));
		}
	}

	bool bRes = cmd.execute();
	if(!bRes){
		return -1;
	}
	return 0;
}

static int processCommandConfigure(int argc, char **argv)
{
	if(argc < 3){
		qCritical("[main] Missing PACKAGE_NAME argument");
		return -1;
	}

	CommandConfigure cmd;
	cmd.setVirtualEnvironmentPath(QDir("."));
	cmd.setPackageName(argv[2]);

	for(int i=3; i<argc; i++)
	{
		QString szArg = argv[i];
		if(szArg.startsWith("--version=")){
			cmd.setVersion(szArg.mid(10));
		}
	}

	bool bRes = cmd.execute();
	if(!bRes){
		return -1;
	}
	return 0;
}

static int processCommandBuild(int argc, char **argv)
{
	if(argc < 3){
		qCritical("[main] Missing PACKAGE_NAME argument");
		return -1;
	}

	CommandBuild cmd;
	cmd.setVirtualEnvironmentPath(QDir("."));
	cmd.setPackageName(argv[2]);

	for(int i=3; i<argc; i++)
	{
		QString szArg = argv[i];
		if(szArg.startsWith("--version=")){
			cmd.setVersion(szArg.mid(10));
		}
	}

	bool bRes = cmd.execute();
	if(!bRes){
		return -1;
	}
	return 0;
}

static int processCommandInstall(int argc, char **argv)
{
	if(argc < 3){
		qCritical("[main] Missing PACKAGE_NAME argument");
		return -1;
	}

	CommandInstall cmd;
	cmd.setVirtualEnvironmentPath(QDir("."));
	cmd.setPackageName(argv[2]);

	for(int i=3; i<argc; i++)
	{
		QString szArg = argv[i];
		if(szArg.startsWith("--version=")){
			cmd.setVersion(szArg.mid(10));
		}
	}

	bool bRes = cmd.execute();
	if(!bRes){
		return -1;
	}
	return 0;
}
