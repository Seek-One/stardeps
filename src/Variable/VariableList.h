/*
 * VariableList.h
 *
 *  Created on: 12 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_VARIABLE_VARIABLELIST_H_
#define SRC_VARIABLE_VARIABLELIST_H_

#include <QString>
#include <QMap>

class Variable
{
public:
	Variable();
	Variable(const QString& szName, const QString& szValue);
	virtual ~Variable();

	const QString& getName() const;
	const QString& getValue() const;

private:
	QString m_szName;
	QString m_szValue;
};

class VariableList  : public QList<Variable>
{
public:
	VariableList();
	virtual ~VariableList();

public:
	void print() const;

	void addVariable(const QString& szName, const QString& szValue);
	void addVariableList(const VariableList& listVars);

	const QString& getValue(const QString& szName, const QString& szDefaultValue) const;
};

#endif /* SRC_VARIABLE_VARIABLELIST_H_ */
