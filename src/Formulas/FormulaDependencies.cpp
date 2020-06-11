/*
 * FormulaDependencies.cpp
 *
 *  Created on: 8 juin 2020
 *      Author: ebeuque
 */

#include "Version/VersionHelper.h"

#include "FormulaDependencies.h"

FormulaDependencies::FormulaDependencies()
{

}

FormulaDependencies::~FormulaDependencies()
{

}

void FormulaDependencies::addDependency(const PackageDependency& dependency)
{
	m_listDependency.append(dependency);
}

void FormulaDependencies::addDependency(const QString& szPackage, const QString& szVersionMin, const QString& szVersionMax)
{
	PackageDependency dependency;
	dependency.setPackage(szPackage);
	dependency.setVersionMin(szVersionMin);
	dependency.setVersionMax(szVersionMax);
	m_listDependency.append(dependency);
}

void FormulaDependencies::addDependencyList(const PackageDependencyList& listDependency)
{
	m_listDependency.append(listDependency);
}

const PackageDependencyList& FormulaDependencies::getList() const
{
	return m_listDependency;
}

FormulaDependenciesList::FormulaDependenciesList()
{

}

FormulaDependenciesList::~FormulaDependenciesList()
{

}

void FormulaDependenciesList::setDependencies(const QString& szVersion, const FormulaDependencies& deps)
{
	insert(szVersion, deps);
}

void FormulaDependenciesList::addDependencies(const QString& szVersion, const FormulaDependencies& deps)
{
	if(contains(szVersion)){
		(*this)[szVersion].addDependencyList(deps.getList());
	}else{
		insert(szVersion, deps);
	}
}

void FormulaDependenciesList::addDependency(const QString& szVersion, const PackageDependency& dependency)
{
	if(contains(szVersion)){
		(*this)[szVersion].addDependency(dependency);
	}else{
		FormulaDependencies list;
		list.addDependency(dependency);
		insert(szVersion, list);
	}
}

QString FormulaDependenciesList::getBestDependenciesVersion(const QString& szVersion) const
{
	QString szFirstVersion;
	QString szLastVersion;

	QString szBeforeVersion;
	QString szAfterVersion;

	FormulaDependenciesList::const_iterator iter;

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
