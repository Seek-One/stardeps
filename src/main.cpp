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

#include "CommandsExecutor/CommandsExecutor.h"

static int processCommandVersion();

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
        if(szCommand == "--version"){
            iRes = processCommandVersion();
        }else if(szCommand == "--help"){
            bShowUsage = true;
        }else{

            QString szArg;
            QString szTmp;

            // Parse for global option
            for(int i=0; i<argc; i++) {
                szArg = argv[i];
                if (szArg.startsWith("--verbose")) {
                    szTmp = szArg.mid(10);
                    QApplicationSettings::setApplicationVerboseMode(szTmp == "full" ? 1 : 0);
                }
                if (szArg.startsWith("--formulas-dir")) {
                    szTmp = szArg.mid(15);
                    QApplicationSettings::setApplicationCustomFormulasDir(szTmp);
                }
            }

        	bool bRes;
        	CommandsExecutor executor;
        	bRes = executor.prepareCommands(szCommand, argc+2, argv+2);
        	if(bRes){
        		bRes = executor.executeCommands();
        		if(!bRes){
        			iRes = -1;
        		}
        	}else{
        		bShowUsage = true;
        	}
        }
    }

    // Show help
    if(bShowUsage){
		qDebug("Usage: %s command [args]", argv[0]);
        qDebug(" ");
        qDebug("  LIST OF ARGUMENTS");
        qDebug("       --version ");
        qDebug("             display application version");
        qDebug("       --help ");
        qDebug("             show help");
        qDebug("       --verbose=[normal,full]");
        qDebug("             set level of verbosity.");
        qDebug(" ");
		qDebug("  LIST OF COMMANDS: ENVIRONMENT");
		qDebug("       createenv TARGET_PLATFORM");
		qDebug("             create an environment directory and a ve.env file with useful environment variables.");
		//qDebug("       listenv");
        qDebug(" ");
        qDebug("  LIST OF COMMANDS: PACKAGE");
		qDebug("       prepare PACKAGE_NAME");
		qDebug("             get the sources of the package in the sources directory.");
		qDebug("       configure PACKAGE_NAME");
		qDebug("             configure the sources of the package in the build directory.");
		qDebug("       build PACKAGE_NAME");
		qDebug("             run the build command in the build directory.");
		qDebug("       install PACKAGE_NAME");
		qDebug("             install the generated package files in the release directory.");
		qDebug(" ");
        qDebug("  LIST OF ARGUMENTS FOR PACKAGE COMMANDS");
        qDebug("       --formulas-dir=DIR");
        qDebug("             set DIR as formula dir.");
        qDebug(" ");
        qDebug("       --pkg-version=VERSION");
        qDebug("             define the version of the package to build.");
        qDebug("       --pkg-option=OPTION");
        qDebug("             tell use the option specified in the formula of the package. You can use this option multiple times.");
        qDebug(" ");
		qDebug("       --scm-tag-version=VERSION");
		qDebug("             define the tag version in the SCM to use.");
		qDebug("       --scm-branch-version=VERSION");
		qDebug("             define the branch version in the SCM to use.");
    }

	return iRes;
}

static int processCommandVersion()
{
    qDebug("%s", APPLICATION_VERSION);
    return 0;
}
