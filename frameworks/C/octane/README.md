# OCTANE

Benchmarks for the [octane](http://github.com/simongui/octane) library.

JSON serialisation is using RapidJSON library.

### Test sources

 * [Plaintext](src/responders/sds_responder.c)
 * [JSON](src/responders/sds_responder.c)

## Software Versions

The tests were run with:

 * [Lockless memory allocator](https://locklessinc.com/)
 * [RapidJSON](http://rapidjson.org/)
 * [libuv](http://libuv.org/)

Please check the versions in the installation and build scripts.

## Test URLs

 * Plaintext - `http://localhost:8080/plaintext`
 * JSON - `http://localhost:8080/json` 
