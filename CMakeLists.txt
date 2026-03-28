cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(GameEngine)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/fetched)

# GLFW
find_package(glfw3 3.3 REQUIRED)

# GLAD
include_directories(thirdparty/glad/include)
include_directories(thirdparty/stb_image)

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        0af55ccecd98d4e5a8d1fad7de25ba429d60e863
)

# EnTT
FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG        v3.13.2
)

FetchContent_MakeAvailable(glm entt)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRC
    Core/Application.cpp
    Core/Model.cpp

    Core/Renderer/Renderer.cpp
    Core/Renderer/Shader.cpp
    Core/Renderer/Texture.cpp

    Core/Input/Input.cpp

    Core/ResourceManager/ResourceManager.cpp
)

add_executable(GameEngine
    thirdparty/glad/src/glad.c
    ${SRC}

    App/main.cpp
    App/AppLayer.cpp
    App/PauseLayer.cpp
)

target_compile_definitions(GameEngine PUBLIC "RESOURCES_PATH=\"${CMAKE_SOURCE_DIR}/res/\"")

target_link_libraries(GameEngine PRIVATE
    glm::glm
    glfw
    EnTT::EnTT
)