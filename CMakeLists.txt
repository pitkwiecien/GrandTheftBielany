cmake_minimum_required(VERSION 3.16)
project(megabonk_clone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- Zależności SDL2 -------------------------------------------------------
# Strategia: najpierw szukamy configów CMake (SDL2::SDL2 itd.).
# pkg-config używamy TYLKO jako fallback i TYLKO jeśli jest dostępny,
# żeby brak pkg-config nie wywalał konfiguracji od razu.

find_package(SDL2 REQUIRED)

find_package(SDL2_image QUIET)
find_package(SDL2_ttf   QUIET)
find_package(SDL2_mixer QUIET)

set(_need_pkgconfig FALSE)
if(NOT TARGET SDL2_image::SDL2_image AND NOT SDL2_image_FOUND)
    set(_need_pkgconfig TRUE)
endif()
if(NOT TARGET SDL2_ttf::SDL2_ttf AND NOT SDL2_ttf_FOUND)
    set(_need_pkgconfig TRUE)
endif()
if(NOT TARGET SDL2_mixer::SDL2_mixer AND NOT SDL2_mixer_FOUND)
    set(_need_pkgconfig TRUE)
endif()

if(_need_pkgconfig)
    find_package(PkgConfig)
    if(NOT PKG_CONFIG_FOUND)
        message(FATAL_ERROR
            "Nie znaleziono configow CMake dla SDL2_image/ttf/mixer, "
            "a pkg-config jest niedostepny.\n"
            "Zainstaluj komplet bibliotek SDL2 z naglowkami:\n"
            "  MSYS2 (UCRT64): pacman -S mingw-w64-ucrt-x86_64-SDL2 "
            "mingw-w64-ucrt-x86_64-SDL2_image mingw-w64-ucrt-x86_64-SDL2_ttf "
            "mingw-w64-ucrt-x86_64-SDL2_mixer mingw-w64-ucrt-x86_64-pkgconf\n"
            "  Debian/Ubuntu:  sudo apt install pkg-config libsdl2-dev "
            "libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev")
    endif()
    if(NOT SDL2_image_FOUND)
        pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
    endif()
    if(NOT SDL2_ttf_FOUND)
        pkg_check_modules(SDL2TTF   REQUIRED SDL2_ttf)
    endif()
    if(NOT SDL2_mixer_FOUND)
        pkg_check_modules(SDL2MIXER REQUIRED SDL2_mixer)
    endif()
endif()

# --- Źródła ----------------------------------------------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(megabonk ${SOURCES})

target_include_directories(megabonk PRIVATE
    ${CMAKE_SOURCE_DIR}/src)

# --- Linkowanie ------------------------------------------------------------
target_link_libraries(megabonk PRIVATE SDL2::SDL2)

# SDL2main istnieje tylko na niektórych platformach (m.in. Windows/MinGW).
if(TARGET SDL2::SDL2main)
    target_link_libraries(megabonk PRIVATE SDL2::SDL2main)
endif()

# SDL2_image
if(TARGET SDL2_image::SDL2_image)
    target_link_libraries(megabonk PRIVATE SDL2_image::SDL2_image)
else()
    target_include_directories(megabonk PRIVATE ${SDL2IMAGE_INCLUDE_DIRS})
    target_link_libraries(megabonk PRIVATE ${SDL2IMAGE_LIBRARIES})
endif()

# SDL2_ttf
if(TARGET SDL2_ttf::SDL2_ttf)
    target_link_libraries(megabonk PRIVATE SDL2_ttf::SDL2_ttf)
else()
    target_include_directories(megabonk PRIVATE ${SDL2TTF_INCLUDE_DIRS})
    target_link_libraries(megabonk PRIVATE ${SDL2TTF_LIBRARIES})
endif()

# SDL2_mixer
if(TARGET SDL2_mixer::SDL2_mixer)
    target_link_libraries(megabonk PRIVATE SDL2_mixer::SDL2_mixer)
else()
    target_include_directories(megabonk PRIVATE ${SDL2MIXER_INCLUDE_DIRS})
    target_link_libraries(megabonk PRIVATE ${SDL2MIXER_LIBRARIES})
endif()

# Kopiowanie assetów obok binarki.
add_custom_command(TARGET megabonk POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:megabonk>/assets)