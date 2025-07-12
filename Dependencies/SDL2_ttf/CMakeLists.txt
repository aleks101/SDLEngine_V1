include(FetchContent)

# Paths to your FreeType build
#   set(FREETYPE_INCLUDE_DIRS "C:/Developer/Libraries/ft2133/freetype-2.13.3/include/" CACHE PATH "Path to FreeType headers")
#   set(FREETYPE_LIBRARY "C:/Developer/Libraries/ft2133/freetype-2.13.3/objs/freetype.a" CACHE FILEPATH "Path to FreeType library")

# Now fetch SDL2_ttf
FetchContent_Declare(
    FreeType
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG VER-2-13-3
)
FetchContent_MakeAvailable(FreeType)

# Tell SDL2_ttf where FreeType is
set(FREETYPE_INCLUDE_DIRS
    "${freetype_SOURCE_DIR}/include"
    "${freetype_BINARY_DIR}/include"
    CACHE PATH "Path to FreeType headers" FORCE
)

set(FREETYPE_LIBRARY
    "${freetype_BINARY_DIR}/libfreetype.a"
    CACHE FILEPATH "Path to FreeType library" FORCE
)

##test
set(FREETYPE_ENABLE_ZLIB OFF)
set(FREETYPE_ENABLE_PNG OFF)
##test


# Now fetch SDL2_ttf
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.24.0
)
FetchContent_MakeAvailable(SDL2_ttf)