cmake_minimum_required(VERSION 3.15)
project(GameEngine)

include_directories(include)

# --- GLFW ---
add_subdirectory(thirdparty/glfw)

# --- GLAD ---
add_library(glad
    thirdparty/glad/src/glad.c
)

target_include_directories(glad PUBLIC thirdparty/glad/include)

file(GLOB_RECURSE SOURCES src/*.c)

add_executable(GameEngine ${SOURCES})

target_include_directories(GameEngine
    PRIVATE src
)

# Link everything together
target_link_libraries(GameEngine
    PRIVATE glfw
    PRIVATE glad
)

# On some platforms you also need extra system libs for GLFW
if (WIN32)
    target_link_libraries(GameEngine PRIVATE opengl32)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(GameEngine PRIVATE dl pthread X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL)
endif()

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/") # This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the project