/*
 * FormulasDependenciesTestCase.cpp
 *
 *  Created on: 9 juin 2020
 *      Author: ebeuque
 */

#include "Formulas/FormulasDependencies.h"

#include "FormulasDependenciesTestCase.h"

FormulasDependenciesTestCase::FormulasDependenciesTestCase()
{

}

FormulasDependenciesTestCase::~FormulasDependenciesTestCase()
{

}

void FormulasDependenciesTestCase::test_getBestVersion()
{
	FormulasDependenciesList depsList;

	{
		FormulasDependencies deps;
		deps.addDependency("openssl", "3.0", QString());
		depsList.setDependencies("latest", deps);
	}
	{
		FormulasDependencies deps;
		deps.addDependency("openssl", "2.0", QString());
		depsList.setDependencies("1.5", deps);
	}
	{
		FormulasDependencies deps;
		deps.addDependency("openssl", "1.0", QString());
		depsList.setDependencies("1.0", deps);
	}

	QString szBestVersion;

	szBestVersion = depsList.getBestDependeciesVersion("0.1.1");
	QVERIFY(szBestVersion == "1.0");

	szBestVersion = depsList.getBestDependeciesVersion("1");
	QVERIFY(szBestVersion == "1.0");

	szBestVersion = depsList.getBestDependeciesVersion("1.0");
	QVERIFY(szBestVersion == "1.0");

	szBestVersion = depsList.getBestDependeciesVersion("1.0.5");
	QVERIFY(szBestVersion == "1.0");

	szBestVersion = depsList.getBestDependeciesVersion("1.1");
	QVERIFY(szBestVersion == "1.0");

	szBestVersion = depsList.getBestDependeciesVersion("1.5");
	QVERIFY(szBestVersion == "1.5");

	szBestVersion = depsList.getBestDependeciesVersion("1.6");
	QVERIFY(szBestVersion == "latest");
}
