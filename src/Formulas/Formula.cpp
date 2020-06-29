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

void Formula::setSCMDefaultBranch(const QString& szDefaultBranch)
{
    m_szDefaultBranch = szDefaultBranch;
}

QString Formula::getSCMDefaultBranch() const
{
    return m_szDefaultBranch;
}

void Formula::addDependencies(const QString& szVersion, const FormulaDependencies& dependencies)
{
	m_listDependencies.insert(szVersion, dependencies);
}

void Formula::setDependenciesList(const FormulaDependenciesList& listDependencies)
{
	m_listDependencies = listDependencies;
}

const FormulaDependenciesList& Formula::getDependenciesList() const
{
	return m_listDependencies;
}

FormulaDependenciesList Formula::getDependenciesListForOptions(const QStringList& listOptions) const
{
	FormulaDependenciesList listDependencies = m_listDependencies;

	FormulaOptionList::const_iterator iter_options;
	FormulaDependenciesList::const_iterator iter_deps;

	for(iter_options = m_listOptions.constBegin(); iter_options != m_listOptions.constEnd(); ++iter_options)
	{
		const FormulaOption& option = (*iter_options);
		if(listOptions.contains(option.getOptionName()))
		{
			const FormulaDependenciesList& listOptionsDependencies = option.getDependenciesList();
			if(!listOptionsDependencies.isEmpty())
			{
				for(iter_deps = listOptionsDependencies.constBegin(); iter_deps != listOptionsDependencies.constEnd(); ++iter_deps)
				{
					QString szVersion = iter_deps.key();
					const FormulaDependencies& deps = iter_deps.value();

					listDependencies.addDependencies(szVersion, deps);
				}
			}
		}
	}

	return listDependencies;
}

void Formula::addOption(const FormulaOption& option)
{
	m_listOptions.append(option);
}

const FormulaOptionList& Formula::getOptions() const
{
	return m_listOptions;
}

void Formula::setGlobalVariables(const FormulaVariableList& listVars)
{
    m_listGlobalVars = listVars;
}

const FormulaVariableList& Formula::getGlobalVariables() const
{
    return m_listGlobalVars;
}

void Formula::addRecipe(const QString& szTargetPlateform, const FormulaRecipe& recipe)
{
	m_listRecipes.insert(szTargetPlateform, recipe);
}

const FormulaRecipeList& Formula::getRecipeList() const
{
	return m_listRecipes;
}
