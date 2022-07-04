# 获取当前目录下所有源文件，并保存到变量dir_designPatterns中
aux_source_directory(. dir_designPatterns)
# 生成名为designPatterns链接库
add_library(designPatterns ${dir_designPatterns})