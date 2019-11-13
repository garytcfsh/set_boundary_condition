#ifndef NODES_H
#define NODES_H
#include <QString>


class Nodes
{
public:
    Nodes();
    Nodes(QString a, QString b, QString c, QString d, QString e, QString f, QString g, QString h);
    int getNODE ();
    QString getX ();
    QString getY ();
    QString getZ ();
    QString getType ();
    QString getH ();
    QString getQ ();
    QString getGrp ();

private:
    int NODE;
    QString X;
    QString Y;
    QString Z;
    QString Type;
    QString H;
    QString Q;
    QString Grp;


};

#endif // NODES_H
