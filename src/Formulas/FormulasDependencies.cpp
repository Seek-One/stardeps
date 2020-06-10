/*
 * FormulasDependencies.cpp
 *
 *  Created on: 8 juin 2020
 *      Author: ebeuque
 */

#include "Version/VersionHelper.h"

#include "FormulasDependencies.h"

FormulasDependencies::FormulasDependencies()
{

}

FormulasDependencies::~FormulasDependencies()
{

}

void FormulasDependencies::addDependency(const PackageDependency& dependency)
{
	m_listDependency.append(dependency);
}

void FormulasDependencies::addDependency(const QString& szPackage, const QString& szVersionMin, const QString& szVersionMax)
{
	PackageDependency dependency;
	dependency.setPackage(szPackage);
	dependency.setVersionMin(szVersionMin);
	dependency.setVersionMax(szVersionMax);
	m_listDependency.append(dependency);
}

const PackageDependencyList& FormulasDependencies::getList() const
{
	return m_listDependency;
}

FormulasDependenciesList::FormulasDependenciesList()
{

}

FormulasDependenciesList::~FormulasDependenciesList()
{

}

void FormulasDependenciesList::setDependencies(const QString& szVersion, const FormulasDependencies& deps)
{
	insert(szVersion, deps);
}

void FormulasDependenciesList::addDependency(const QString& szVersion, const PackageDependency& dependency)
{
	if(contains(szVersion)){
		(*this)[szVersion].addDependency(dependency);
	}else{
		FormulasDependencies list;
		list.addDependency(dependency);
		insert(szVersion, list);
	}
}

QString FormulasDependenciesList::getBestDependeciesVersion(const QString& szVersion) const
{
	QString szFirstVersion;
	QString szLastVersion;

	QString szBeforeVersion;
	QString szAfterVersion;

	FormulasDependenciesList::const_iterator iter;

	for(iter = constBegin(); iter != constEnd(); ++iter)
	{
		const QString& szCurrentVersion = iter.key();

		if(szCurrentVersion == szVersion){
			return szCurrentVersion;
		}

		// Get first version
		if(szFirstVersion.isEmpty() || VersionHelper::isLessThan(szCurrentVersion, szFirstVersion)){
			szFirstVersion = szCurrentVersion;
		}

		// Get last version
		if(szLastVersion.isEmpty() || VersionHelper::isGreaterThan(szCurrentVersion, szLastVersion)){
			szLastVersion = szCurrentVersion;
		}

		// Get before version
		if(VersionHelper::isLessThanOrEqual(szCurrentVersion, szVersion)){
			if(szBeforeVersion.isEmpty() || VersionHelper::isGreaterThan(szCurrentVersion, szVersion)){
				szBeforeVersion = szCurrentVersion;
			}
		}

		// Get after version
		if(VersionHelper::isGreaterThanOrEqual(szCurrentVersion, szVersion)){
			if(szAfterVersion.isEmpty() || VersionHelper::isLessThan(szCurrentVersion, szVersion)){
				szAfterVersion = szCurrentVersion;
			}
		}
	}

	if(szBeforeVersion.isEmpty()){
		return szFirstVersion;
	}
	if(szAfterVersion.isEmpty()){
		return szLastVersion;
	}
	if(szVersion.startsWith(szBeforeVersion)){
		return szBeforeVersion;
	}
	if(szAfterVersion == "latest"){
		return szAfterVersion;
	}
	return szBeforeVersion;
}
