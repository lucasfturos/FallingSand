# -------------------------------------------------------------------

add_executable(${PROJECT_NAME} 
    main.cpp
)

add_subdirectory(FallingSand)
add_subdirectory(Menu)
add_subdirectory(Render)
add_subdirectory(SandTetrix)

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