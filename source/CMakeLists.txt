cmake_minimum_required(VERSION 2.8)
project(vscode-cpp-remote-debug)

# compile folder1/file1.cxx into executable file1
add_executable(file1 folder1/file1.cxx)

# add root directory as search path so that it can be
# seen from within folder1/file1.cxx
target_include_directories(file1 PRIVATE . )
