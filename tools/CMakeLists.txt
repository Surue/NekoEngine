#source files
file(GLOB_RECURSE Neko_TOOLS_SRC src/*.cpp include/*.h)

source_group("Tools"				FILES ${Neko_TOOLS_SRC})

List(APPEND Neko_SRC ${Neko_TOOLS_SRC})
		
include_directories(${NEKO_CORE_DIR}/include)

add_library(Neko_Tool STATIC ${Neko_SRC})
target_link_libraries(Neko_Tool PRIVATE Neko_Core)

target_compile_options(Neko_Tool PRIVATE $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra>
        $<$<CXX_COMPILER_ID:MSVC>:
        /W4>)

set_target_properties (Neko_Tool PROPERTIES FOLDER Neko/Core)

target_include_directories(Neko_Tool PUBLIC "${IMGUI_ROOT}")
target_include_directories(Neko_Tool PUBLIC include/)
neko_lib_config(Neko_Tool)

