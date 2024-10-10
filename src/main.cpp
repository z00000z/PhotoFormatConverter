#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QMessageBox>
// #include <QFileDialog>
// #include <QTextEdit>
// #include <QFile>

#include "converter.h"

// #include "converter.h"
#include <libraw/libraw.h>
// #include <stb_image_write.h>
// #include <iostream>
// #include <filesystem>
#include <string>
// #include <algorithm> // 用于 std::clamp
// #include <QImage>
// #include <QColor>
#include "MainWindow.h"

void convertFilesInResourceDirectory()
{

    std::string srcDir = "D:/home/my_code/PhotoFormatConverter/resource/";
    std::string inputFile = srcDir + "DSC_5879.NEF"; // 替换为实际文件名
    std::string outputFile = srcDir + "DSC_JPG";     // 输出文件名

    if (convertNEFtoJPEG(inputFile, outputFile))
    {
        std::cout << "Conversion successful: " << outputFile << std::endl;
    }
    else
    {
        std::cerr << "Conversion failed." << std::endl;
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(800, 600);
    window.show();
    return app.exec();
}
