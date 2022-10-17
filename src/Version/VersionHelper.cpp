/*
 * VersionHelper.cpp
 *
 *  Created on: 9 juin 2020
 *      Author: ebeuque
 */

#include <QStringList>

#include "Version/VersionHelper.h"

VersionHelper::VersionHelper()
{

}

VersionHelper::~VersionHelper()
{

}

bool VersionHelper::isLessThan(const QString& szVersion1, const QString& szVersion2)
{
	return (compare(szVersion1, szVersion2) < -1);
}

bool VersionHelper::isLessThanOrEqual(const QString& szVersion1, const QString& szVersion2)
{
	return (compare(szVersion1, szVersion2) <= -1);
}

bool VersionHelper::isGreaterThan(const QString& szVersion1, const QString& szVersion2)
{
	return (compare(szVersion1, szVersion2) > 0);
}

bool VersionHelper::isGreaterThanOrEqual(const QString& szVersion1, const QString& szVersion2)
{
	return (compare(szVersion1, szVersion2) >= 0);
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

bool VersionHelper::checkVersion(const QString& szVersion, const QString& szVersionMin, const QString& szVersionMax)
{
	bool bRes = true;

	if(!szVersionMin.isEmpty()){
		if(isLessThan(szVersion, szVersionMin)){
			bRes = false;
		}
	}

	if(!szVersionMax.isEmpty()){
		if(isGreaterThan(szVersion, szVersionMax)){
			bRes = false;
		}
	}

	return bRes;
}

bool VersionHelper::checkVersion(const QString& szVersion, const QString& szCheckVersion)
{
	if(szCheckVersion.startsWith(">=")){
		return isGreaterThanOrEqual(szVersion, szCheckVersion.mid(2));
	}
	if(szCheckVersion.startsWith(">")){
		return isGreaterThan(szVersion, szCheckVersion.mid(1));
	}
	if(szCheckVersion.startsWith("=")){
		return (szVersion == szCheckVersion.mid(1));
	}
	if(szCheckVersion.startsWith("<=")){
		return isLessThanOrEqual(szVersion, szCheckVersion.mid(2));
	}
	if(szCheckVersion.startsWith("<")){
		return isLessThan(szVersion, szCheckVersion.mid(1));
	}
	return (szVersion == szCheckVersion);
}
