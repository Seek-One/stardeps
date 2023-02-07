/*
 * PackageDependency.cpp
 *
 *  Created on: 10 juin 2020
 *      Author: ebeuque
 */

#include "PackageDependency.h"

PackageDependency::PackageDependency()
{
	m_iSearchMode = PackageSearchMode::Unknown;
}

PackageDependency::~PackageDependency()
{

}

void PackageDependency::setPackage(const QString& szPackage)
{
	m_szPackage = szPackage;
}

const QString& PackageDependency::getPackage() const
{
	return m_szPackage;
}

void PackageDependency::setVersionMin(const QString& szVersionMin)
{
	m_szVersionMin = szVersionMin;
}

const QString& PackageDependency::getVersionMin() const
{
	return m_szVersionMin;
}

void PackageDependency::setVersionMax(const QString& szVersionMax)
{
	m_szVersionMax = szVersionMax;
}

const QString& PackageDependency::getVersionMax() const
{
	return m_szVersionMax;
}

void PackageDependency::setPkgConfigName(const QString& szPkgConfigName)
{
	m_szPkgConfigName = szPkgConfigName;
}

const QString& PackageDependency::getPkgConfigName() const
{
	return m_szPkgConfigName;
}


const PackageSearchMode& PackageDependency::getSearchMode() const
{
	return m_iSearchMode;
}

void PackageDependency::setSearchMode(const PackageSearchMode& iSearchMode)
{
	m_iSearchMode = iSearchMode;
}

QString PackageDependency::toString() const
{
	QString szTmp = m_szPackage;
	if(!m_szPkgConfigName.isEmpty()){
		szTmp += "[" + m_szPkgConfigName + "]";
	}

	if(!m_szVersionMin.isEmpty() || !m_szVersionMax.isEmpty()){
		szTmp += " (";
		if(!m_szVersionMin.isEmpty()){
			szTmp += ">= " + m_szVersionMin;
		}
		if(!m_szVersionMax.isEmpty()){
			if(!m_szVersionMin.isEmpty()){
				szTmp += ", ";
			}
			szTmp += "<= " + m_szVersionMax;
		}
		szTmp += ")";
	}

	szTmp += ", search mode: " + m_iSearchMode.toString();

	return szTmp;
}

PackageDependencyList::PackageDependencyList()
{

}

PackageDependencyList::~PackageDependencyList()
{

}
