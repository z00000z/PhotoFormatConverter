#!/bin/bash

# 遍历当前目录下的所有.dll文件
for file in $(find . -name "*.dll" -o -name "*.exe"); do
    # 使用ldd命令查看文件的依赖，然后使用grep命令过滤出包含/mingw64/bin/的路径并保存
    ldd_output=$(ldd $file | grep -o "/mingw64/bin/[^ ]*")

    # 遍历每一个元素
        while IFS= read -r line; do
            # 如果为空跳过
            if [ -z "$line" ]; then
                continue
            fi
            # 使用cp命令复制文件
            echo "copying $line"
            cp $line .
        done <<< "$ldd_output"
done