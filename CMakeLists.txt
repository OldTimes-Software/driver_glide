add_library(
        glide_driver SHARED
        glide.c
        plugin.c
        plugin.h)

target_link_directories(glide_driver PRIVATE 3rdparty/Glide3x/Lib/Win32/)
target_link_libraries(glide_driver glide3x)

target_include_directories(glide_driver PRIVATE
        ../../plcore/include/
        ../../plgraphics/include/
        3rdparty/Glide3x/Include/
        )
