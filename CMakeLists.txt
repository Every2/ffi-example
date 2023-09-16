cmake_minimum_required(VERSION 3.8)
project(CMakeProject1)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Find Python
find_package(PythonLibs REQUIRED)

# Include Python headers
include_directories(${PYTHON_INCLUDE_DIRS})

# Create a Python extension module from addmodule.c
add_library(addTwoIntegers MODULE "src/addTwoIntegers.c" src/FFI.cc)

# Set the .pyd extension for the output
set_target_properties(addTwoIntegers PROPERTIES SUFFIX ".pyd")

# Link the Python libraries with the module
target_link_libraries(addTwoIntegers PRIVATE ${PYTHON_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET addTwoIntegers PROPERTY CXX_STANDARD 20)
endif()