/*
 * CommandInstall.cpp
 *
 *  Created on: 11 mars 2020
 *      Author: ebeuque
 */

#include "CommandInstall.h"

CommandInstall::CommandInstall() : AbstractPackageCommand("install")
{

}

CommandInstall::~CommandInstall()
{

}

bool CommandInstall::doExecute()
{
	bool bRes = true;

    // Execute steps
    if(bRes){
        bRes = doExecuteStep("install", getBuildPackageDir());
    }

	// Execute commands
	if(bRes){
		const FormulaRecipeList& listRecipes = getFormula()->getRecipeList();
		QString szTargetPlateform = getEnv().getPlatformTypeName();
		if(listRecipes.contains(szTargetPlateform)){
			const FormulaRecipe& recipe = listRecipes.value(szTargetPlateform);
			const FormulaCommands& listCommands = recipe.getInstallCommands();

			FormulaCommands::const_iterator iter_cmd;
			for(iter_cmd = listCommands.constBegin(); iter_cmd != listCommands.constEnd(); ++iter_cmd)
			{
				bRes = doRunCommand((*iter_cmd), getBuildPackageDir());
				if(!bRes){
					qCritical("[install] aborting configure due to error");
					break;
				}
			}
		}
	}

	return bRes;
}

