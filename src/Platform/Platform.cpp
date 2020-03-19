/*
 * Platform.cpp
 *
 *  Created on: 19 mars 2020
 *      Author: ebeuque
 */

#include "Platform.h"

Platform::Type Platform::fromString(const QString& szPlatform)
{
	if(szPlatform == "linux-gcc-32"){
		return Linux_GCC_32;
	}
	if(szPlatform == "linux-gcc-64"){
		return Linux_GCC_64;
	}
	if(szPlatform == "win32-gcc"){
		return Win32_GCC;
	}
	return Unknown;
}
