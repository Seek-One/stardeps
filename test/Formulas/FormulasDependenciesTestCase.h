/*
 * FormulasDependenciesTestCase.h
 *
 *  Created on: 9 juin 2020
 *      Author: ebeuque
 */

#ifndef TEST_FORMULAS_FORMULASDEPENDENCIESTESTCASE_H_
#define TEST_FORMULAS_FORMULASDEPENDENCIESTESTCASE_H_

#include <QTest>

class FormulasDependenciesTestCase {
public:
	FormulasDependenciesTestCase();
	virtual ~FormulasDependenciesTestCase();

private slots:
	void test_version_Compare();
};

#endif /* TEST_FORMULAS_FORMULASDEPENDENCIESTESTCASE_H_ */
