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
	QString szBestVersion;

	FormulasDependenciesList::const_iterator iter;

	for(iter = constBegin(); iter != constEnd(); ++iter)
	{
		const QString& szCurrentVersion = iter.key();

		if(VersionHelper::isLessThan(szCurrentVersion, szVersion)){
			if(szBestVersion.isEmpty()){
				szBestVersion = szCurrentVersion;
			}else{
				if(VersionHelper::isGreaterThan(szCurrentVersion, szBestVersion)){
					szBestVersion = szCurrentVersion;
				}
			}
		}
	}

	return szBestVersion;
}
