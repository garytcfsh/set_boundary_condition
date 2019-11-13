#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nodes.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openOldMffFile( QFile*, QFile*);
    void createNewMffFile( QFile*, QString);
    void renameMffFile( QFile*, QFile*);

private slots:
    void on_open_CSV_from_QGIS_clicked();

    void on_modify_mff_from_Fracman_clicked();

private:
    Ui::MainWindow *ui;

    QList <Nodes*> nodeList;
};
#endif // MAINWINDOW_H
