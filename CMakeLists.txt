# Created By Alex Tsao
cmake_minimum_required(VERSION 3.14)
project(heilang)
set(CMAKE_CXX_STANDARD 17)
function(add_executable_dirs target property dirs)
    foreach (dir ${dirs} ${ARGN})
        aux_source_directory(${dir} sources)
    endforeach ()
    add_executable(${target} ${sources})
    target_include_directories(${target} ${property} ${dirs} ${ARGN})
endfunction()

set(LLVM_DIR "F:/LLVM_Debug/lib/cmake/llvm")
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs all)

add_executable_dirs(heilang PRIVATE .)
target_link_libraries(heilang ${llvm_libs})
