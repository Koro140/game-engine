cmake_minimum_required(VERSION 3.15)
project(GameEngine)

include_directories(include)

# --- GLFW ---
add_subdirectory(thirdparty/glfw)

# --- GLAD ---
add_library(glad
    thirdparty/glad/src/glad.c
)

target_include_directories(glad PUBLIC thirdparty/glad/include thirdparty/nuklear)

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