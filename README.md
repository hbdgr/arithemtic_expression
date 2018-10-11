# Dependencies

`make`, `cmake`

# Build

Start with update submodules (Catch2):
```
$ git submodule update --init
```

Create new dir for build and use cmake
```
$ mkdir build && cd build
$ cmake .. && make
```

# Test

Run tests with:
```
./test/tests
```
