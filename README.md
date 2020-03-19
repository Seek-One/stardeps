# stardeps
Cross platform dependencies builder

StarDeps allow you to build libraries from sources.

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

Intialize environnement to select compiler.

```
stardeps createenv TARGET_PLATFORM
```

You can use the following TARGET_PLATFORM :

```
  linux-gcc-32: Use linux gcc 32 bits compiler
  linux-gcc-64: Use linux gcc 64 bits compiler
  win32-gcc: Use windows mingw32 gcc 32 bits (cross-)compiler
```

Directory structure will have the following scheme :

```
./
 |-- ve.env  
 |-- src/  
 |   |-- PACKAGE_NAME[-VERSION]  
 |-- build/  
 |   |-- PACKAGE_NAME[-VERSION]  
 |-- release/  
 |   |-- PACKAGE_NAME[-VERSION]  
```

## Prepare package sources

This command downloads the sources of the selected package and configure the version to use.

```
stardeps prepare PACKAGE_NAME [OPTIONS]
```

You can use the following OPTIONS:

```
  --version=[VERSION]
      Set the target version name. This defines the target source directory name as src/PACKAGE_NAME[-VERSION]. If no version is set it will use the current developpement version.
  --scm-branch-version=[VERSION]
      Use this version instead of the --version to checkout in SCM.
  --scm-tag-version=[VERSION]
      Use this version instead of the --version to checkout in SCM.
```

## Configure package sources

This command allow you to configure th build.

```
stardeps configure PACKAGE_NAME [OPTIONS]
```

You can use the following OPTIONS:

```
  --version=[VERSION]
      Set the target version name to build.
```

## Supported package

startdeps support build of the folowwing package :

* openssl : https://www.openssl.org/
* curl : https://curl.haxx.se/


     
