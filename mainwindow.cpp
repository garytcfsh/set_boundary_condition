#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_open_CSV_from_QGIS_clicked()
{
    QFile csvFromQGIS;
    int st = -1;
    st = openCSVFile( &csvFromQGIS, "csv");

    if (st == 0)
    {
        saveCSVasNodeList( &csvFromQGIS);

        csvFromQGIS.close();
    }
}

void MainWindow::saveCSVasNodeList( QFile *csvFromQGIS)
{

    QTextStream csvFromQGISStream (csvFromQGIS);
    csvFromQGISStream.readLine();

    while (!csvFromQGISStream.atEnd())
    {
        QStringList oneLine;
        oneLine = csvFromQGISStream.readLine().split(",");
        nodeList.append (new Nodes (oneLine[0], oneLine[1], oneLine[2],
                oneLine[3], oneLine[4], oneLine[5], oneLine[6], oneLine[7]));

    }
}

int MainWindow::openCSVFile(QFile *file, QString fileType)
{
    return openFile( file, fileType);
}

void MainWindow::on_modify_mff_from_Fracman_clicked()
{
    QFile oldMff, newMff;
    int st = -1;

    st = openMffFile( &oldMff, "mff");
    if (st == 0)
    {
        QString fileName = oldMff.fileName();
        fileName.remove( fileName.length()-3, 3);
        fileName = fileName + "new";
        createNewMffFile( &newMff, fileName);
        QTextStream oldMffStream( &oldMff);
        QTextStream newMffStream( &newMff);
        searchGridNodeNum( &oldMffStream, &oldMff);
        wrightNewMffFile( &oldMffStream, &newMffStream);
        renameMffFile( &oldMff, &newMff);
        oldMff.close();
        newMff.close();
    }
}

void MainWindow::searchGridNodeNum(QTextStream *oldMffStream, QFile *oldMff)
{
    QStringList QSL_oneLine;
    QString oneLine;
    bool findingStartNum = true;

    qint64 posHead = oldMff->pos();

    while( !oldMffStream->atEnd() && findingStartNum)
    {
        oneLine = oldMffStream->readLine();

        if (oneLine.contains("MatrixElem"))
        {
            QSL_oneLine = oldMffStream->readLine().simplified().split(" ");
            gridNodeStartNum = QSL_oneLine[2].toInt();

            findingStartNum = false;
        }
    }

    oldMffStream->seek(posHead);
}

void MainWindow::wrightNewMffFile( QTextStream *oldMffStream, QTextStream *newMffStream)
{
    QStringList QSL_oneLine;
    QString oneLine;
    int nodeNum;

    while (!oldMffStream->atEnd())
    {
        oneLine = oldMffStream->readLine();
        *newMffStream << oneLine << endl;

        if (oneLine.contains("*** HEADER"))
        {
            for (nodeNum = 0; nodeNum < gridNodeStartNum; nodeNum++)
            {
                oneLine = oldMffStream->readLine();
                *newMffStream << oneLine << endl;
            }
            for (int i=0; i < nodeList.count(); i++)
            {
                QSL_oneLine = oldMffStream->readLine().simplified().split(" ");
                QSL_oneLine[4] = nodeList[i]->getType();
                QSL_oneLine[5] = nodeList[i]->getH();
                QSL_oneLine[6] = nodeList[i]->getQ();
                QSL_oneLine[7] = nodeList[i]->getGrp();
                oneLine = "";
                for (int j=0; j<QSL_oneLine.count(); j++)
                {
                    oneLine = oneLine + '\t' + QSL_oneLine[j];
                }
                *newMffStream << oneLine << endl;
            }
        }
    }

}

int MainWindow::openMffFile( QFile* oldMff, QString fileType)
{
    return openFile( oldMff, fileType);
}

void MainWindow::createNewMffFile( QFile* newMff, QString fileName)
{
    createNewFile( newMff, fileName);
}

void MainWindow::renameMffFile( QFile* oldMff, QFile* newMff)
{
    renameFile( oldMff, newMff);
}

int MainWindow::openFile(QFile *file,  QString fileType)
{
    QString filePath = QFileDialog::getOpenFileName(
                this,
                tr("Select a file"),
                "",
                fileType + " Files (*." + fileType + ")");
    if (!filePath.isNull())
    {
        file->setFileName( filePath);
        file->open( QFile::ReadOnly|QFile::Text);

        return 0;
    }
    return -1;
}

void MainWindow::createNewFile(QFile *newFile, QString fileName)
{
    newFile->setFileName( fileName);
    newFile->open( QFile::WriteOnly|QFile::Text);
}

void MainWindow::renameFile(QFile *oldFile, QFile *newFile)
{
    QString fileName = oldFile->fileName();
    fileName.remove( fileName.length()-3, 3);
    oldFile->rename( fileName + "old");
    newFile->rename( fileName + "mff");
}


void MainWindow::on_generate_QGIS_import_file_clicked()
{
    QFile oldMff, newMff;
    int st = -1;

    st = openMffFile( &oldMff, "mff");
    if (st == 0)
    {
        QString fileName = oldMff.fileName();
        fileName.remove( fileName.length()-4, 4);
        fileName = fileName + "_grid.csv";
        createNewFile( &newMff, fileName);
        QTextStream oldMffStream( &oldMff);
        QTextStream newMffStream( &newMff);

        searchGridNodeNum( &oldMffStream, &oldMff);
        wrightQGISImportFile( &oldMffStream, &newMffStream);
    }
}

void MainWindow::wrightQGISImportFile( QTextStream *oldMffStream, QTextStream *newMffStream)
{
    QStringList QSL_oneLine;
    QString oneLine;
    int nodeNum;
    bool nodeEnd = false;

    while (!oldMffStream->atEnd())
    {
        oneLine = oldMffStream->readLine();

        if (oneLine.contains("*** HEADER"))
        {
            for (nodeNum = 0; nodeNum < gridNodeStartNum; nodeNum++)
            {
                oneLine = oldMffStream->readLine();
            }
            while (!nodeEnd)
            {
                QSL_oneLine = oldMffStream->readLine().simplified().split(" ");
                if (QSL_oneLine[0] == "0")
                {
                    nodeEnd = true;
                }
                else
                {
                    oneLine = QSL_oneLine.join(",");
                    *newMffStream << oneLine << endl;
                }
            }
        }
    }

}
