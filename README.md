# Blue
[![CodeFactor](https://www.codefactor.io/repository/github/naranbataar/blue/badge)](https://www.codefactor.io/repository/github/naranbataar/blue)
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
