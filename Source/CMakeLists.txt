file(GLOB_RECURSE SRC_FILES *.cpp)

add_library(SDLEngine STATIC ${SRC_FILES})

target_link_libraries(SDLEngine
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    ${FREETYPE}
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)