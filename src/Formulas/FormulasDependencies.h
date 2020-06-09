/*
 * FormulasDependencies.h
 *
 *  Created on: 8 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULASDEPENDENCIES_H_
#define SRC_FORMULAS_FORMULASDEPENDENCIES_H_

#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QMap>

#include "FormulaCommands.h"

class FormulaRecipe;

class FormulasDependency
{
public:
	FormulasDependency();
	virtual ~FormulasDependency();

	void setPackage(const QString& szPackage);
	const QString& getPackage() const;
	void setVersionMin(const QString& szVersionMin);
	const QString& getVersionMin() const;
	void setVersionMax(const QString& szVersionMax);
	const QString& getVersionMax() const;

private:
	QString m_szPackage;
	QString m_szVersionMin;
	QString m_szVersionMax;
};

class FormulasDependencies {
public:
	FormulasDependencies();
	virtual ~FormulasDependencies();

	void addDependency(const FormulasDependency& dependency);
	void addDependency(const QString& szPackage, const QString& szVersionMin, const QString& szVersionMax);

private:
	QList<FormulasDependency> m_listDependency;
};

class FormulasDependenciesList : public QMap<QString, FormulasDependencies>
{
public:
	FormulasDependenciesList();
	virtual ~FormulasDependenciesList();

	void addDependency(const QString& szVersion, const FormulasDependency& dependency);

	QString getBestDependeciesVersion(const QString& szVersion) const;
};

#endif /* SRC_FORMULAS_FORMULASDEPENDENCIES_H_ */
