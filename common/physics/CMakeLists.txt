
LIST(APPEND PHYSICS_LIBS Neko_Core gles3_wrapper)
file(GLOB_RECURSE physics_src include/*.h src/*.cpp)

add_library(physics STATIC ${physics_src})
target_link_libraries(physics PUBLIC ${PHYSICS_LIBS})

target_include_directories(physics PUBLIC "include/")
neko_lib_config(physics)
set_target_properties (physics PROPERTIES FOLDER Neko/Common)