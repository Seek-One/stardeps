//
// Created by ebeuque on 07/02/23.
//

#include "PackageSearchMode.h"


PackageSearchMode::PackageSearchMode()
{
	m_iMode = PackageSearchMode::Environment;
}

PackageSearchMode::PackageSearchMode(SearchMode iSearchMode)
{
	m_iMode = iSearchMode;
}

PackageSearchMode::~PackageSearchMode()
{

}

PackageSearchMode PackageSearchMode::fromString(const QString& szSearchMode)
{
	if(szSearchMode == "all"){
		return PackageSearchMode::All;
	}else if(szSearchMode == "environment"){
		return PackageSearchMode::Environment;
	}else if(szSearchMode == "system"){
		return PackageSearchMode::System;
	}else if(szSearchMode == "custom"){
		return PackageSearchMode::Custom;
	}
	return PackageSearchMode::Default;
}

void PackageSearchMode::setFromString(const QString &szSearchMode)
{
	*this = fromString(szSearchMode);
}

QString PackageSearchMode::toString() const
{
	switch(m_iMode){
	case PackageSearchMode::All: return "all";
	case PackageSearchMode::Environment: return "environment";
	case PackageSearchMode::System: return "system";
	case PackageSearchMode::Custom: return "custom";
	default:
		break;
	}
	return "environment";
}

bool PackageSearchMode::operator==(const PackageSearchMode& other) const
{
	return m_iMode == other.m_iMode;
}

bool PackageSearchMode::operator==(const PackageSearchMode::SearchMode& iSearchMode) const
{
	return m_iMode == iSearchMode;
}

PackageSearchMode& PackageSearchMode::operator=(const PackageSearchMode& other)
{
	m_iMode = other.m_iMode;
	return *this;
}

PackageSearchMode& PackageSearchMode::operator=(const PackageSearchMode::SearchMode& iSearchMode)
{
	m_iMode = iSearchMode;
	return *this;
}