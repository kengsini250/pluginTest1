#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->pushButton_update,&QPushButton::clicked,this,[this]{
        QDir dir("debug/plugin");
        qDebug()<<dir.absolutePath();
        dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
        QFileInfoList list = dir.entryInfoList();

        ui->comboBox->clear();
        for(auto p=list.begin();p!=list.end();p++){
            ui->comboBox->addItem(p->baseName());
            int re = LoadDll(p->baseName());
            if(re!=0){}
        }

        ui->comboBox->setCurrentIndex(0);
    });


    connect(ui->pushButton_Load,&QPushButton::clicked,this,[this]{
        if(plugins.contains(ui->comboBox->currentText())){

        }else{
            int re = LoadDll(ui->comboBox->currentText());
            if(re!=0){}
        }
    });

    connect(ui->pushButton_remove,&QPushButton::clicked,this,[this]{
        QString name = ui->comboBox->currentText();
        int idx = ui->comboBox->currentIndex();
        if(plugins.contains(name)){
            auto dll = plugins[name];
            if(dll->isLoaded()){
                dll->unload();
                delete dll;
            }
            plugins.remove(name);
        }
        ui->comboBox->removeItem(idx);
    });

    connect(ui->pushButton,&QPushButton::clicked,this,[this]{
        QString a = ui->textEdit->toPlainText();
        QString b = ui->textEdit_2->toPlainText();
        int aa = a.toInt();
        int bb = b.toInt();


        usedll = (UseDll)plugins[ui->comboBox->currentText()]->resolve("func");
        ui->label_2->setText(QString::number(usedll(aa,bb)));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::LoadDll(const QString &d)
{
    QLibrary* dll = new QLibrary("plugin/"+d+".dll");
    if(dll->load()){
        plugins.insert(d,dll);
        return 0;   
    }else{
        qDebug()<<"load : "<<dll->errorString();
        return 2;
    }
}

