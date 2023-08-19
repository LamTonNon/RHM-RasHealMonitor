cmake_minimum_required(VERSION 3.5)

project(FanControler)

############################################################
# Create a library
############################################################

#Generate the shared library from the library sources
add_library(fan_api_lib SHARED 
    src/fan_api.c
)
add_library(fanapi::library ALIAS fan_api_lib)

target_include_directories(fan_api_lib
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(cooler_service
    src/main.c
)

# link the new fan_api_lib target with the cooler_service target
target_link_libraries( cooler_service
    fanapi::library
    -l:libi2c.a
)
