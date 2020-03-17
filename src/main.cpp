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
#include "Commands/CommandInstall.h"

static int processCommandVersion();
static int processCommandCreateEnv(int argc, char **argv);
static int processCommandPrepare(int argc, char **argv);
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
        }else if(szCommand == "install"){
            iRes = processCommandInstall(argc, argv);
        }else{
            bShowUsage = true;
        }
    }

    // Show help
    if(bShowUsage || (iRes == -1)){
		qDebug("Usage: %s command [args]", argv[0]);
		qDebug("       createenv");
		qDebug("       listenv");
		qDebug("       prepare package-name [--version=[VERSION]]");
		qDebug("       install package-name");
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
	bool bRes = CommandCreateEnv::execute(".", argv[2]);
	if(!bRes){
		return -1;
	}
	return 0;
}

static int processCommandPrepare(int argc, char **argv)
{
	CommandPrepare cmd;
	cmd.setVirtualEnvironmentPath(".");
	cmd.setPackageName(argv[2]);

	bool bRes = cmd.execute();
	if(!bRes){
		return -1;
	}
	return 0;
}

static int processCommandInstall(int argc, char **argv)
{
	bool bRes = CommandInstall::execute(".", argv[2]);
	if(!bRes){
		return -1;
	}
	return 0;
}
