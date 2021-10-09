#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_Load, &QPushButton::clicked, this, [this]
            {
                //加载dll
                QLibrary dll("plugin/pluginTest_1.dll");

                if (dll.load())
                {

                    //dll的函数入口
                    //利用函数指针调用
                    usedll = (UseDll)dll.resolve("func");

                    if (!usedll)
                    {
                        qDebug() << "use : " << dll.errorString();
                    }
                }
                else
                {
                    qDebug() << "load : " << dll.errorString();
                }
            });

    connect(ui->pushButton, &QPushButton::clicked, this, [this]
            {
                QString a = ui->textEdit->toPlainText();
                QString b = ui->textEdit_2->toPlainText();
                int aa = a.toInt();
                int bb = b.toInt();

                //使用插件
                ui->label_2->setText(QString::number(usedll(aa, bb)));
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}
