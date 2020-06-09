/*
 * VersionHelper.cpp
 *
 *  Created on: 9 juin 2020
 *      Author: ebeuque
 */

#include <QStringList>

#include "Global/VersionHelper.h"

VersionHelper::VersionHelper()
{

}

VersionHelper::~VersionHelper()
{

}

bool VersionHelper::isLessThan(const QString& szVersion1, const QString& szVersion2)
{
	return (compare(szVersion1, szVersion2) == -1);
}

bool VersionHelper::isGreaterThan(const QString& szVersion1, const QString& szVersion2)
{
	return (compare(szVersion1, szVersion2) == 1);
}

int VersionHelper::compare(const QString& szVersion1, const QString& szVersion2)
{
	if(szVersion1 == szVersion2){
		return 0;
	}
	if(szVersion1 == "latest"){
		return 1;
	}
	if(szVersion2 == "latest"){
		return -1;
	}

	QStringList listTokensV1 = szVersion1.split('.');
	QStringList listTokensV2 = szVersion2.split('.');

	QString szTokV1;
	QString szTokV2;

	int iCurrentIdx = 0;
	do{
		if(listTokensV1.count() > iCurrentIdx){
			szTokV1 = listTokensV1[iCurrentIdx];
		}else{
			szTokV1 = QString();
		}

		if(listTokensV2.count() > iCurrentIdx){
			szTokV2 = listTokensV2[iCurrentIdx];
		}else{
			szTokV2 = QString();
		}

		if (!szTokV1.isEmpty() && !szTokV2.isEmpty())
		{
			int iRes = QString::compare(szTokV1, szTokV2);
			if(iRes != 0){
				return iRes;
			}
		}else{
			break;
		}

		iCurrentIdx++;
	}while(true);

	if (!szTokV1.isEmpty() && szTokV2.isEmpty()){
		return 1;
	}
	if (szTokV1.isEmpty() && !szTokV2.isEmpty()){
		return -1;
	}

	return 0;
}
