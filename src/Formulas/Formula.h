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

#include "FormulaDependencies.h"
#include "FormulaOptions.h"
#include "FormulaRecipe.h"

class Formula
{
public:
	enum TypeSCM {
		SCM_None,
		SCM_Git,
		SCM_Svn
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

	void addDependencies(const QString& szVersion, const FormulaDependencies& dependencies);
	void setDependenciesList(const FormulaDependenciesList& listDependencies);
	const FormulaDependenciesList& getDependenciesList() const;

	FormulaDependenciesList getDependenciesListForOptions(const QStringList& listOptions) const;

	void addOption(const FormulaOption& option);
	const FormulaOptionList& getOptions() const;

	void addRecipe(const QString& szTargetPlateform, const FormulaRecipe& recipe);
	const FormulaRecipeList& getRecipeList() const;

private:
	QString m_szName;
	QString m_szHomepage;

	TypeSCM m_iTypeSCM;
	QString m_szSCMURL;

	FormulaDependenciesList m_listDependencies;
	FormulaOptionList m_listOptions;
	FormulaRecipeList m_listRecipes;

};

#endif /* SRC_FORMULAS_FORMULA_H_ */
