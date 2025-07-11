file(GLOB_RECURSE SRC_FILES *.cpp)

add_library(SDLEngine STATIC ${SRC_FILES})

###### NOVO

set(SDL_TTF_URL "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.24.0/SDL2_ttf-devel-2.24.0-mingw.tar.gz")
set(SDL_TTF_ZIP ${CMAKE_BINARY_DIR}/SDL2_ttf.zip)
set(SDL_TTF_DIR ${CMAKE_BINARY_DIR}/external)

# Download the zip archive
file(DOWNLOAD ${SDL_TTF_URL} ${SDL_TTF_ZIP} SHOW_PROGRESS)

# Extract it
execute_process(
  COMMAND ${CMAKE_COMMAND} -E tar xzf ${SDL_TTF_ZIP}
  WORKING_DIRECTORY ${SDL_TTF_DIR}
)
target_include_directories(SDLEngine PUBLIC ${SDL_TTF_DIR}/SDL2_ttf-2.24.0/x86_64-w64-mingw32/include/SDL2)

set(CMAKE_FIND_LIBRARY_SUFFIXES .a)

find_library(LIBTTF libSDL2_ttf PATHS ${SDL_TTF_DIR}/SDL2_ttf-2.24.0/x86_64-w64-mingw32/lib)
message(STATUS "Found SDL2_tff: ${LIBTTF}")

set(CMAKE_FIND_LIBRARY_SUFFIXES ${_OLD_SUFFIXES})

####### NOVO

# Set output directory for the built static library
set_target_properties(SDLEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_link_libraries(SDLEngine
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    ${FREETYPE}
    ${LIBTFF}#SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)