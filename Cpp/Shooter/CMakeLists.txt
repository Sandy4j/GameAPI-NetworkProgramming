cmake_minimum_required(VERSION 3.15)
project(Shooter VERSION 1.0 LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# OpenGL
find_package(OpenGL REQUIRED)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/libraries/include
    ${PROJECT_SOURCE_DIR}/game/ray
    ${PROJECT_SOURCE_DIR}/game/logic
    ${PROJECT_SOURCE_DIR}/game/entity
    ${PROJECT_SOURCE_DIR}/game/entity/systems
    ${PROJECT_SOURCE_DIR}/game/entity/components
    ${PROJECT_SOURCE_DIR}/assets/data_levels
    ${PROJECT_SOURCE_DIR}/game/level
    ${PROJECT_SOURCE_DIR}/game/time
    ${PROJECT_SOURCE_DIR}/core/engine/input
    ${PROJECT_SOURCE_DIR}/core/engine/state/states
    ${PROJECT_SOURCE_DIR}/core/engine/state
    ${PROJECT_SOURCE_DIR}/core/engine/singleton
    ${PROJECT_SOURCE_DIR}/core/engine/observer
    ${PROJECT_SOURCE_DIR}/core/engine/factory
    ${PROJECT_SOURCE_DIR}/core/engine/decorator
    ${PROJECT_SOURCE_DIR}/core/patterns
    ${PROJECT_SOURCE_DIR}/core/engine
    ${PROJECT_SOURCE_DIR}/core/graphics_pipeline
    ${PROJECT_SOURCE_DIR}/core
)

# Library directories
link_directories(${PROJECT_SOURCE_DIR}/libraries/lib)

# Collect all source files
set(CORE_SOURCES
    core/Engine.cpp
    core/engine/input/command.cpp
    core/engine/singleton/GameManager.cpp
    core/engine/singleton/InputManager.cpp
    core/engine/singleton/RenderManager.cpp
    core/engine/singleton/TimeManager.cpp
    core/engine/singleton/UIManager.cpp
    core/engine/state/GameState.cpp
    core/engine/state/states/GameOverState.cpp
    core/engine/state/states/GameplayState.cpp
    core/engine/state/states/LobyState.cpp
    core/engine/state/states/MainMenuState.cpp
    core/engine/state/states/PauseState.cpp
)

set(GRAPHICS_SOURCES
    core/graphics_pipeline/EBO.cpp
    core/graphics_pipeline/ShaderProgram.cpp
    core/graphics_pipeline/stb.cpp
    core/graphics_pipeline/Texture.cpp
    core/graphics_pipeline/VAO.cpp
    core/graphics_pipeline/VBO.cpp
)

set(GAME_SOURCES
    game/entity/systems/SpriteSystem.cpp
    game/level/Level.cpp
    game/logic/GunSystem.cpp
    game/logic/PlayerController.cpp
    game/ray/RayLine.cpp
)

set(IMGUI_SOURCES
    libraries/include/imgui/imgui.cpp
    libraries/include/imgui/imgui_demo.cpp
    libraries/include/imgui/imgui_draw.cpp
    libraries/include/imgui/imgui_impl_glfw.cpp
    libraries/include/imgui/imgui_impl_opengl3.cpp
    libraries/include/imgui/imgui_tables.cpp
    libraries/include/imgui/imgui_widgets.cpp
)

set(GLM_SOURCES
    libraries/include/glm/detail/glm.cpp
)

set(GLAD_SOURCES
    glad.c
)

# Main executable
add_executable(${PROJECT_NAME}
    Shooter.cpp
    ${CORE_SOURCES}
    ${GRAPHICS_SOURCES}
    ${GAME_SOURCES}
    ${IMGUI_SOURCES}
    ${GLM_SOURCES}
    ${GLAD_SOURCES}
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw3
)

# Platform-specific settings
if(WIN32)
    # Export symbols for NVIDIA Optimus
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        WIN32
        _CONSOLE
        UNICODE
        _UNICODE
    )
    
    # Link additional Windows libraries
    target_link_libraries(${PROJECT_NAME}
        opengl32
    )
    
    # Set subsystem to console
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
endif()

if(UNIX AND NOT APPLE)
    # Linux-specific settings
    target_link_libraries(${PROJECT_NAME}
        dl
        pthread
    )
endif()

if(APPLE)
    # macOS-specific settings
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    
    target_link_libraries(${PROJECT_NAME}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
    )
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Copy assets to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/core/graphics_pipeline/shaders
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/core/graphics_pipeline/shaders
)

# Optional: Copy DLLs on Windows
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/libraries/lib/glfw3.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copying GLFW DLL to output directory"
    )
endif()

# Installation rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

install(DIRECTORY assets/
    DESTINATION bin/assets
)

install(DIRECTORY core/graphics_pipeline/shaders/
    DESTINATION bin/core/graphics_pipeline/shaders
)

# Print configuration summary
message(STATUS "")
message(STATUS "========== Build Configuration ==========")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "=========================================")
message(STATUS "")