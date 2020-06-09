/*
 * VersionHelperTestCase.cpp
 *
 *  Created on: 9 juin 2020
 *      Author: ebeuque
 */

#include "Global/VersionHelper.h"

#include "VersionHelperTestCase.h"

VersionHelperTestCase::VersionHelperTestCase()
{

}

VersionHelperTestCase::~VersionHelperTestCase()
{

}

void VersionHelperTestCase::test_version_Compare()
{
	int iRes;

	iRes = VersionHelper::compare("latest", "latest");
	QVERIFY(iRes == 0);

	iRes = VersionHelper::compare("1.0", "latest");
	QVERIFY(iRes == -1);

	iRes = VersionHelper::compare("latest", "1.0");
	QVERIFY(iRes == 1);

	iRes = VersionHelper::compare("1.0", "1.0");
	QVERIFY(iRes == 0);

	iRes = VersionHelper::compare("1.0", "2.0");
	QVERIFY(iRes == -1);

	iRes = VersionHelper::compare("2.0", "1.0");
	QVERIFY(iRes == 1);

	iRes = VersionHelper::compare("1.0", "1.0.0");
	QVERIFY(iRes == -1);

	iRes = VersionHelper::compare("1.0.0", "1.0");
	QVERIFY(iRes == 1);
}
