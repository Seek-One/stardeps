/*
 * FormulasDependencies.h
 *
 *  Created on: 8 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULADEPENDENCIES_H_
#define SRC_FORMULAS_FORMULADEPENDENCIES_H_

#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QMap>

#include "Package/PackageDependency.h"
#include "Package/PackageSearchMode.h"

#include "FormulaCommands.h"

class FormulaDependencies {
public:
	FormulaDependencies();
	virtual ~FormulaDependencies();

	void addDependency(const PackageDependency& dependency);
	void addDependency(const QString& szPackage, const QString& szVersionMin, const QString& szVersionMax);
	void addDependencyList(const PackageDependencyList& listDependency);

	const PackageDependencyList& getList() const;

	const PackageSearchMode& getSearchMode() const;
	void setSearchMode(const PackageSearchMode& iSearchMode);

private:
	PackageDependencyList m_listDependency;
	PackageSearchMode m_iSearchMode;
};

class FormulaDependenciesList : public QMap<QString, FormulaDependencies>
{
public:
	FormulaDependenciesList();
	virtual ~FormulaDependenciesList();

	void setDependencies(const QString& szVersion, const FormulaDependencies& deps);
	void addDependencies(const QString& szVersion, const FormulaDependencies& deps);


	void addDependency(const QString& szVersion, const PackageDependency& dependency);

	QString getBestDependenciesVersion(const QString& szVersion) const;
};

#endif /* SRC_FORMULAS_FORMULADEPENDENCIES_H_ */
