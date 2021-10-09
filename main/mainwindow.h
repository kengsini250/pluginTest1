#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLibrary>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    QMap<QString,QLibrary*> plugins;
    [[nodiscard]]
    int LoadDll(const QString&);

    typedef int (*UseDll)(int,int);
    UseDll usedll;
};
#endif // MAINWINDOW_H
