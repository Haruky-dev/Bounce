cmake_minimum_required( VERSION 3.26 )

project(bounce VERSION 0.90.0 LANGUAGES CXX)

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

find_package( SFML 3 REQUIRED COMPONENTS Graphics Window System Audio REQUIRED )

# src files (.cpp)
add_executable( ${PROJECT_NAME}
    src/main.cpp
    src/Game.cpp

    src/entities/Ball.cpp
    src/entities/Human.cpp
    src/entities/ai/Computer.cpp
    src/entities/ai/Neuron.cpp

    src/tools/Math.cpp
    src/tools/Json.cpp
    src/tools/Flags.cpp
    src/tools/Constants.cpp
    src/tools/FrameRate.cpp
    src/tools/Collision.cpp

    src/cache/FontCache.cpp
    src/cache/SFX.cpp
    src/cache/TextureCache.cpp

    src/engine/visuals/LoadUI.cpp
    src/engine/visuals/MenuUI.cpp
    src/engine/visuals/PlayUI.cpp
    src/engine/visuals/PauseUI.cpp
    src/engine/visuals/SetUI.cpp
    src/engine/visuals/EndUI.cpp
    src/engine/visuals/QuitUI.cpp

    src/engine/Manager.cpp
    src/engine/Dispatcher.cpp

    src/engine/layers/LoadLayer.cpp
    src/engine/layers/MenuLayer.cpp
    src/engine/layers/PlayLayer.cpp
    src/engine/layers/PauseLayer.cpp
    src/engine/layers/SetLayer.cpp
    src/engine/layers/EndLayer.cpp
    src/engine/layers/QuitLayer.cpp

    src/engine/io/Constraint.cpp
    src/engine/io/Input.cpp

    src/engine/features/Motion.cpp
    src/engine/features/Animation.cpp

    src/buffing/BuffOperator.cpp
    src/buffing/Generator.cpp
)

# link SFML libs
target_link_libraries( ${PROJECT_NAME} PRIVATE
    sfml-audio
    sfml-window
    sfml-system
    sfml-graphics
)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties( ${PROJECT_NAME} PROPERTIES OUTPUT_NAME "game" )
set_source_files_properties( ${PROJECT_SOURCE_DIR}/src/tools/Json.cpp
    PROPERTIES OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/data/conf.json )

# inc assets/ in build
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${PROJECT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${PROJECT_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/data

    COMMENT "Copied [assets/] and [data/] directories..."
)
