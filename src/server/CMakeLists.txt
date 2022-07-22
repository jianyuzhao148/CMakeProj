# 获取当前目录下所有源文件，并保存到变量dir_server中
aux_source_directory(. dir_server)

set(MYSQL_LIBS 
	mysqlclient z zstd ssl crypto resolv m hiredis)

include_directories("/usr/include/mysql")
include_directories("/usr/include/hiredis")
link_directories("/usr/lib/x86_64-linux-gnu")

link_libraries(${MYSQL_LIBS})

# 生成名为server链接库
add_library(server ${dir_server})