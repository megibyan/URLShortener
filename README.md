URLShortener
============

[![Build Status](https://travis-ci.org/bowlofstew/served.png)](https://travis-ci.org/bowlofstew/served)

## Overview

A simple API to parse long URL to a shorter version, and retrieve the longer version from the latter.

URLShortener builds upon libz, [Boost](http://www.boost.org/), [Served](https://github.com/meltwater/served), and [Crypto++](https://cryptopp.com).

### Features:

* ✅ Shorten longer URL
* ✅ Retrieve original long URL from a short one, if possible

## Installation

### Requirements

* [Required] - libz
* [Required] - [Boost (1.78 or newer)](http://www.boost.org/)
* [Required] - [Served (1.0 or newer)](https://github.com/meltwater/served)
* [Required] - [Crypto++ (8.6 or newer)](https://cryptopp.com)
* [Required] - [CMake (3.14 or newer)](https://cmake.org)
* [Required] - [C++ (17 or newer)](https://en.cppreference.com/w/cpp/17)

### Provided endpoint

Endpoint               | Purpose
---------------------- | -----------------------------------
/encode                | shorten a URL
/decode                | try to retrieve longer version of a URL

*For detailed information see ../Auxiliary/Documentation/html/index.html*

### System Compatibility

OS           | Compiler      | Status
------------ | ------------- | -------------
OSX Intel    | Clang 13.0    | Working
OSX Intel    | Clang 12.0.5  | Working
OSX ARM    	 | Clang 12.0.5  | Working


### Building

```bash
$ git clone https://github.com/megibyan/URLShortener.git
$ cd URLShortener
$ mkdir Build && cd Build
$ cmake ../ && make -j12
```

or use `Build.sh` located at `Auxiliary/Scripts`

```bash
$ ./Build
```

### Usage
```bash
$ ./URLShortener
```

In a separate tab:

```bash
$ curl --header "Content-Type: application/string" --request POST --data "google.com" http://localhost:8080/encode
$ curl --header "Content-Type: application/string" --request POST --data "https://url.short/KbLNv" http://localhost:8080/decode
```

or use `URLShortener.sh` (on Intel only) located at `Auxiliary/Scripts`

```bash
$ cd ../URLShortener/Scripts
$ ./URLShortener -e "google.com"
$ ./URLShortener -d "https://url.short/KbLNv"
```

### Testing

```bash
$ cd ../Build
$ make Test -j12 && ./Test
```

or use `Test.sh` located at `Auxiliary/Scripts`

```bash
$ ./Test
```

## License
[MIT](https://choosealicense.com/licenses/mit/)

## Future improvements
 - Get rid of Served and do the server handling using boost natively.
   - There are a couple of issues in the library, and it's not maintained anymore.
 - Support for other OSs.
   - This should be as simple as building third party dependencies for the platforms.
 - Short URL can be 7 characters fixed.
 - Use a non SQL DB instead of memory hashing.
 - Third party dependencies should have better place to live.
 - Rebuild `boost` with `-DCXX_VISIBILITY_PRESET=hidden`.

### Known issues
  - In case of internal crash the service process may still live because of a corner case bug in `Served` library.
  - Current encoding guarantees the uniqueness but doesn't guaranty the short URL length.
