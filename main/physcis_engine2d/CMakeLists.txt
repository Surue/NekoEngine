include_directories("include/")

file(GLOB_RECURSE physics_engine2d_src include/*.h src/*.cpp)

file(GLOB_RECURSE shaders_src ${CMAKE_SOURCE_DIR}/data/shaders/*.vert ${CMAKE_SOURCE_DIR}/data/shaders/*.frag)

source_group("Shaders"	FILES ${shaders_src})

add_executable(physics_engine2d ${physics_engine2d_src} ${shaders_src})
target_link_libraries(physics_engine2d PUBLIC Neko_Core Neko_Tool sdl_engine gles3_wrapper physics)
neko_bin_config(physics_engine2d)

if(EMSCRIPTEN)
    get_target_property(bin_link_flags physics_engine2d LINK_FLAGS)
    set_target_properties(physics_engine2d PROPERTIES LINK_FLAGS
            "${bin_link_flags} -s USE_SDL=2 -s USE_WEBGL2=1 ")
endif()
set_target_properties (physics_engine2d PROPERTIES FOLDER Neko\\Main)
set_target_properties(physics_engine2d PROPERTIES UNITY_BUILD ON)