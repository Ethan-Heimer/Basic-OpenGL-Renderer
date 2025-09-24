# g++ -I ./include -o test main.cpp glad.cpp 
# -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl


cmake_minimum_required(VERSION 3.10)

set(NAME Renderer)
project(${NAME} VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard (e.g., C++17, C++20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)        
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source files for the executable
add_executable(${NAME}
    main.cpp
    src/glad.cpp
    src/app.cpp
    src/window.cpp
    src/errors.cpp
    src/jsonloader.cpp
    src/shader.cpp
    src/object.cpp
    src/renderer.cpp
    src/input.cpp
)


message("Ensuring Json Parser is installed")

include(FetchContent)
FetchContent_Declare(
    Json
    GIT_REPOSITORY "https://github.com/nlohmann/json"
    GIT_TAG "origin/master"
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/Json"
)
FetchContent_MakeAvailable(Json)

# Optional: Add include directories if you have custom headers
target_include_directories(${NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(${NAME} PRIVATE ./Json/include)

#target_link_libraries(${NAME} nlohmann_json)

target_link_libraries(${NAME} glfw)
target_link_libraries(${NAME} GLU)
target_link_libraries(${NAME} GL)
target_link_libraries(${NAME} Xrandr)
target_link_libraries(${NAME} Xxf86vm)
target_link_libraries(${NAME} Xi)
target_link_libraries(${NAME} Xinerama)
target_link_libraries(${NAME} X11)
target_link_libraries(${NAME} rt)
target_link_libraries(${NAME} dl)
