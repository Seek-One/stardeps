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

class VariableList  : public QMap<QString, QString>
{
public:
	VariableList();
	virtual ~VariableList();

public:
	void print() const;
};

#endif /* SRC_VARIABLE_VARIABLELIST_H_ */
