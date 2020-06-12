/*
 * CommandBuild.cpp
 *
 *  Created on: 20 mars 2020
 *      Author: ebeuque
 */

#include "CommandBuild.h"

CommandBuild::CommandBuild() : AbstractPackageCommand("build")
{

}

CommandBuild::~CommandBuild()
{

}

bool CommandBuild::doExecute()
{
	bool bRes = true;

	// Execute commands
	if(bRes){
		const FormulaRecipeList& listRecipes = getFormula()->getRecipeList();
		QString szTargetPlateform = getEnv().getPlatformTypeName();
		if(listRecipes.contains(szTargetPlateform)){
			const FormulaRecipe& recipe = listRecipes.value(szTargetPlateform);
			const FormulaCommands& listCommands = recipe.getBuildCommands();

			FormulaCommands::const_iterator iter_cmd;
			for(iter_cmd = listCommands.constBegin(); iter_cmd != listCommands.constEnd(); ++iter_cmd)
			{
				bRes = doRunCommand((*iter_cmd), getBuildPackageDir());
				if(!bRes){
					qCritical("[build] aborting configure due to error");
					break;
				}
			}
		}
	}

	return bRes;
}
