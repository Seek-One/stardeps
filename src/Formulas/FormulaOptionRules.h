//
// Created by ebeuque on 07/02/23.
//

#ifndef STARDEPS_FORMULAOPTIONRULES_H
#define STARDEPS_FORMULAOPTIONRULES_H

#include <QString>

#include "Formulas/FormulaVariableList.h"

#include "Package/PackageSearchMode.h"

class FormulaOptionRules
{
public:
	enum State {
		StateAll,
		StateEnabled,
		StateDisabled
	};

public:
	FormulaOptionRules();
	virtual ~FormulaOptionRules();

	void setRuleState(State iState);
	State getRuleState() const;

	void setRuleMode(const QString& szMode);
	const QString& getRuleMode() const;

	void setDependenciesSearchMode(const PackageSearchMode& iDependenciesSearchMode);
	const PackageSearchMode& getDependenciesSearchMode() const;

	void setVariableList(const FormulaVariableList& listVariables);
	const FormulaVariableList& getVariableList() const;

	bool matchState(bool bState) const;

	bool matchModes(const QStringList& listModes, bool bAcceptNoMode = true) const;

private:
	State m_iState;
	QString m_szMode;
	PackageSearchMode m_iDependenciesSearchMode;

	FormulaVariableList m_listVars;
};

typedef QList<FormulaOptionRules> FormulaOptionRuleList;


#endif //STARDEPS_FORMULAOPTIONRULES_H
