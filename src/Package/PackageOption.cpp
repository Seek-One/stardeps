//
// Created by ebeuque on 06/02/23.
//

#include <QStringList>

#include "PackageOption.h"

PackageOption::PackageOption()
{

}

PackageOption::PackageOption(const QString& szPackageOption)
{
	QStringList listTokens = szPackageOption.split(":");
	if(listTokens.count() >= 1) {
		m_szOptionName = listTokens[0];
		if(listTokens.count() >= 2) {
			m_listModes = listTokens[1].split(',');
		}
	}
}

PackageOption::~PackageOption()
{

}

const QString& PackageOption::getOptionName() const
{
	return m_szOptionName;
}

const QStringList& PackageOption::getModes() const
{
	return m_listModes;
}