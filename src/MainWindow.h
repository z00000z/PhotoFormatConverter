#pragma once

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>

class ExportDialog;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void exportFile(); // 声明

private:
    void createMenus();
    

    void addFileActions(QMenu *fileMenu);

    void addEditActions(QMenu *editMenu);

private:
    Ui::MainWindow *ui;

    ExportDialog* exportDialog = nullptr;
};
