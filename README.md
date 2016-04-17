# easyunit

This is my build of Barthelemy Dagenais' EasyUnit.

## EasyUnit 1.0 Readme file

### Contents

* Description
* Installation
* Documentation
* Changelog
* Archive contents

### Description

EasyUnit:

* a unit testing framework for C++ which is extremely simple and easely customizable;
* EC++ compatible for embedded version (no STL, RTTI, multiple inheritance and exceptions);
* no boilerplate code : 0 line, none, niet, nada;
* results output and test execution are entirely customizable;
* default configuration are optimized for general needs;
* based on Michael Feathers' CppUnitLite framework.
  
EasyUnit was created to ease creation and use of unit testing in C++. Most of the existing frameworks ask programmers to create objects and use macros to administer test cases in addition to write their own test cases. It is the author belief that boilerplate code and taking care of test administration discourage programmers and students to use unit testing even if it is representing one line of code per test case.

EasyUnit is released under LGPL. See LICENSE.md for more information.

### Installation

To install easyunit, unzip all files. The headers are located in the easyunit folder. Compile your own version with source files contained in src folder. There is a makefile for UNIX in the src folder.

For detailled information, go to this web page: http://easyunit.sourceforge.net/index.php?page=installation&folder=guide

### Documentation

Documentation may be found on easyunit web site: http://easyunit.sourceforge.net

### Changelog

1.0 Release

* Added Doxygen documentation
* Improved TESTF macro structure and performance
* Added new ASSERT macros
* Fixed a bug in the execution loop of DefaultTestPrinter

1.0 Beta2 Release

* Added examples
* Added DECLARE macro to use with fixtures (no global variables anymore)
* DefaultTestPrinter is now customizable
* Put all classes under easyunit namespace
* Added readme and license textfiles
* Added support for exceptions (reported as "error")

### Archive contents

readme.txt        This file  
license.txt       EasyUnit license  
/easyunit         EasyUnit header files  
/examples         Examples on how to use EasyUnit  
/src              EasyUnit sources  
/doc              Doxygen documentation of EasyUnit classes

Copyright (C) 2004 Barthelemy Dagenais  
barthelemy@prologique.com
