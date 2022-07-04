# 获取当前目录下所有源文件，并保存到变量dir_algorithm中
aux_source_directory(. dir_algorithm)
# 生成名为algorithm链接库
add_library(algorithm ${dir_algorithm})