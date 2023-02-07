/*
 * FormulaOptions.h
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULAOPTIONS_H_
#define SRC_FORMULAS_FORMULAOPTIONS_H_

#include <QList>

#include <Formulas/FormulaVariableList.h>
#include <Formulas/FormulaDependencies.h>
#include <Formulas/FormulaOptionRules.h>

#include "Package/PackageOptionList.h"

class FormulaOption {
public:
	FormulaOption();
	virtual ~FormulaOption();

	bool isNull() const;

	void setOptionName(const QString& szName);
	const QString& getOptionName() const;

	void setDefaultState(bool bDefaultState);
	bool getDefaultState() const;

	void setDefaultModes(const QStringList& szModes);
	const QStringList& getDefaultModes() const;

	void setDependenciesList(const FormulaDependenciesList& listDependencies);
	const FormulaDependenciesList& getDependenciesList() const;

	PackageSearchMode getDependenciesSearchMode(const QStringList& listOptionModes) const;

	FormulaVariableList getVariableListForState(bool bState, const QStringList& listModes) const;

	void addOptionRule(const FormulaOptionRules& formulaOptionRule);
	const FormulaOptionRuleList& getOptionRuleList() const;

private:
	QString m_szOptionName;

	bool m_bDefaultState;
	QStringList m_listDefaultModes;

	FormulaDependenciesList m_listDependencies;

	FormulaOptionRuleList m_listRules;
};

class FormulaOptionList : public QList<FormulaOption>
{
public:
	FormulaOptionList();
	virtual ~FormulaOptionList();

	const FormulaOption& getOptionByName(const QString& szOptionName, const FormulaOption& defaultOption = FormulaOption()) const;
};

#endif /* SRC_FORMULAS_FORMULAOPTIONS_H_ */
