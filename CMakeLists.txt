cmake_minimum_required(VERSION 3.24)
project(calc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

set(src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(cpp_files
	"${src_dir}/main.cpp"
	"${src_dir}/token.cpp"
	"${src_dir}/lexer.cpp"
)

add_executable(calc ${cpp_files} ${header_files})
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
