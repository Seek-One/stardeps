/*
 * EnvironmentLoader.h
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_ENVIRONMENT_ENVIRONMENTLOADER_H_
#define SRC_ENVIRONMENT_ENVIRONMENTLOADER_H_

#include <QString>
#include <QSharedPointer>

#include "Environment.h"

class EnvironmentLoader {
public:
	EnvironmentLoader();
	virtual ~EnvironmentLoader();

	bool loadEnvironmentVars(Environment& env);
};

#endif /* SRC_ENVIRONMENT_ENVIRONMENTLOADER_H_ */
