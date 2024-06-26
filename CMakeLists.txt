# CMake file

cmake_minimum_required(VERSION "3.13.4")

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

# Define project data 
set (APPLICATION_VENDOR_NAME "seekone")
set (APPLICATION_VENDOR_DOMAIN "www.seek-one.fr")
set (APPLICATION_NAME "StarDeps")
set (APPLICATION_VERSION_MAJOR 1)
set (APPLICATION_VERSION_MINOR 1)
set (APPLICATION_VERSION_PATCH 0)
if(NOT DEFINED APPLICATION_VERSION_BUILD)
	set(APPLICATION_VERSION_BUILD "")
endif()
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(APPLICATION_VERSION_BUILD ${APPLICATION_VERSION_BUILD}dbg)
endif()
set (APPLICATION_VERSION ${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}${APPLICATION_VERSION_BUILD})
set (APPLICATION_CONTACTMAIL "contact@seek-one.fr")
set (APPLICATION_CONTACT "Contact Seek-One <${APPLICATION_CONTACTMAIL}>")
set (APPLICATION_PACKAGE_VENDOR "seekone")
set (APPLICATION_PACKAGE_NAME "stardeps")
set (APPLICATION_EXE_NAME stardeps)

project (stardeps CXX C)

set (CMAKE_VERBOSE_MAKEFILE OFF)

##############################
# Project configuration
##############################

# Define common project config
include (CMakeModules/ProjectCommonConfig.cmake)

##################
# Define options
##################

include (CMakeModules/ProjectCompilerChecks.cmake)

####################
# Library checking
####################

# Compiler
set(WITH_COMPILER_LIBRARIES ON CACHE BOOL "Enable build with compiler libraries")
set(WITH_PTHREAD ON CACHE BOOL "Enable build with pthread library")
# GUI
set(WITH_QT ON CACHE BOOL "Enable build with qt library")
set(QT4_COMPONENTS QtCore QtTest)
set(QT5_COMPONENTS Core Test)
set(QT6_COMPONENTS Core Test)

# Set packaging options
set (PACKAGE_DEPS)
if(WITH_AUTONOMOUS_PACKAGE_BUILD)
	set(AUTONOMOUS_PACKAGE_BUILD ON CACHE BOOL "Enable build of autonomous package without dependencies")
endif()

include (CMakeModules/ProjectIncludeLibraries.cmake)

####################
# Config file
####################

# Configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
add_definitions(-DHAVE_CONFIG_H)
configure_file (
	"${PROJECT_SOURCE_DIR}/version.h.in"
	"${PROJECT_BINARY_DIR}/version.h"
)
add_definitions(-DHAVE_VERSION_H)
include_directories (${PROJECT_BINARY_DIR})

####################
# Add sources
####################

include_directories (${PROJECT_SOURCE_DIR}/src)

set(APP_COMMON_SOURCES
	src/Formulas/FormulaDependencies.cpp
	src/Formulas/FormulaDependencies.h
	src/Package/PackageDependency.cpp
	src/Package/PackageDependency.h
	src/Package/PackageOption.cpp
	src/Package/PackageOption.h
	src/Package/PackageOptionList.cpp
	src/Package/PackageOptionList.h
	src/Package/PackageSearchMode.cpp
	src/Package/PackageSearchMode.h
	src/Variable/VariableList.cpp
	src/Variable/VariableList.h
	src/Version/VersionHelper.cpp
	src/Version/VersionHelper.h
)

set(APPLICATION_SOURCES
	src/main.cpp
	src/CommandEnvironment/AbstractCommandEnvironment.cpp
	src/CommandEnvironment/AbstractCommandEnvironment.h
	src/CommandEnvironment/DefaultCommandEnvironment.cpp
	src/CommandEnvironment/DefaultCommandEnvironment.h
	src/CommandEnvironment/PackageCommandEnvironment.cpp
	src/CommandEnvironment/PackageCommandEnvironment.h
	src/Commands/AbstractCommand.cpp
	src/Commands/AbstractCommand.h
	src/Commands/AbstractPackageCommand.cpp
	src/Commands/AbstractPackageCommand.h
	src/Commands/CommandBuild.cpp
	src/Commands/CommandBuild.h
	src/Commands/CommandClean.cpp
	src/Commands/CommandClean.h
	src/Commands/CommandConfigure.cpp
	src/Commands/CommandConfigure.h
	src/Commands/CommandCreateEnv.cpp
	src/Commands/CommandCreateEnv.h
	src/Commands/CommandInstall.cpp
	src/Commands/CommandInstall.h
	src/Commands/CommandPrepare.cpp
	src/Commands/CommandPrepare.h
	src/CommandsExecutor/CommandsExecutor.cpp
	src/CommandsExecutor/CommandsExecutor.h
	src/Connector/AbstractConnector.cpp
	src/Connector/AbstractConnector.h
	src/Connector/ConnectorArchive.cpp
	src/Connector/ConnectorArchive.h
	src/Connector/ConnectorGit.cpp
	src/Connector/ConnectorGit.h
	src/Connector/ConnectorMercurial.cpp
	src/Connector/ConnectorMercurial.h
	src/Connector/ConnectorSVN.cpp
	src/Connector/ConnectorSVN.h
	src/Environment/Environment.cpp
	src/Environment/Environment.h
	src/Environment/EnvironmentLoader.cpp
	src/Environment/EnvironmentLoader.h
	src/Formulas/Formula.cpp
	src/Formulas/Formula.h
	src/Formulas/FormulaCommands.cpp
	src/Formulas/FormulaCommands.h
	src/Formulas/FormulaOptionRules.cpp
	src/Formulas/FormulaOptionRules.h
	src/Formulas/FormulaOptions.cpp
	src/Formulas/FormulaOptions.h
	src/Formulas/FormulaParser.cpp
	src/Formulas/FormulaParser.h
	src/Formulas/FormulaRecipe.cpp
	src/Formulas/FormulaRecipe.h
	src/Formulas/FormulaStep.cpp
	src/Formulas/FormulaStep.h
	src/Formulas/FormulaStepAction.cpp
	src/Formulas/FormulaStepAction.h
	src/Formulas/FormulaVariableList.cpp
	src/Formulas/FormulaVariableList.h
	src/Global/QApplicationSettings.cpp
	src/Global/QApplicationSettings.h
	src/Platform/Platform.cpp
	src/Platform/Platform.h
	src/Shell/ShellExecutor.cpp
	src/Shell/ShellExecutor.h
	${APP_COMMON_SOURCES}
)

# Creating MOC file for sources file using "slots" or Q_OBJECT macro
set(APPLICATION_MOC_HEADERS
	src/Shell/ShellExecutor.h
)
qtx_wrap_cpp(
	APPLICATION_MOC_OUTFILES
	${APPLICATION_MOC_HEADERS}
)

####################
# i18n
####################

set (I18N_FILES
	src/main.cpp
)

set (TS_FILES
	ts/fr.ts
)

option (UPDATE_TRANSLATIONS "Update source translation ts/*.ts files (WARNING: make clean will delete the source .ts files! Danger!)" ON)
if (UPDATE_TRANSLATIONS)
	qtx_create_translation(qm_FILES ${TS_FILES} ${I18N_FILES})
else (UPDATE_TRANSLATIONS)
	qtx_add_translation(qm_FILES ${TS_FILES})
endif (UPDATE_TRANSLATIONS)

add_custom_target(update_ts ALL DEPENDS ${qm_FILES})

####################
# Resource files
####################

# Configure translation file
configure_file (
	"${PROJECT_SOURCE_DIR}/ts.qrc.in"
	"${PROJECT_BINARY_DIR}/ts.qrc"
)

if (WIN32)
	set (QT_TS_FILES
		"${QT_TRANSLATIONS_DIR}/qt_fr.qm"
	)
	INSTALL(FILES ${QT_TS_FILES} DESTINATION ${INSTALL_PATH_SHARE}/translations)
endif()

# Resources
set (QRC_TS_FILES
	${PROJECT_BINARY_DIR}/ts.qrc
)
#set (QRC_FILES
#	${PROJECT_BINARY_DIR}/data/app.qrc
#)
#qtx_add_resources(RCS_OUTFILES ${QRC_FILES})
qtx_add_resources(RCS_TS_OUTFILES ${QRC_TS_FILES})

# Install formulas
install(DIRECTORY ${PROJECT_SOURCE_DIR}/data/formulas
	DESTINATION ${INSTALL_PATH_SHARE}/
	PATTERN ".svn" EXCLUDE
	PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_READ WORLD_EXECUTE
)

####################
# RPATH
####################

if(UNIX AND NOT APPLE)
	# Default library path for debian
	set(CMAKE_INSTALL_RPATH "/usr/${INSTALL_PATH_LIB}")
	# Define RPATH instead of RUNPATH
	set(CMAKE_EXE_LINKER_FLAGS "-Wl,--disable-new-dtags")
endif(UNIX AND NOT APPLE)

####################
# Create Executable
####################

## Remove the output console
add_executable (${APPLICATION_EXE_NAME}
	${APPLICATION_SOURCES}
	${APPLICATION_MODEL_SOURCES}
	${APPLICATION_MOC_OUTFILES}
	${RCS_OUTFILES}
	${RCS_TS_OUTFILES}
	${qm_FILES}
)
target_link_libraries (${APPLICATION_EXE_NAME}
	${QT_LIBRARIES}
)
install(TARGETS ${APPLICATION_EXE_NAME} DESTINATION ${INSTALL_PATH_BIN})

############################
# Common files installation
############################

# Documentation file
set(DOCFILES_EXT "")
if(WIN32)
	set(DOCFILES_EXT ".txt")
endif(WIN32)

# README file
configure_file (
	"${PROJECT_SOURCE_DIR}/README.md"
	"${PROJECT_BINARY_DIR}/README${DOCFILES_EXT}"
	NEWLINE_STYLE ${AUTO_NEWLINE_STYLE}
)
install(FILES "${PROJECT_BINARY_DIR}/README${DOCFILES_EXT}" DESTINATION ${INSTALL_PATH_DOC})

# COPYING file
configure_file (
	"${PROJECT_SOURCE_DIR}/COPYING"
	"${PROJECT_BINARY_DIR}/COPYING${DOCFILES_EXT}"
	NEWLINE_STYLE ${AUTO_NEWLINE_STYLE}
)
# ChangeLog file
set(CHANGELOG "ChangeLog")
install(FILES "${PROJECT_SOURCE_DIR}/${CHANGELOG}" DESTINATION ${INSTALL_PATH_DOC} RENAME ChangeLog${DOCFILES_EXT})

# Application icons
if(UNIX AND NOT WIN32)
	file(GLOB LIST_ICONS RELATIVE ${PROJECT_SOURCE_DIR}/data/logos ${PROJECT_SOURCE_DIR}/data/logos/*${APPLICATION_PACKAGE_NAME}.png)
	foreach(ICON ${LIST_ICONS})
		set(ICON_DST "")
		if(${ICON} MATCHES "_[^_]*${APPLICATION_PACKAGE_NAME}.png")
			STRING(REGEX REPLACE "_[^_]*${APPLICATION_PACKAGE_NAME}.png" "" ICON_DST ${ICON})
			STRING(REPLACE "_" "/" ICON_DST ${ICON_DST})
			set(ICON_DST ${INSTALL_PATH_ICONS}/${ICON_DST})
		else()
			set(ICON_DST ${INSTALL_PATH_ICONS})
		endif()
		install(FILES ${PROJECT_SOURCE_DIR}/data/logos/${ICON}
			DESTINATION ${ICON_DST} RENAME ${APPLICATION_PACKAGE_NAME}.png
			PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_READ WORLD_EXECUTE
		)
	endforeach(ICON)
endif(UNIX AND NOT WIN32)

####################
# Build test suite
####################

SET (UNITTEST_SRC 
	test/main.cpp
	test/Formulas/FormulaDependenciesTestCase.cpp
	test/Formulas/FormulaDependenciesTestCase.h
	test/Version/VersionHelperTestCase.cpp
	test/Version/VersionHelperTestCase.h
)
	
# Creating MOC file for sources file using "slots" or Q_OBJECT macro
set(UNITTEST_MOC_HEADERS
	test/Formulas/FormulaDependenciesTestCase.h
	test/Version/VersionHelperTestCase.h
)
QT_WRAP_CPP(
	UNITTEST_MOC_OUTFILES
	${UNITTEST_MOC_HEADERS}
)

set (UNITTEST_EXE ${APPLICATION_EXE_NAME}-testsuite)
add_executable (${UNITTEST_EXE} ${UNITTEST_SRC} ${UNITTEST_MOC_OUTFILES}
	${APP_COMMON_SOURCES}
	${RCS_OUTFILES}
	
)
set_target_properties(${UNITTEST_EXE} PROPERTIES COMPILE_FLAGS -DUNITTEST)
target_link_libraries (${UNITTEST_EXE}
	${QT_LIBRARIES}
	${PTHREAD_LIBRARIES}
)

#################
# Build package
#################

set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${INSTALL_PATH_BIN})
INCLUDE(InstallRequiredSystemLibraries)

# CPack confile file
configure_file(${PROJECT_SOURCE_DIR}/CPackOptions.cmake.in
	${PROJECT_BINARY_DIR}/CPackOptions.cmake
	@ONLY)
set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_BINARY_DIR}/CPackOptions.cmake)

if(WIN32)
	if(CMAKE_BUILD_TYPE MATCHES Debug)
		SET(CPACK_GENERATOR ZIP)
	else()
		SET(CPACK_GENERATOR ZIP NSIS)
	endif()
elseif(APPLE)
	configure_file(${PROJECT_SOURCE_DIR}/platforms/osx/Info.plist.in
		${PROJECT_BINARY_DIR}/platforms/osx/Info.plist
		@ONLY)
	configure_file(${PROJECT_SOURCE_DIR}/platforms/osx/run.sh.in
		${PROJECT_BINARY_DIR}/platforms/osx/${APPLICATION_NAME}
		@ONLY)
	SET(CPACK_GENERATOR Bundle)
else()
	SET(CPACK_GENERATOR TGZ DEB)
endif()

SET(CPACK_PACKAGE_NAME ${APPLICATION_PACKAGE_NAME})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${APPLICATION_DESCRIPTION_SUMMARY})
SET(CPACK_PACKAGE_VENDOR ${APPLICATION_VENDOR_NAME})
SET(CPACK_PACKAGE_CONTACT ${APPLICATION_CONTACT})
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_BINARY_DIR}/README${DOCFILES_EXT}")
SET(CPACK_PACKAGE_VERSION_MAJOR ${APPLICATION_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${APPLICATION_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${APPLICATION_VERSION_PATCH}${APPLICATION_VERSION_BUILD})
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_BINARY_DIR}/COPYING${DOCFILES_EXT}")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY ${APPLICATION_PACKAGE_NAME}) # Useful for registry key and NSIS auto uninstaller

if(CMAKE_BUILD_TYPE MATCHES Debug)
	SET(CPACK_STRIP_FILES FALSE)
	SET(CPACK_SOURCE_STRIP_FILES FALSE)
else()
	SET(CPACK_STRIP_FILES TRUE)
	SET(CPACK_SOURCE_STRIP_FILES TRUE)
endif()

if(WIN32)
	# NSIS
	SET(CPACK_NSIS_DISPLAY_NAME "${APPLICATION_NAME}")
elseif(APPLE)
	if (NOT CPACK_SYSTEM_NAME)
		IF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
			SET(CPACK_SYSTEM_NAME amd64)
		ELSEIF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
			SET(CPACK_SYSTEM_NAME i386)
		ENDIF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
	endif()

	SET(CPACK_BUNDLE_NAME "${APPLICATION_NAME}")
else()
	# DEB instruction files
	configure_file (
		"${PROJECT_SOURCE_DIR}/platforms/debian/postinst.in"
		"${PROJECT_BINARY_DIR}/platforms/debian/postinst"
	)
	configure_file (
		"${PROJECT_SOURCE_DIR}/platforms/debian/prerm.in"
		"${PROJECT_BINARY_DIR}/platforms/debian/prerm"
	)

	if (NOT CPACK_SYSTEM_NAME)
		IF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
			SET(CPACK_SYSTEM_NAME amd64)
		ELSEIF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
			SET(CPACK_SYSTEM_NAME i386)
		ENDIF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
	endif()

	JOINLIST(PACKAGE_DEPS ", " DEBIAN_DEPS)

	SET(CPACK_DEBIAN_PACKAGE_NAME ${APPLICATION_PACKAGE_NAME})
	SET(CPACK_DEBIAN_PACKAGE_VERSION ${APPLICATION_VERSION})
	SET(CPACK_DEBIAN_PACKAGE_DEPENDS ${DEBIAN_DEPS})
	SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${PROJECT_BINARY_DIR}/platforms/debian/postinst;${PROJECT_BINARY_DIR}/platforms/debian/prerm;")
	SET(CPACK_DEBIAN_PACKAGE_SECTION "misc")
	# SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${DEB_ARCH})
endif()
SET(CPACK_PACKAGE_EXECUTABLES "${APPLICATION_EXE_NAME}" "${APPLICATION_NAME}")
include(CPack)
