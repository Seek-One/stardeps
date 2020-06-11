/*
 * FormulaDependenciesTestCase.h
 *
 *  Created on: 9 juin 2020
 *      Author: ebeuque
 */

#ifndef TEST_FORMULAS_FORMULADEPENDENCIESTESTCASE_H_
#define TEST_FORMULAS_FORMULADEPENDENCIESTESTCASE_H_

#include <QTest>

class FormulaDependenciesTestCase : public QObject  {
	Q_OBJECT
public:
	FormulaDependenciesTestCase();
	virtual ~FormulaDependenciesTestCase();

private slots:
	void test_getBestVersion();
};

#endif /* TEST_FORMULAS_FORMULADEPENDENCIESTESTCASE_H_ */
