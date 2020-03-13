/*
 * Formula.h
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULA_H_
#define SRC_FORMULAS_FORMULA_H_

#include <QString>

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

private:
	QString m_szName;
	QString m_szHomepage;

	TypeSCM m_iTypeSCM;
	QString m_szSCMURL;
};

#endif /* SRC_FORMULAS_FORMULA_H_ */
