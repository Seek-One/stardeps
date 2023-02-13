# stardeps
Cross platform dependencies builder

StarDeps allows you to build libraries from sources.

## Requirements

  * CMake
  * Qt version 5

## Compiling from source

Install dependencies:

```
apt-get install git cmake qtbase5-dev qttools5-dev qttools5-dev-tools
```

Get the code:

```
git clone https://github.com/Jet1oeil/stardeps.git && cd stardeps
```

Compile:

```
./build.sh regen
make
```

## Usage

```
stardeps COMMAND [OPTIONS]
```
You can use the following COMMAND:

```
createenv
  Initialize an environment in the selected.
prepare PACKAGE_NAME
  Prepare package name from sources
help
  Display some help about command usage.
version
  Print application version
```

## Create environnement

Intialize environment to select compiler.

```
stardeps createenv TARGET_PLATFORM
```

You can use the following TARGET_PLATFORM :

```
linux-gcc-32: Use linux gcc 32 bits compiler
linux-gcc-64: Use linux gcc 64 bits compiler
win32-gcc: Use windows mingw32 gcc 32 bits (cross-)compiler
darwin-clang-64: Use macOS darwin gcc 64 bits compiler
```

Directory structure will have the following scheme :

```
./
 |-- ve.env  
 |-- PACKAGE_NAME[-VERSION]
 |   |-- src/
 |   |-- build/
 |   |-- release/
 |-- PACKAGE_NAME[-VERSION]
 |   |-- src/
 |   |-- ...
```

## Prepare package sources

This command downloads the sources of the selected package and configure the version to use.

```
stardeps prepare PACKAGE_NAME [OPTIONS]
```

## Configure package sources

This command allows you to configure the build.

```
stardeps configure PACKAGE_NAME [OPTIONS]
```

## Build package sources

This command allows you to build the package from the configure commands.

```
stardeps build PACKAGE_NAME [OPTIONS]
```

## Install package sources

This command allows you to install the build in the release path.

```
stardeps install PACKAGE_NAME [OPTIONS]

```

## List of options

You can use the following OPTIONS:

``` 
LIST OF ARGUMENTS
   --version 
         display application version
   --help 
         show help
   --verbose=[normal,full]
         set level of verbosity.

CUSTOM ENVIRONMENT VARIABLE
   you can define some environment in the ve.env file.
         FORMULAS_DIR: path to the formula directory
         VE_PKG_CONFIG_PATH: path to environment the .pkgconfig-files directory path

LIST OF COMMANDS: ENVIRONMENT
   createenv TARGET_PLATFORM
         create an environment directory and a ve.env file with useful environment variables.

LIST OF ARGUMENTS FOR ENVIRONMENT COMMANDS
   --pkg-config-mode=SEARCH_MODE (default: default)
         set search mode policy for pkg-config.
              system: search only in system (PKG_CONFIG_LIBDIR or PKG_CONFIG_PATH will not be set)
              environment: search only in current environment (define PKG_CONFIG_LIBDIR to the .pkgconfig-files directory path)
              default: search in environment first then in system (define PKG_CONFIG_PATH to the .pkgconfig-files directory path)

LIST OF COMMANDS: PACKAGE
   prepare PACKAGE_NAME
         get the sources of the package in the sources directory.
   configure PACKAGE_NAME
         configure the sources of the package in the build directory.
   build PACKAGE_NAME
         run the build command in the build directory.
   install PACKAGE_NAME
         install the generated package files in the release directory.

LIST OF ARGUMENTS FOR PACKAGE COMMANDS
   --formulas-dir=DIR
         set DIR as formula dir.
   --previous-steps
         execute all previous commands steps.

   --pkg-version=VERSION
         define the version of the package to build.
   --pkg-option=OPTION[:OPTION_MODE1[,OPTION_MODE2]]
         tell use the option specified in the formula of the package. You can use this option multiple times.
         you can also specify some mode for the option depending on formula.

   --scm-tag-version=VERSION
         define the tag version in the SCM to use.
   --scm-branch-version=VERSION
         define the branch version in the SCM to use.

   --pkg-config-mode=SEARCH_MODE (default: default)
         set search mode policy for pkg-config. If not set use policy from environment.
              system: search only in system (PKG_CONFIG_LIBDIR or PKG_CONFIG_PATH will not be set)
              environment: search only in current environment (define PKG_CONFIG_LIBDIR to the .pkgconfig-files directory path)
              default: search in environment first then in system (define PKG_CONFIG_PATH to the .pkgconfig-files directory path)
```

## Formulas

Package are described in a JSON file called formula.

* GIT
* MAKE
* RSYNC


## Supported package

startdeps support build of the following package :

* openssl : https://www.openssl.org/
* curl : https://curl.haxx.se/
* live555 : http://live555.com/
* ffmpeg : https://ffmpeg.org/


     
