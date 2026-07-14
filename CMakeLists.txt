cmake_minimum_required(VERSION 4.2)
project(GSCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH engine/external-libs)
set(CMAKE_INCLUDE_PATH engine/external-libs)
set(CMAKE_LIBRARY_PATH engine/external-libs)

add_subdirectory(engine/external-libs/raylib)

add_executable(GSCE
        sandbox/test.cpp
        sandbox/test.h
        engine/source/core/core.h
)

target_include_directories(GSCE PRIVATE ${CMAKE_SOURCE_DIR}/engine/external-libs/entt)
target_link_libraries(GSCE raylib)

if (MINGW)
    target_link_options(GSCE PRIVATE -static-libgcc -static-libstdc++ -static)
endif()

if(EMSCRIPTEN)
    # Заставляем Emscripten создавать HTML
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(SHELL_FILE "${CMAKE_CURRENT_SOURCE_DIR}/engine/platform/web/default.html")
    target_link_options(GSCE PRIVATE
            -sUSE_GLFW=3
            -sWASM=1
            -sASYNCIFY
            --shell-file ${SHELL_FILE}
            -s EXPORTED_RUNTIME_METHODS='["requestFullscreen","requestPointerLock"]'
    )

elseif(WIN32)
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()