# Blue
[![CodeFactor](https://www.codefactor.io/repository/github/naranbataar/blue/badge)](https://www.codefactor.io/repository/github/naranbataar/blue)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/529281ddf87d41df94beab97734e577d)](https://www.codacy.com/manual/Naranbataar/Blue?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Naranbataar/Blue&amp;utm_campaign=Badge_Grade)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/Naranbataar/Blue.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Naranbataar/Blue/context:cpp)
[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/)

A minimal tool that searches duplicated files in the current directory using its MD5 checksum and size

## Installation
You need just a C compiler with the default libraries, and `make`
```shell
# Compiles to `blue`
make
# Optional, copy the binary to /usr/local/bin
sudo make install
```

## Example
```shell
# Searches a file
blue 18771d92fec7fc9374ef7c5a3e2ab50f 64
```
```shell
./file1
./file2
./files/file3
```
