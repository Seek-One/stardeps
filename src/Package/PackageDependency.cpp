/*
 * PackageDependency.cpp
 *
 *  Created on: 10 juin 2020
 *      Author: ebeuque
 */

#include "PackageDependency.h"

PackageDependency::PackageDependency()
{

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

QString PackageDependency::toString() const
{
	QString szTmp = m_szPackage;

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
	return szTmp;
}

PackageDependencyList::PackageDependencyList()
{

}

PackageDependencyList::~PackageDependencyList()
{

}
