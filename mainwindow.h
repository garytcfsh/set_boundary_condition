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

    int openCSVFile( QFile*, QString);
    int openMffFile( QFile*, QString);
    void createNewMffFile( QFile*, QString);
    void renameMffFile( QFile*, QFile*);
    int openFile( QFile*, QString);
    void createNewFile( QFile*, QString);
    void renameFile( QFile*, QFile*);
    void saveCSVasNodeList( QFile*);
    void searchGridNodeNum( QTextStream*, QFile*, int*);
    void wrightNewMffFile( QTextStream*, QTextStream*, int);

private slots:
    void on_open_CSV_from_QGIS_clicked();

    void on_modify_mff_from_Fracman_clicked();

private:
    Ui::MainWindow *ui;

    QList <Nodes*> nodeList;
};
#endif // MAINWINDOW_H
