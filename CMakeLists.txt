set(CMAKE_POLICY_DEFAULT_CMP0000 NEW)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

cmake_minimum_required(VERSION 3.16)

project(LINEPOP2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0135 NEW)

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "Minimum macOS version" FORCE)
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_FULLY_DISCONNECTED ON CACHE BOOL "Use vendored dependencies without downloading" FORCE)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/PTSD/CMakeLists.txt")
    add_subdirectory(PTSD)
else()
    FetchContent_Declare(
        ptsd
        URL         https://github.com/ntut-open-source-club/practical-tools-for-simple-design/archive/refs/tags/v0.2.zip
        SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/PTSD
    )
    FetchContent_MakeAvailable(ptsd)
endif()

set(PTSD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/PTSD")
set(PTSD_PUBLIC_INCLUDE_DIRS
    "${PTSD_ROOT}/include"
    "${PTSD_ROOT}/lib/sdl2/include"
    "${PTSD_ROOT}/lib/glew/include"
    "${PTSD_ROOT}/lib/spdlog/include"
    "${PTSD_ROOT}/lib/glm"
    "${PTSD_ROOT}/lib/imgui"
    "${PTSD_ROOT}/lib/imgui/backends"
)

foreach(REQUIRED_FILE
    "${PTSD_ROOT}/include/pch.hpp"
    "${PTSD_ROOT}/include/Util/GameObject.hpp"
    "${PTSD_ROOT}/lib/glm/glm/vec2.hpp"
)
    if(NOT EXISTS "${REQUIRED_FILE}")
        message(FATAL_ERROR
            "Missing required project dependency file: ${REQUIRED_FILE}\n"
            "Please re-extract the complete source package. Do not copy only src/include/Resources; the PTSD folder must be complete."
        )
    endif()
endforeach()

include(files.cmake)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
list(TRANSFORM SRC_FILES PREPEND "${SRC_DIR}/")
list(TRANSFORM INCLUDE_FILES PREPEND "${INCLUDE_DIR}/")

# file(GLOB_RECURSE SRC_FILES src/*)
# file(GLOB_RECURSE HEADER_FILES include/*)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
    ${INCLUDE_FILES}
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    SDL_MAIN_HANDLED
    RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources"
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    ${DEPENDENCY_INCLUDE_DIRS}
    ${PTSD_PUBLIC_INCLUDE_DIRS}
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    PTSD
)
