
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h" "main.cpp")

set_target_properties(
	CMakeProject1 PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)