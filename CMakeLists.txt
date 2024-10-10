cmake_minimum_required(VERSION 3.10)
project(YezhuConverter VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_WIN32_EXECUTABLE ON)

# undefined reference to `vtable for MainWindow'
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

# build type
if(DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Set to either \"Release\" or \"Debug\"")
else()
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Set to either \"Release\" or \"Debug\"")
endif()

set(PROJECT_NAME yezhu_converter)

set(DIALOGS_DIR src/dialogs)
set(DIALOGS_FILE
    ${DIALOGS_DIR}/ExportDialog.cpp
)

set(WIDGETS_DIR src/widgets)
set(WIDGETS_FILE
)


set(SOURCE_DIR src)
set(SOURCE_FILE
    ${DIALOGS_FILE}
    ${WIDGETS_FILE}
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/converter.cpp
    ${SOURCE_DIR}/MainWindow.cpp
)

# set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

# 查找 Qt6 库
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(JPEG REQUIRED)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILE})

target_include_directories(${PROJECT_NAME} PRIVATE include)

# 链接 Qt6 库
target_link_libraries(${PROJECT_NAME}

    # Qt6::Core
    # Qt6::Gui
    Qt6::Widgets
    raw
    JPEG::JPEG
)

# 设置自动处理 Qt6 的 MOC、资源和 UI 文件
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 添加安装规则
# install(TARGETS ${PROJECT_NAME}
# RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
# )
install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT binary
)

# 安装动态库
# install(TARGETS JPEG::JPEG
# DESTINATION ${CMAKE_INSTALL_LIBDIR}
# COMPONENT libraries
# )
# 复制动态库到安装目录
# 复制 Qt 动态库到安装目录
install(CODE "
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $ENV{MSYSTEM}/mingw64/bin/Qt6Core.dll
    $ENV{MSYSTEM}/mingw64/bin/Qt6Gui.dll
    $ENV{MSYSTEM}/mingw64/bin/Qt6Widgets.dll

    $ENV{CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
)
")

# 检查 Qt6Widgets.dll.a 是否存在
set(QT_WIDGETS_LIB_PATH "$ENV{MSYSTEM}/mingw64/bin/Qt6Widgets.dll.a")

if(EXISTS ${QT_WIDGETS_LIB_PATH})
    message(STATUS "Qt6Widgets library exists.")
else()
    message(WARNING "Qt6Widgets library does not exist!")
endif()

# 如果有需要，可以添加头文件目录
# install(DIRECTORY ${SOURCE_DIR}/ DESTINATION include/${PROJECT_NAME})

# 输出编译器信息
message(STATUS "CXX compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "CXX compiler version: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C compiler version: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
