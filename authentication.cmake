cmake_minimum_required(VERSION 3.12)
project(authentication_lib VERSION 1.0)

# Specify C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set position independent code for shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

# Collect all source files
set(SOURCES
    authentication_library.cpp
    User.cpp
    CryptoUtils.cpp
    RoutingNumberGenerator.cpp
)

# Create shared library instead of executable
add_library(authentication_lib SHARED ${SOURCES})

# Link OpenSSL
target_link_libraries(authentication_lib PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(authentication_lib PRIVATE ${OPENSSL_INCLUDE_DIR})

# Add compiler flags if needed
target_compile_options(authentication_lib PRIVATE -Wno-deprecated-declarations)

# Set output names based on platform
if(WIN32)
    set_target_properties(authentication_lib PROPERTIES 
        PREFIX ""
        OUTPUT_NAME "authentication"
        SUFFIX ".dll"
    )
elseif(APPLE)
    set_target_properties(authentication_lib PROPERTIES 
        OUTPUT_NAME "authentication"
        SUFFIX ".dylib"
    )
else() # Linux
    set_target_properties(authentication_lib PROPERTIES 
        OUTPUT_NAME "authentication"
        SUFFIX ".so"
    )
endif()