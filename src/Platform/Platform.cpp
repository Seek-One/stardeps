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
    if(szPlatform == "linux-mingw-gcc-32"){
        return Linux_MINGW_GCC_32;
    }
    if(szPlatform == "linux-mingw-gcc-64"){
        return Linux_MINGW_GCC_64;
    }
	if(szPlatform == "windows-gcc-32"){
		return Windows_GCC_32;
	}
    if(szPlatform == "windows-gcc-64"){
        return Windows_GCC_64;
    }
    if(szPlatform == "windows-msvc"){
        return Windows_MSVC;
    }
    if(szPlatform == "darwin-clang-64"){
        return Darwin_CLANG_64;
    }
	return Unknown;
}

const char* Platform::toString(Platform::Type iType)
{
    switch(iType){
        case Linux_GCC_32: return "linux-gcc-32";
        case Linux_GCC_64: return "linux-gcc-64";
        case Linux_MINGW_GCC_32: return "linux-mingw-gcc-32";
        case Linux_MINGW_GCC_64: return "linux-mingw-gcc-64";
        case Windows_GCC_32: return "windows-gcc-32";
        case Windows_GCC_64: return "windows-gcc-64";
        case Windows_MSVC: return "windows-msvc";
        case Darwin_CLANG_64: return "darwin-clang-64";
        default: break;
    }
    return "";
}
