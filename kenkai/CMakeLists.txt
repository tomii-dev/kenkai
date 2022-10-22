add_executable(kenkai
    src/main.cpp
    src/game.cpp
    src/control.cpp

    src/component/animator.cpp

    src/object/object.cpp
    src/object/entity/entity.cpp
    src/object/entity/player.cpp

    src/world/world.cpp

    src/util/taskmanager.cpp
)

target_compile_features(kenkai PRIVATE cxx_std_17)

target_include_directories(kenkai
    PUBLIC include
    PUBLIC ${SFML_DIR}/include
)

target_link_directories(kenkai 
    PRIVATE ${SFML_DIR}/lib
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/filebuilder
)

target_link_libraries(kenkai
    sfml-window
    sfml-system
    sfml-graphics
    filebuilder
)