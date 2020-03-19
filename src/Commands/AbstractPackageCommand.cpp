/*
 * AbstractPackageCommand.cpp
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#include "AbstractPackageCommand.h"

AbstractPackageCommand::AbstractPackageCommand(const QString& szLabel) : AbstractCommand(szLabel)
{

}

AbstractPackageCommand::~AbstractPackageCommand()
{

}

void AbstractPackageCommand::setPackageName(const QString& szPackageName)
{
	m_szPackageName = szPackageName;
}

void AbstractPackageCommand::setVersion(const QString& szVersion)
{
	m_szVersion = szVersion;
}

