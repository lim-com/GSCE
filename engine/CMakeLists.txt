#GSCE engine build as static lib

add_library(gsce STATIC)

set(CMAKE_PREFIX_PATH external-libs)
set(CMAKE_INCLUDE_PATH external-libs)
set(CMAKE_LIBRARY_PATH external-libs)

add_subdirectory(external-libs/raylib)
add_subdirectory(external-libs/spdlog)
target_link_libraries(gsce PUBLIC spdlog)
target_link_libraries(gsce PUBLIC raylib)

target_include_directories(gsce PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/external-libs/entt
        ${CMAKE_CURRENT_SOURCE_DIR}/platform
)

#add imgui to gsce
file(GLOB_RECURSE IMGUI_SOURCE CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/external-libs/imgui/*.cpp
)
target_sources(gsce PRIVATE ${IMGUI_SOURCE})
target_include_directories(gsce PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/external-libs/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/external-libs/raylib-imgui
)
#---

#find recursive and target all .h headers
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h
)
target_sources(gsce PRIVATE ${ENGINE_HEADERS})

#find recursive and target all .cpp sources
file(GLOB_RECURSE ENGINE_SOURCE CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)
target_sources(gsce PRIVATE ${ENGINE_SOURCE})

if(EMSCRIPTEN)
    file(GLOB_RECURSE PLATFORM_HEADERS CONFIGURE_DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/platform/web/*.h
    )
    file(GLOB_RECURSE PLATFORM_SOURCE CONFIGURE_DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/platform/web/*.cpp
    )
else()
    file(GLOB_RECURSE PLATFORM_HEADERS CONFIGURE_DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/platform/native/*.h
    )
    file(GLOB_RECURSE PLATFORM_SOURCE CONFIGURE_DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/platform/native/*.cpp
    )
endif ()

target_sources(gsce PRIVATE ${PLATFORM_HEADERS})
target_sources(gsce PRIVATE ${PLATFORM_SOURCE})
