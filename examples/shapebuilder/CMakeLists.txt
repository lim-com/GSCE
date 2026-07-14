add_executable(shapebuilder
    shapebuilder-main.cpp
)

target_link_libraries(shapebuilder PRIVATE engine)

if (MINGW)
    target_link_options(shapebuilder PRIVATE -static-libgcc -static-libstdc++ -static)
endif()

if(EMSCRIPTEN)
    # Заставляем Emscripten создавать HTML
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(SHELL_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../engine/platform/web/default.html")
    target_link_options(shapebuilder PRIVATE
            -sUSE_GLFW=3
            -sWASM=1
            -sASYNCIFY
            --shell-file ${SHELL_FILE}
            -s EXPORTED_RUNTIME_METHODS='["requestFullscreen","requestPointerLock"]'
    )
endif ()