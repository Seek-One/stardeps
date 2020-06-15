/*
 * Platform.h
 *
 *  Created on: 19 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_PLATFORM_PLATFORM_H_
#define SRC_PLATFORM_PLATFORM_H_

#include <QString>

class Platform {
public:
	enum Type {
		Unknown,
		Linux_GCC_32,
		Linux_GCC_64,
		Win32_GCC,
        Darwin_CLANG_64
	};

public:
	static Platform::Type fromString(const QString& szPlatform);
	static const char* toString(Platform::Type iType);
};

#endif /* SRC_PLATFORM_PLATFORM_H_ */
