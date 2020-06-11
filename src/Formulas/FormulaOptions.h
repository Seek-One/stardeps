/*
 * FormulaOptions.h
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULAOPTIONS_H_
#define SRC_FORMULAS_FORMULAOPTIONS_H_

#include <QList>

#include <Formulas/FormulasDependencies.h>
#include <Formulas/FormulaVariableList.h>

class FormulaOption {
public:
	FormulaOption();
	virtual ~FormulaOption();

	void setOptionName(const QString& szName);
	const QString& getOptionName() const;

	void setDependenciesList(const FormulasDependenciesList& listDependencies);
	const FormulasDependenciesList& getDependenciesList() const;

	void addVariable(const QString& szVarName, const QString& szVarValue);
	QString getVariable(const QString& szVarName) const;

	void setVariableList(const FormulaVariableList& listVariables);
	const FormulaVariableList& getVariableList() const;

private:
	QString m_szOptionName;

	FormulasDependenciesList m_listDependencies;

	FormulaVariableList m_listVars;
};

class FormulaOptionList : public QList<FormulaOption> {
public:
	FormulaOptionList();
	virtual ~FormulaOptionList();
};

#endif /* SRC_FORMULAS_FORMULAOPTIONS_H_ */
