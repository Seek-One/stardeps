/*
 * QApplicationSettings.cpp
 *
 *  Created on: 11 mars 2020
 *      Author: ebeuque
 */

#include "QApplicationSettings.h"

QDir QApplicationSettings::g_applicationDir;
QDir QApplicationSettings::g_applicationDataDir;

QApplicationSettings::QApplicationSettings()
{

}

QApplicationSettings::~QApplicationSettings()
{

}

const QDir& QApplicationSettings::applicationDir()
{
	return g_applicationDir;
}

void QApplicationSettings::setApplicationDir(const QDir& dir)
{
	g_applicationDir = dir;
}

const QDir& QApplicationSettings::applicationDataDir()
{
	return g_applicationDataDir;
}

void QApplicationSettings::setApplicationDataDir(const QDir& dir)
{
	g_applicationDataDir = dir;
}


QDir QApplicationSettings::applicationFormulasPath()
{
	return QDir(g_applicationDataDir.filePath("formulas"));
}
