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

        // Add steps to the list
        if(bAcceptStep){
            listFormulaStepActionResult.append(formulaStep.getFormulaStepActionList());
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
