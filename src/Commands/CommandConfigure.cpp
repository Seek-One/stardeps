/*
 * CommandConfigure.cpp
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#include "CommandConfigure.h"

CommandConfigure::CommandConfigure() : AbstractPackageCommand("configure")
{

}

CommandConfigure::~CommandConfigure()
{

}


bool CommandConfigure::doExecute()
{
	bool bRes;

	// Load formula
	QSharedPointer<Formula> pFormula;
	bRes = loadFormula(m_szPackageName, pFormula);

	return bRes;
}
