/*
 * Formula.h
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULA_H_
#define SRC_FORMULAS_FORMULA_H_

#include <QString>
#include <QMap>
#include <QList>

#include "Package/PackageOptionList.h"

#include "FormulaDependencies.h"
#include "FormulaOptions.h"
#include "FormulaRecipe.h"

class Formula
{
public:
	enum TypeSCM {
		SCM_None,
		SCM_Git,
		SCM_Svn,
		SCM_Mercurial,
        SCM_Archive
	};

public:
	Formula();
	virtual ~Formula();

	void setName(const QString& szName);
	QString getName() const;

	void setHomepage(const QString& szHomepage);
	QString getHomepage() const;

	void setTypeSCM(TypeSCM iTypeSCM);
	TypeSCM getTypeSCM() const;

	void setSCMURL(const QString& szSCMURL);
	QString getSCMURL() const;

    void setSCMDefaultBranch(const QString& szDefaultBranch);
    QString getSCMDefaultBranch() const;

	void addDependencies(const QString& szVersion, const FormulaDependencies& dependencies);
	void setDependenciesList(const FormulaDependenciesList& listDependencies);
	const FormulaDependenciesList& getDependenciesList() const;

	FormulaDependenciesList getDependenciesListForOptions(const PackageOptionList& listPackageOptions) const;

	void addOption(const FormulaOption& option);
	const FormulaOptionList& getOptions() const;

	void setGlobalVariables(const FormulaVariableList& listVars);
    const FormulaVariableList& getGlobalVariables() const;

	void addRecipe(const QString& szTargetPlateform, const FormulaRecipe& recipe);
	const FormulaRecipeList& getRecipeList() const;

private:
	QString m_szName;
	QString m_szHomepage;

	TypeSCM m_iTypeSCM;
	QString m_szSCMURL;
	QString m_szDefaultBranch;

	FormulaDependenciesList m_listDependencies;
	FormulaOptionList m_listOptions;
    FormulaVariableList m_listGlobalVars;
	FormulaRecipeList m_listRecipes;
};

#endif /* SRC_FORMULAS_FORMULA_H_ */
