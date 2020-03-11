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

static int processVersionCommand();

int main(int argc, char **argv)
{
	int iRes = 0;

	QCoreApplication::setApplicationName(APPLICATION_NAME);
	QCoreApplication::setApplicationVersion(APPLICATION_VERSION);

	QCoreApplication a(argc, argv);

	if(argc < 2){
		qDebug("Usage: %s command [args]", argv[0]);
		qDebug("       createenv []");
		qDebug("       install package-name");
		qDebug("       version");
		return -1;
	}

    QString szCommand = argv[1];

    if(szCommand == "version"){
        iRes = processVersionCommand();
    }

	return iRes;
}


static int processVersionCommand()
{
    qDebug("%s", APPLICATION_VERSION);
    return 0;
}
