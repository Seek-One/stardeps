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
