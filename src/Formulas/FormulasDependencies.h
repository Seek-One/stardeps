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

#include "Package/PackageDependency.h"

#include "FormulaCommands.h"

class FormulaRecipe;

class FormulasDependencies {
public:
	FormulasDependencies();
	virtual ~FormulasDependencies();

	void addDependency(const PackageDependency& dependency);
	void addDependency(const QString& szPackage, const QString& szVersionMin, const QString& szVersionMax);

	const PackageDependencyList& getList() const;

private:
	PackageDependencyList m_listDependency;
};

class FormulasDependenciesList : public QMap<QString, FormulasDependencies>
{
public:
	FormulasDependenciesList();
	virtual ~FormulasDependenciesList();

	void setDependencies(const QString& szVersion, const FormulasDependencies& deps);
	void addDependency(const QString& szVersion, const PackageDependency& dependency);

	QString getBestDependeciesVersion(const QString& szVersion) const;
};

#endif /* SRC_FORMULAS_FORMULASDEPENDENCIES_H_ */
