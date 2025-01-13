#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QScrollArea>
#include <QUdpSocket>

#include "peer.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    QWidget window;
    window.setFixedSize(1000, 720);

    connInfo aliceConnInfo = {QHostAddress::LocalHost, 50000};
    connInfo bobConnInfo = {QHostAddress::LocalHost, 50001};

    Peer *alice = new Peer(&window, QString("Alice"), 10, aliceConnInfo, bobConnInfo);
    Peer *bob = new Peer(&window, QString("Bob"), 510, bobConnInfo, aliceConnInfo);

    window.show();
    return app.exec();
}

