#include "ExportDialog.h"

#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSlider>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

ExportDialog::ExportDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("导出");
    // 文件路径选择
    QLineEdit *filePathEdit = new QLineEdit(this);
    QPushButton *browseButton = new QPushButton("浏览", this);
    connect(browseButton, &QPushButton::clicked, this, [=]()
            {
            QString filePath = QFileDialog::getOpenFileName(this, "选择源文件");
            if (!filePath.isEmpty()) {
                filePathEdit->setText(filePath);
            } });

    QHBoxLayout *fileLayout = new QHBoxLayout;
    fileLayout->addWidget(filePathEdit);
    fileLayout->addWidget(browseButton);

    // 输出格式选择
    QComboBox *formatComboBox = new QComboBox(this);
    formatComboBox->addItems({"JPEG", "PNG", "BMP"});

    // 质量滑块
    QSlider *qualitySlider = new QSlider(Qt::Horizontal, this);
    qualitySlider->setRange(0, 100);
    qualitySlider->setValue(85);

    // DPI 和分辨率调整
    QCheckBox *dpiCheckBox = new QCheckBox("分辨率", this);
    QSpinBox *dpiSpinBox = new QSpinBox(this);
    dpiSpinBox->setRange(1, 1000);
    dpiSpinBox->setValue(300);

    QCheckBox *resizeCheckBox = new QCheckBox("改变图像尺寸", this);
    QSpinBox *widthSpinBox = new QSpinBox(this);
    QSpinBox *heightSpinBox = new QSpinBox(this);
    widthSpinBox->setRange(1, 10000);
    heightSpinBox->setRange(1, 10000);
    widthSpinBox->setValue(6048);
    heightSpinBox->setValue(4024);

    QHBoxLayout *resizeLayout = new QHBoxLayout;
    resizeLayout->addWidget(widthSpinBox);
    resizeLayout->addWidget(new QLabel("x"));
    resizeLayout->addWidget(heightSpinBox);

    // 文件输出路径
    QLineEdit *outputPathEdit = new QLineEdit(this);
    QPushButton *outputBrowseButton = new QPushButton("浏览", this);
    connect(outputBrowseButton, &QPushButton::clicked, this, [=]()
            {
            QString outputPath = QFileDialog::getExistingDirectory(this, "选择保存文件夹");
            if (!outputPath.isEmpty()) {
                outputPathEdit->setText(outputPath);
            } });

    QHBoxLayout *outputPathLayout = new QHBoxLayout;
    outputPathLayout->addWidget(outputPathEdit);
    outputPathLayout->addWidget(outputBrowseButton);

    // 导出按钮
    QPushButton *exportButton = new QPushButton("导出", this);
    QPushButton *cancelButton = new QPushButton("取消", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(exportButton);
    buttonLayout->addWidget(cancelButton);

    // 总布局
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("源文件：", fileLayout);
    formLayout->addRow("导出格式：", formatComboBox);
    formLayout->addRow("质量：", qualitySlider);
    formLayout->addRow(dpiCheckBox, dpiSpinBox);
    formLayout->addRow(resizeCheckBox, resizeLayout);
    formLayout->addRow("保存到：", outputPathLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // 信号槽连接
    connect(exportButton, &QPushButton::clicked, this, [=]()
            {
                // 执行导出操作
            });

    connect(cancelButton, &QPushButton::clicked, this, &QWidget::close);
}