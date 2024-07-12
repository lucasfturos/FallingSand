# -------------------------------------------------------------------

# List all the header files in the src directory
set(SRC_HEADERS
    Render/render.hpp
)

# List all the source files in the src directory
set(SRC_SOURCES
    Render/draw.cpp
    Render/handle.cpp
    Render/logic.cpp
    Render/render.cpp
    main.cpp
)

# Add executable target with source and header files
add_executable(${PROJECT_NAME} 
    ${SRC_HEADERS} 
    ${SRC_SOURCES}
)

# Specify libraries or flags to use when linking
target_link_libraries(${PROJECT_NAME}
    # SFML
    PRIVATE sfml-graphics
    PRIVATE sfml-window
    PRIVATE sfml-system
)

# -------------------------------------------------------------------