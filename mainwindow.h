#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nodes.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

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
    void searchGridNodeNum( QTextStream*, QFile*);
    void wrightNewMffFile( QTextStream*, QTextStream*);
    void wrightQGISImportFile( QTextStream*, QTextStream*);

private slots:
    void on_open_CSV_from_QGIS_clicked();

    void on_modify_mff_from_Fracman_clicked();

    void on_generate_QGIS_import_file_clicked();

private:
    Ui::MainWindow *ui;

    QList <Nodes*> nodeList;
    int gridNodeStartNum;
    QMessageBox msg;
};
#endif // MAINWINDOW_H
