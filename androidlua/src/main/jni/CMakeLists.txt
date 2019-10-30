# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.4.1)
#set(CMAKE_BUILD_TYPE Release FORCE)
add_compile_options(-DLUA_USE_C89)
add_compile_options(-DDLUA_DL_DLOPEN)
add_compile_options(-DLUA_COMPAT_5_1)
add_compile_options(-DLUA_COMPAT_5_2)
include_directories(lua)
aux_source_directory(lua LUA_SRC)

list(REMOVE_ITEM LUA_SRC "lua/lua.c")
list(REMOVE_ITEM LUA_SRC "lua/luac.c")

add_library(lua STATIC ${LUA_SRC})

aux_source_directory(luajava LUA_JAVA)
add_library(luajava SHARED ${LUA_JAVA})
find_library(log-lib log)
target_link_libraries(luajava lua ${log-lib})