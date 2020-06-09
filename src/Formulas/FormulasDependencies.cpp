/*
 * FormulasDependencies.cpp
 *
 *  Created on: 8 juin 2020
 *      Author: ebeuque
 */

#include "Version/VersionHelper.h"

#include "FormulasDependencies.h"

FormulasDependency::FormulasDependency()
{

}

FormulasDependency::~FormulasDependency()
{

}

void FormulasDependency::setPackage(const QString& szPackage)
{
	m_szPackage = szPackage;
}

const QString& FormulasDependency::getPackage() const
{
	return m_szPackage;
}

void FormulasDependency::setVersionMin(const QString& szVersionMin)
{
	m_szVersionMin = szVersionMin;
}

const QString& FormulasDependency::getVersionMin() const
{
	return m_szVersionMin;
}

void FormulasDependency::setVersionMax(const QString& szVersionMax)
{
	m_szVersionMax = szVersionMax;
}

const QString& FormulasDependency::getVersionMax() const
{
	return m_szVersionMax;
}

FormulasDependencies::FormulasDependencies()
{

}

FormulasDependencies::~FormulasDependencies()
{

}

void FormulasDependencies::addDependency(const FormulasDependency& dependency)
{
	m_listDependency.append(dependency);
}

void FormulasDependencies::addDependency(const QString& szPackage, const QString& szVersionMin, const QString& szVersionMax)
{
	FormulasDependency dependency;
	dependency.setPackage(szPackage);
	dependency.setVersionMin(szVersionMin);
	dependency.setVersionMax(szVersionMax);
	m_listDependency.append(dependency);
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

void FormulasDependenciesList::addDependency(const QString& szVersion, const FormulasDependency& dependency)
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
