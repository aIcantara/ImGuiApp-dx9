cmake_minimum_required(VERSION 3.15)

project(ImGuiApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(third-party/imgui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ui/window.cpp
    src/ui/draw.cpp
    src/ui/fonts/fonts.cpp
)

if (NOT "${DXSDK_DIR}" STREQUAL "")
    target_include_directories(${PROJECT_NAME} PUBLIC "${DXSDK_DIR}/Include")
    target_link_directories(${PROJECT_NAME} PUBLIC "${DXSDK_DIR}/Lib/$<IF:$<BOOL:$<STREQUAL:${CMAKE_SIZEOF_VOID_P},8>>,x64,x86>")
elseif (NOT "$ENV{DXSDK_DIR}" STREQUAL "")
    target_include_directories(${PROJECT_NAME} PUBLIC "$ENV{DXSDK_DIR}/Include")
    target_link_directories(${PROJECT_NAME} PUBLIC "$ENV{DXSDK_DIR}/Lib/$<IF:$<BOOL:$<STREQUAL:${CMAKE_SIZEOF_VOID_P},8>>,x64,x86>")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PUBLIC d3d9 d3dx9 imgui)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")