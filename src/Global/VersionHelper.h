/*
 * VersionHelper.h
 *
 *  Created on: 9 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_GLOBAL_VERSIONHELPER_H_
#define SRC_GLOBAL_VERSIONHELPER_H_

#include <QString>

class VersionHelper {
public:
	VersionHelper();
	virtual ~VersionHelper();

	static bool isVersionLessThan(const QString& szVersion1, const QString& szVersion2);
	static bool isVersionGreaterThan(const QString& szVersion1, const QString& szVersion2);
};

#endif /* SRC_GLOBAL_VERSIONHELPER_H_ */
