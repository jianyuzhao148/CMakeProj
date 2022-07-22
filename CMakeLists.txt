cmake_minimum_required(VERSION 2.8)
project ("CmakeProj")
# 主版本号 可在代码中获取
set (CMAKEPROJ_VERSION_MAJOR 1)
# 副版本号
set (CMAKEPROJ_VERSION_MINJOR 0)

# 启动GDB调试
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# 查找src目录下所有源文件 
# 并将名称保存到dir_src变量中
aux_source_directory(src dir_src)

# 添加子目录,使子目录下CMakeLists.txt编译
# add_subdirectory(src/algorithm)
# add_subdirectory(src/designPatterns)
add_subdirectory(src/server)


# 生成目标
add_executable(Main ${dir_src})

# 添加链接库
# target_link_libraries(Main algorithm)
# target_link_libraries(Main designPatterns)
target_link_libraries(Main server)