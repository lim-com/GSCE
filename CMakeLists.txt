cmake_minimum_required(VERSION 4.2)
project(GSCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH external-libs)
set(CMAKE_INCLUDE_PATH external-libs)
set(CMAKE_LIBRARY_PATH external-libs)

add_subdirectory(external-libs/raylib)

add_executable(GSCE
        sandbox/test.cpp
        sandbox/test.h
)

target_link_libraries(GSCE raylib)

if (MINGW)
    target_link_options(GSCE PRIVATE -static-libgcc -static-libstdc++ -static)
endif()

if(EMSCRIPTEN)
    # Заставляем Emscripten создавать HTML
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(SHELL_FILE "${CMAKE_CURRENT_SOURCE_DIR}/web-templates/test.html")
    target_link_options(GSCE PRIVATE
            -sUSE_GLFW=3
            -sWASM=1
            -sASYNCIFY
            "--shell-file" "${SHELL_FILE}"
    )

elseif(WIN32)
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()