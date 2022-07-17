BlurCamBack
===========

Blurring the background of the webcam.

Table of Contents
=================
<!--ts-->
  * [Build](#build)
  * [Dependency](#dependency)
  * [Tests](#tests)
<!--te-->

Build
=====

Linux
-----

```bash
mkdir build && cd build && cmake .. && make
```

Dependency
==========
  * gcc
  * Valgrind
  * OpenCV
  * fmt

Tests
=====

Run unit tests
--------------

```bash
./build/bin/BlurCamBack_unit
```

Run performance tests
---------------------

```bash
./build/bin/BlurCamBack_bench
```

Memory leak tests(Valgrind)
--------

```bash
(cd build && ctest -T memcheck)
```
