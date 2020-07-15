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

class FormulaOptionRule
{
public:
	enum State {
		StateAll,
		StateEnabled,
		StateDisabled
	};

public:
	FormulaOptionRule();
	virtual ~FormulaOptionRule();

	void setRuleState(State iState);
	State getRuleState() const;

	void setVariableList(const FormulaVariableList& listVariables);
	const FormulaVariableList& getVariableList() const;

	bool matchState(bool bState) const;

private:
	State m_iState;

	FormulaVariableList m_listVars;
};

typedef QList<FormulaOptionRule> FormulaOptionRuleList;

class FormulaOption {
public:
	FormulaOption();
	virtual ~FormulaOption();

	bool isNull() const;

	void setOptionName(const QString& szName);
	const QString& getOptionName() const;

	void setDefaultState(bool bDefaultState);
	bool getDefaultState() const;

	void setDependenciesList(const FormulaDependenciesList& listDependencies);
	const FormulaDependenciesList& getDependenciesList() const;

	FormulaVariableList getVariableListForState(bool bState) const;

	void addOptionRule(const FormulaOptionRule& formulaOptionRule);
	const FormulaOptionRuleList& getOptionRuleList() const;

private:
	QString m_szOptionName;

	bool m_bDefaultState;

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
