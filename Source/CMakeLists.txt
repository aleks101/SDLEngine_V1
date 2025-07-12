file(GLOB_RECURSE SRC_FILES *.cpp)

add_library(SDLEngine STATIC ${SRC_FILES})

# Set output directory for the built static library
set_target_properties(SDLEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_link_libraries(SDLEngine
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    #FreeType::FreeType
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)