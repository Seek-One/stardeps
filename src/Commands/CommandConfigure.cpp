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

	// Execute commands
	if(bRes){
		const FormulaRecipeList& listRecipes = pFormula->getRecipeList();
		QString szTargetPlateform = m_env.getPlatformTypeName();
		if(listRecipes.contains(szTargetPlateform)){
			const FormulaRecipe& recipe = listRecipes.value(szTargetPlateform);
			const FormulaCommands& listCommands = recipe.getConfigureCommands();

			FormulaCommands::const_iterator iter_cmd;
			for(iter_cmd = listCommands.constBegin(); iter_cmd != listCommands.constEnd(); ++iter_cmd)
			{
				bRes = doRunCommand((*iter_cmd), getBuildPackageDir());
				if(!bRes){
					qCritical("[configure] aborting configure due to error");
					break;
				}
			}
		}
	}

	return bRes;
}