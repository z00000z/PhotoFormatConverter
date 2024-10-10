#include "MainWindow.h"

#include "dialogs/ExportDialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // 创建文本编辑器
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    // 创建菜单栏
    createMenus();
}
MainWindow::~MainWindow()
{
}
void MainWindow::exportFile()
{
    if (!exportDialog) { // 如果尚未创建 ExportDialog
        exportDialog = new ExportDialog(this); // 创建实例并设置父窗口
        exportDialog->resize(300, 400); // 设置大小
    }
    exportDialog->show(); // 显示窗口
}

void MainWindow::createMenus()
{
    QMenuBar *menuBar = this->menuBar();

    // 创建“文件”菜单
    QMenu *fileMenu = menuBar->addMenu("文件");
    addFileActions(fileMenu);

    // 创建“编辑”菜单
    QMenu *editMenu = menuBar->addMenu("编辑");
    addEditActions(editMenu);
}

void MainWindow::addFileActions(QMenu *fileMenu)
{
    QAction *exportAction = fileMenu->addAction("导出");
    QAction *exitAction = fileMenu->addAction("退出");

    connect(exportAction, &QAction::triggered, this, &MainWindow::exportFile);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    // 这里可以连接其他 QAction 的信号和槽
}

void MainWindow::addEditActions(QMenu *editMenu)
{

    // 这里可以连接其他 QAction 的信号和槽
}