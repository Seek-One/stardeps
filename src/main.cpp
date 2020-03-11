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


QStringList getWSDLFileNames(const char* szPathSrc);
void copyPath(QString src, QString dst);
bool removeDir(const QString & dirName);

int main(int argc, char **argv)
{
	int iRes = 0;

	QCoreApplication::setApplicationName(APPLICATION_NAME);
	QCoreApplication::setApplicationVersion(APPLICATION_VERSION);

	QCoreApplication a(argc, argv);

	if(argc < 2){
		qDebug("Usage: %s command [args]", argv[0]);
		return -1;
	}

	return iRes;
}

