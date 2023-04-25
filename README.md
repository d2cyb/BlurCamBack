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

Docker
======

Build
-----

```bash
docker build -t blur-background --target build .
```

Test
-----

```bash
docker build -t blur-background --target test .
```

Export binary app from container
--------------------------------

```bash
DOCKER_BUILDKIT=1 docker build -t blur-background-app --target app-export --output type=local,dest=out .
```


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
