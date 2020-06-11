/*
 * Formula.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include <Formulas/Formula.h>

Formula::Formula()
{
	m_iTypeSCM = SCM_None;
}

Formula::~Formula()
{

}

void Formula::setName(const QString& szName)
{
	m_szName = szName;
}

QString Formula::getName() const
{
	return m_szName;
}

void Formula::setHomepage(const QString& szHomepage)
{
	m_szHomepage = szHomepage;
}

QString Formula::getHomepage() const
{
	return m_szHomepage;
}

void Formula::setTypeSCM(TypeSCM iTypeSCM)
{
	m_iTypeSCM = iTypeSCM;
}

Formula::TypeSCM Formula::getTypeSCM() const
{
	return m_iTypeSCM;
}

void Formula::setSCMURL(const QString& szSCMURL)
{
	m_szSCMURL = szSCMURL;
}

QString Formula::getSCMURL() const
{
	return m_szSCMURL;
}

void Formula::addDependencies(const QString& szVersion, const FormulasDependencies& dependencies)
{
	m_listDependencies.insert(szVersion, dependencies);
}

void Formula::setDependenciesList(const FormulasDependenciesList& listDependencies)
{
	m_listDependencies = listDependencies;
}

const FormulasDependenciesList& Formula::getDependenciesList() const
{
	return m_listDependencies;
}

void Formula::addOption(const FormulaOption& option)
{
	m_listOptions.append(option);
}

const FormulaOptionList& Formula::getOptions() const
{
	return m_listOptions;
}

void Formula::addRecipe(const QString& szTargetPlateform, const FormulaRecipe& recipe)
{
	m_listRecipes.insert(szTargetPlateform, recipe);
}

const FormulaRecipeList& Formula::getRecipeList() const
{
	return m_listRecipes;
}
