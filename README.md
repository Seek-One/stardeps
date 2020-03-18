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
stardeps createenv
```

Directory structure will have the following scheme :

```
[virtual-enrivonment-root]/  
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
  --scm-tag-version=[VERSION]:
      Use this version instead of the --version to checkout in SCM.
```
