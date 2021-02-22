# How to create your own bot

## Common structure of bot
```
├── CMakeLists.txt
├── commands
│   ├── base_command.hpp
│   ├── docs_search_command.hpp
│   ├── // Other commands.
├── handlers
│   └── message_handler.hpp
|   └── // Other event handlers.
├── long_poller
│   └── long_poller.hpp
|── utils
|   └── string_utils.hpp
├── main.cpp
```
## Preparation
```
mkdir example_bot
cd example_bot
git clone https://github.com/duonumerouno/cpp_vk_lib.git
```

Of cource, you can add library as a submodule in your project.

Next, you should to create `bot` directory with following script
```
include_directories(../cpp_vk_lib/lib/include)
include_directories(../cpp_vk_lib/dependencies/simdjson/include)
include_directories(../cpp_vk_lib/dependencies)

set(SOURCES
    # Your source files.
    main.cpp
)
add_executable(test ${SOURCES})

target_link_libraries(test curl curlpp -Lbuild cpp_vk_lib -L../cpp_vk_lib/dependencies/simdjson simdjson)
```


## Creating CMakeLists
Here is example CMake script to make bot and library work together:
```
cmake_minimum_required(VERSION 3.9)

project(example_bot
    DESCRIPTION "C++ vk library"
    LANGUAGES CXX
)

set(CMAKE_C_COMPILER /usr/bin/clang CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "" FORCE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MACOSX_RPATH OFF)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)
set(EXECUTABLE_OUTPUT_PATH ../build)

add_subdirectory(cpp_vk_lib)
add_subdirectory(example_bot)
```
