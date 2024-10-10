#!/bin/bash

# 获取当前脚本目录
destination="$(pwd)"

# 遍历当前目录下的所有 .exe 文件
for exe in *.exe; do
    if [ -f "$exe" ]; then
        echo "Processing $exe..."
        # 使用 ldd 查看依赖库
        ldd "$exe"

        # 从 ldd 输出中提取库名并复制
        ldd "$exe" | awk '{print $1}' | while read -r lib; do
            # 提取库名
            lib_name=$(basename "$lib")
            # 如果库在 /mingw64/bin/ 下，进行复制到当前目录
            if [ -f "/mingw64/bin/$lib_name" ]; then
                cp "/mingw64/bin/$lib_name" "$destination/"
                echo "Copied: $lib_name"
            fi
        done
    fi
done

echo "Libraries copied to $destination."
