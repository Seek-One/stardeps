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

class FormulaOption {
public:
	FormulaOption();
	virtual ~FormulaOption();

	bool isNull() const;

	void setOptionName(const QString& szName);
	const QString& getOptionName() const;

	void setDependenciesList(const FormulaDependenciesList& listDependencies);
	const FormulaDependenciesList& getDependenciesList() const;

	void addVariable(const QString& szVarName, const QString& szVarValue);
	QString getVariable(const QString& szVarName) const;

	void setVariableList(const FormulaVariableList& listVariables);
	const FormulaVariableList& getVariableList() const;

private:
	QString m_szOptionName;

	FormulaDependenciesList m_listDependencies;

	FormulaVariableList m_listVars;
};

class FormulaOptionList : public QList<FormulaOption>
{
public:
	FormulaOptionList();
	virtual ~FormulaOptionList();

	const FormulaOption& getOptionByName(const QString& szOptionName, const FormulaOption& defaultOption = FormulaOption()) const;
};

#endif /* SRC_FORMULAS_FORMULAOPTIONS_H_ */
