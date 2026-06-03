cmake_minimum_required(VERSION 3.16)

project(gtb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED)

find_package(SDL2_image QUIET)
find_package(SDL2_ttf QUIET)
find_package(SDL2_mixer QUIET)

set(SDL_COMPONENTS
    SDL2_image
    SDL2_ttf
    SDL2_mixer
)

set(_need_pkgconfig FALSE)

foreach(component IN LISTS SDL_COMPONENTS)
    if(NOT TARGET ${component}::${component} AND NOT ${component}_FOUND)
        set(_need_pkgconfig TRUE)
    endif()
endforeach()

if(_need_pkgconfig)
    find_package(PkgConfig)

    if(NOT PKG_CONFIG_FOUND)
        message(FATAL_ERROR
            "Nie znaleziono SDL2_image/SDL2_ttf/SDL2_mixer przez CMake, a pkg-config jest niedostepny."
        )
    endif()

    if(NOT SDL2_image_FOUND)
        pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
    endif()

    if(NOT SDL2_ttf_FOUND)
        pkg_check_modules(SDL2TTF REQUIRED SDL2_ttf)
    endif()

    if(NOT SDL2_mixer_FOUND)
        pkg_check_modules(SDL2MIXER REQUIRED SDL2_mixer)
    endif()
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(gtb ${SOURCES})

target_include_directories(gtb PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(gtb PRIVATE SDL2::SDL2)

if(TARGET SDL2::SDL2main)
    target_link_libraries(gtb PRIVATE SDL2::SDL2main)
endif()

function(link_sdl_component target component pkg_prefix)
    if(TARGET ${component}::${component})
        target_link_libraries(${target} PRIVATE ${component}::${component})
    else()
        target_include_directories(${target} PRIVATE
            ${${pkg_prefix}_INCLUDE_DIRS}
        )
        target_link_libraries(${target} PRIVATE
            ${${pkg_prefix}_LIBRARIES}
        )
    endif()
endfunction()

link_sdl_component(gtb SDL2_image SDL2IMAGE)
link_sdl_component(gtb SDL2_ttf SDL2TTF)
link_sdl_component(gtb SDL2_mixer SDL2MIXER)

add_custom_command(TARGET gtb POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:gtb>/assets
)