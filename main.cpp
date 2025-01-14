#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QScrollArea>
#include <QUdpSocket>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "peer.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    QWidget window;

    QHBoxLayout *splitter = new QHBoxLayout(&window);

    QVBoxLayout leftLayout(&window);
    QVBoxLayout rightLayout(&window);

    QWidget leftCol;
    QWidget rightCol;

    leftCol.setLayout(&leftLayout);
    rightCol.setLayout(&rightLayout);

    splitter->addWidget(&leftCol);
    splitter->addWidget(&rightCol);

    connInfo aliceConnInfo = {QHostAddress::LocalHost, 50000};
    connInfo bobConnInfo = {QHostAddress::LocalHost, 50001};

    Peer *alice = new Peer(&window, &leftLayout, QString("Alice"), aliceConnInfo, bobConnInfo);
    Peer *bob = new Peer(&window, &rightLayout, QString("Bob"), bobConnInfo, aliceConnInfo);

    window.show();
    return app.exec();
}

