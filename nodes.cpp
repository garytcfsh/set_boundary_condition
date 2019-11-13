#include "nodes.h"

Nodes::Nodes()
{

}

Nodes::Nodes (QString a, QString b, QString c, QString d, QString e, QString f, QString g, QString h)
{
    a.remove("\"");
    NODE = a.toInt();
    b.remove("\"");
    X = b;
    c.remove("\"");
    Y = c;
    d.remove("\"");
    Z = d;
    e.remove("\"");
    Type = e;
    f.remove("\"");
    H = f;
    g.remove("\"");
    Q = g;
    h.remove("\"");
    Grp = h;
}

int Nodes::getNODE()
{
    return NODE;
}

QString Nodes::getX()
{
    return X;
}

QString Nodes::getY()
{
    return Y;
}

QString Nodes::getZ()
{
    return Z;
}

QString Nodes::getType()
{
    return Type;
}

QString Nodes::getH()
{
    return H;
}

QString Nodes::getQ()
{
    return Q;
}

QString Nodes::getGrp()
{
    return Grp;
}
