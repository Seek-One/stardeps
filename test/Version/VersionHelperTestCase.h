/*
 * VersionHelperTestCase.h
 *
 *  Created on: 9 juin 2020
 *      Author: ebeuque
 */

#ifndef TEST_VERSION_VERSIONHELPERTESTCASE_H_
#define TEST_VERSION_VERSIONHELPERTESTCASE_H_

#include <QTest>

class VersionHelperTestCase : public QObject  {
	Q_OBJECT
public:
	VersionHelperTestCase();
	virtual ~VersionHelperTestCase();

private slots:
	void test_version_Compare();
};

#endif /* TEST_VERSION_VERSIONHELPERTESTCASE_H_ */
