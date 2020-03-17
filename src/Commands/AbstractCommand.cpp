/*
 * AbstractCommand.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include <QProcess>
#include <QEventLoop>

#include "AbstractCommand.h"

AbstractCommand::AbstractCommand()
{

}

AbstractCommand::~AbstractCommand()
{

}

void AbstractCommand::setVirtualEnvironmentPath(const QString& szPath)
{
	m_szVEPath = szPath;
}
