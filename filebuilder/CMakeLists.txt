add_library(filebuilder STATIC
    src/filewriter.cpp
    src/filereader.cpp
    
    src/builder/animationbuilder.cpp
)

target_compile_features(filebuilder PRIVATE cxx_std_17)

target_include_directories(filebuilder
    PUBLIC include
)