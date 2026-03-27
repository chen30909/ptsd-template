set(CMAKE_POLICY_DEFAULT_CMP0000 NEW)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

cmake_minimum_required(VERSION 3.16)
project(LINEPOP2)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    ptsd

    URL         https://github.com/ntut-open-source-club/practical-tools-for-simple-design/archive/refs/tags/v0.2.zip

    # Or alternatively if you want to use a specific git commit instead of a release:
    # GIT_REPOSITORY  https://github.com/ntut-open-source-club/practical-tools-for-simple-design.git
    # GIT_TAG         <git_tag>

    SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/PTSD
)

FetchContent_MakeAvailable(ptsd)

include(files.cmake)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM INCLUDE_FILES PREPEND ${INCLUDE_DIR}/)

# file(GLOB_RECURSE SRC_FILES src/*)
# file(GLOB_RECURSE HEADER_FILES include/*)

add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Character.cpp
    ${SRC_DIR}/DebugMode.cpp
    ${SRC_DIR}/GameCharacter.cpp
    ${SRC_DIR}/Global.cpp
    ${SRC_DIR}/PhaseMainAction.cpp
    ${SRC_DIR}/PhaseResourceManager.cpp
    ${SRC_DIR}/StageObject.cpp
    ${SRC_DIR}/JumpPage.cpp
    ${SRC_DIR}/AppStage.cpp
    ${SRC_DIR}/AppInit.cpp
    ${SRC_DIR}/StageObjectInit.cpp
    ${SRC_DIR}/StageObjectCheck.cpp
    ${SRC_DIR}/StageObjectDisappear.cpp
    ${SRC_DIR}/StageObjectItemUsed.cpp
    ${SRC_DIR}/StageObjectMakeDisappear.cpp
    ${SRC_DIR}/StageObjectShuffle.cpp
    ${SRC_DIR}/StageObjectUpdate.cpp
    ${SRC_FILES}
    ${HEADER_FILES}
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# Always use the full path to Resources
target_compile_definitions(${PROJECT_NAME} PRIVATE GA_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")

# Add an install rule to install the Resources directory
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Resources DESTINATION .)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${DEPENDENCY_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2main
    PTSD
)
