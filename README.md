# Dependencies

`make`, `cmake`

# Build

Start with update submodules (Catch2):
```
$ git submodule update --init
```

Create new directory for build and use cmake
```
$ mkdir build && cd build
$ cmake .. && make
```

# Test
Tests are located in `test` directory and includes:
- expressions
- complex expressions
- invalid inputs
- operators priority
- and parentheses

## Run tests with:
```
./build_dir/test/tests
```
