#GSCE engine build as static lib

add_library(engine STATIC)

set(CMAKE_PREFIX_PATH external-libs)
set(CMAKE_INCLUDE_PATH external-libs)
set(CMAKE_LIBRARY_PATH external-libs)

add_subdirectory(external-libs/raylib)
target_link_libraries(engine PUBLIC raylib)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/external-libs/entt
)

#target_sources(engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

#temp main.cpp
target_sources(engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/platform/web/web-main.cpp)
