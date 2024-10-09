#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QFile>

#include "converter.h"


#include "converter.h"
#include <libraw/libraw.h>
// #include <stb_image_write.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm> // 用于 std::clamp
#include <QImage>
#include <QColor>
namespace zlh
{
    void cout()
    {
        std::cout << "zlh Hello World";
    }
};


void convertFilesInResourceDirectory() {
    std::string srcDir = "D:/home/my_code/PhotoFormatConverter/resource/";
    std::string inputFile = srcDir+"DSC_5879.NEF";  // 替换为实际文件名
    std::string outputFile = srcDir+"DSC_JPG"; // 输出文件名

    if (convertNEFtoJPEG(inputFile, outputFile)) {
        std::cout << "Conversion successful: " << outputFile << std::endl;
    } else {
        std::cerr << "Conversion failed." << std::endl;
    }
}


int main(int argc, char *argv[])
{

    // convertFilesInResourceDirectory();
    QApplication app(argc, argv);

    // 创建一个窗口
    QWidget window;
    window.setWindowTitle("Hello World");

    // 创建一个按钮
    QPushButton button("Hello World", &window);

    QObject::connect(&button, &QPushButton::clicked, [&]() {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(&window, "确认", "hai", 
                                      QMessageBox::Ok | QMessageBox::Cancel);
        if (reply == QMessageBox::Ok) {
            // 用户点击了 OK
        } else {
            // 用户点击了 Cancel
        }
    });

    // 创建布局并将按钮添加到窗口中
    QVBoxLayout layout;
    layout.addWidget(&button);
    window.setLayout(&layout);
    std::cout << "Hello World";
    std::cout << "/f";

    // 显示窗口
    zlh::cout();
    window.show();

    return app.exec();
}
