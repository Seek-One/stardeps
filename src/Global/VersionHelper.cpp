/*
 * VersionHelper.cpp
 *
 *  Created on: 9 juin 2020
 *      Author: ebeuque
 */

#include "Global/VersionHelper.h"

VersionHelper::VersionHelper()
{

}

VersionHelper::~VersionHelper()
{

}

bool VersionHelper::isVersionLessThan(const QString& szVersion1, const QString& szVersion2)
{
	if(szVersion1 == "latest"){
		return false;
	}

	return true;
}

bool VersionHelper::isVersionGreaterThan(const QString& szVersion1, const QString& szVersion2)
{
	if(szVersion1 == "latest"){
		return true;
	}
	if(szVersion2 == "latest"){
		return false;
	}

	QStringList listTokensV1 = szVersion1.split('.');
	QStringList listTokensV2 = szVersion2.split('.');

	int iCurrentIdx = 0;
	do{
		if((listTokensV1.count() > iCurrentIdx) && (listTokensV2.count() > iCurrentIdx)){

		}
	}while(true);

	return false;
}
