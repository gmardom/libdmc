# DM Libraries

A collection of libraries for C programming language.

## Usage

#### Building standalone library

```shell
cmake -Bbuild -H. -GNinja
cd ./build
ninja
```

#### Using inside Cmake projct

```cmake
add_subdirectory(path/to/dm-lib)
target_link_libraries(<target> LINK_PUBLIC dm-lib)
```
