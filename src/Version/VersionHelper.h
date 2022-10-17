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

	static bool isLessThan(const QString& szVersion1, const QString& szVersion2);
	static bool isLessThanOrEqual(const QString& szVersion1, const QString& szVersion2);
	static bool isGreaterThan(const QString& szVersion1, const QString& szVersion2);
	static bool isGreaterThanOrEqual(const QString& szVersion1, const QString& szVersion2);
	static int compare(const QString& szVersion1, const QString& szVersion2);

	static bool checkVersion(const QString& szVersion, const QString& szVersionMin, const QString& szVersionMax);
	static bool checkVersion(const QString& szVersion, const QString& szCheckVersion);
};

#endif /* SRC_GLOBAL_VERSIONHELPER_H_ */
