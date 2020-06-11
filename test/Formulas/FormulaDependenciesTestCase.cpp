/*
 * FormulaDependenciesTestCase.cpp
 *
 *  Created on: 9 juin 2020
 *      Author: ebeuque
 */

#include <Formulas/FormulaDependencies.h>

#include "FormulaDependenciesTestCase.h"

FormulaDependenciesTestCase::FormulaDependenciesTestCase()
{

}

FormulaDependenciesTestCase::~FormulaDependenciesTestCase()
{

}

void FormulaDependenciesTestCase::test_getBestVersion()
{
	FormulaDependenciesList depsList;

	{
		FormulaDependencies deps;
		deps.addDependency("openssl", "3.0", QString());
		depsList.setDependencies("latest", deps);
	}
	{
		FormulaDependencies deps;
		deps.addDependency("openssl", "2.0", QString());
		depsList.setDependencies("1.5", deps);
	}
	{
		FormulaDependencies deps;
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
