cmake_minimum_required(VERSION 4.2)
project(GSCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH external-libs)

find_package(SDL2 REQUIRED)

add_executable(GSCE
        sandbox/test.cpp
        sandbox/test.h
)

target_link_libraries(GSCE PRIVATE SDL2::SDL2)

if (MINGW)
    target_link_options(GSCE PRIVATE -static-libgcc -static-libstdc++ -static)
endif()

if(EMSCRIPTEN)
    # Включаем SDL
    target_link_options(GSCE PRIVATE
            -s USE_SDL=2
    )
    # Заставляем Emscripten создавать HTML
    set_target_properties(GSCE PROPERTIES SUFFIX ".html")
elseif(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()