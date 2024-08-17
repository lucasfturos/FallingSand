# -------------------------------------------------------------------

set(SRC_HEADERS
    FallingSand/falling_sand.hpp
    Render/render.hpp
    SandTetrix/sand_tetrix.hpp
)

set(SRC_SOURCES
    FallingSand/falling_sand.cpp
    Render/render.cpp
    SandTetrix/draw.cpp
    SandTetrix/logic.cpp
    SandTetrix/sand_tetrix.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} 
    ${SRC_HEADERS} 
    ${SRC_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
    # SFML
    PRIVATE sfml-graphics
    PRIVATE sfml-window
    PRIVATE sfml-system
)

# -------------------------------------------------------------------