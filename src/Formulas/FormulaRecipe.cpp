/*
 * FormulaRecipe.cpp
 *
 *  Created on: 20 mars 2020
 *      Author: ebeuque
 */

#include "FormulaRecipe.h"

FormulaRecipe::FormulaRecipe()
{

}

FormulaRecipe::~FormulaRecipe()
{

}

void FormulaRecipe::setFormulaSteps(const FormulaStepList& listStep)
{
    m_listStep = listStep;
}

const FormulaStepList& FormulaRecipe::getFormulaSteps() const
{
    return m_listStep;
}

FormulaStepActionList FormulaRecipe::getFormulaStepActionList(const QString& szStep, const QString& szPlatform) const
{
    FormulaStepActionList listFormulaStepActionResult;

    FormulaStepList::const_iterator iter;
    for(iter = m_listStep.constBegin(); iter != m_listStep.constEnd(); ++iter)
    {
        const FormulaStep& formulaStep = (*iter);
        bool bAcceptStep = true;

        // If requested step
        if(formulaStep.getStep() != szStep) {
            bAcceptStep = false;
        }

        // Check platforms
        if(bAcceptStep){
            bAcceptStep = formulaStep.acceptPlatform(szPlatform);
        }

        if(bAcceptStep){

            const FormulaStepActionList& formulaStepActionList = formulaStep.getFormulaStepActionList();

            FormulaStepActionList::const_iterator iter_action;
            for(iter_action = formulaStepActionList.constBegin(); iter_action != formulaStepActionList.constEnd(); ++iter_action)
            {
                const FormulaStepAction& formulaStepAction = (*iter_action);

                bool bAccept = true;

                // Don't include platforms step
                if(formulaStepAction.getActionType() == FormulaStepAction::ActionPlatforms){
                    bAccept = false;
                }

                if(bAccept) {
                    listFormulaStepActionResult.append(formulaStepAction);
                }
            }
        }
    }

    return listFormulaStepActionResult;
}

void FormulaRecipe::setPrepareCommands(const FormulaCommands& listCommands)
{
    m_listPrepareCommands = listCommands;
}

const FormulaCommands& FormulaRecipe::getPrepareCommands() const
{
    return m_listPrepareCommands;
}

void FormulaRecipe::setConfigureCommands(const FormulaCommands& listCommands)
{
	m_listConfigureCommands = listCommands;
}

const FormulaCommands& FormulaRecipe::getConfigureCommands() const
{
	return m_listConfigureCommands;
}

void FormulaRecipe::setBuildCommands(const FormulaCommands& listCommands)
{
	m_listBuildCommands = listCommands;
}

const FormulaCommands& FormulaRecipe::getBuildCommands() const
{
	return m_listBuildCommands;
}

void FormulaRecipe::setInstallCommands(const FormulaCommands& listCommands)
{
	m_listInstallCommands = listCommands;
}

const FormulaCommands& FormulaRecipe::getInstallCommands() const
{
	return m_listInstallCommands;
}

FormulaRecipeList::FormulaRecipeList()
{

}

FormulaRecipeList::~FormulaRecipeList()
{

}
