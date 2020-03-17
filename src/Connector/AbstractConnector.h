/*
 * AbstractConnector.h
 *
 *  Created on: 17 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_CONNECTOR_ABSTRACTCONNECTOR_H_
#define SRC_CONNECTOR_ABSTRACTCONNECTOR_H_

#include "Shell/ShellExecutor.h"

class AbstractConnector {
public:
	AbstractConnector();
	virtual ~AbstractConnector();

protected:
	ShellExecutor m_shell;
};

#endif /* SRC_CONNECTOR_ABSTRACTCONNECTOR_H_ */
