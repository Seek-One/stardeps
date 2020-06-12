/*
 * DefaultCommandEnvironment.h
 *
 *  Created on: 12 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDENVIRONMENT_DEFAULTCOMMANDENVIRONMENT_H_
#define SRC_COMMANDENVIRONMENT_DEFAULTCOMMANDENVIRONMENT_H_

#include "AbstractCommandEnvironment.h"

class DefaultCommandEnvironment : public AbstractCommandEnvironment {
public:
	DefaultCommandEnvironment();
	virtual ~DefaultCommandEnvironment();
};

#endif /* SRC_COMMANDENVIRONMENT_DEFAULTCOMMANDENVIRONMENT_H_ */
