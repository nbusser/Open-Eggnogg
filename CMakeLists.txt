cmake_minimum_required(VERSION 3.16) # This project requires CMake 3.16 or newer
project(OpenEggnogg LANGUAGES CXX) # Defines the project name and the language used

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Sets the output directory for executables
option(BUILD_SHARED_LIBS "Build shared libraries" OFF) # Embedds libraries into the executable

# Downloads and includes SFML library from GitHub
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x) # TODO: update to SFML 3.0 when it's released
FetchContent_MakeAvailable(SFML)

# Adds the executable and links the SFML library
add_executable(OpenEggnogg src/main.cpp src/Character.cpp)
target_link_libraries(OpenEggnogg PRIVATE sfml-graphics)
target_compile_features(OpenEggnogg PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET OpenEggnogg
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:OpenEggnogg>
        VERBATIM)
endif()

install(TARGETS OpenEggnogg)
