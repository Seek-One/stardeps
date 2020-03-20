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

typedef QList<QString> FormulaCommands;
typedef QMap<QString, FormulaCommands> FormulaConfigureRulesList;

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

	void addConfigureRule(const QString& szTargetPlateform, const FormulaCommands& listCommands);
	const FormulaConfigureRulesList& getConfigureRules() const;

private:
	QString m_szName;
	QString m_szHomepage;

	TypeSCM m_iTypeSCM;
	QString m_szSCMURL;

	FormulaConfigureRulesList m_listConfigureRules;

};

#endif /* SRC_FORMULAS_FORMULA_H_ */
