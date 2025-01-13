#include "peer.h"

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>

Peer::Peer(QWidget *parent, QString name, int x_offset, connInfo my_conn_info, connInfo peer_conn_info) : QWidget(parent)
{
    sendInputTextButton = new QPushButton(name, parent);
    sendInputTextButton->setGeometry(x_offset, 10, 480, 50);

    inputText = new QTextEdit(parent);
    inputText->setGeometry(x_offset, 70, 480, 170);
    inputText->show();

    text = QString("");

    receivedMessages = new QTextEdit(parent);
    receivedMessages->setGeometry(x_offset, 250, 480, 460);
    receivedMessages->setText(text);
    receivedMessages->setReadOnly(true);

    udpSocket = new QUdpSocket(parent);
    udpSocket->bind(my_conn_info.addr, my_conn_info.port);

    my_conn_info_ = my_conn_info;
    peer_conn_info_ = peer_conn_info;

    connect(sendInputTextButton, SIGNAL (clicked()), this, SLOT (sendDatagrams()));
    connect(udpSocket, SIGNAL (readyRead()), this, SLOT (readDatagrams()));
}

void Peer::sendDatagrams()
{
    QHostAddress a = QHostAddress::LocalHost;

    std::string stdtxt = inputText->toPlainText().toStdString();
    const char* txt = stdtxt.c_str();

    size_t txt_sz = 0;
    while (txt_sz < strlen(txt))
    {
        const char* chunk_of_txt = (txt+txt_sz);
        udpSocket->writeDatagram(chunk_of_txt, 512, a, this->peer_conn_info_.port);
        txt_sz += 512;
    }
}

void Peer::readDatagrams()
{
    QHostAddress a = QHostAddress::LocalHost;

    if (this->peer_conn_info_.port == 50001)
    {
        text.append("Message from Bob at\n");
    }
    else
    {
        text.append("Message from Alice at\n");
    }

    text.append("[");
    text.append(QDateTime::currentDateTime().toString().toStdString().c_str());
    text.append("]\n");

    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        text.append(datagram.data().toStdString().c_str());
    }
    text.append("\n\n");
    receivedMessages->setText(text.toStdString().c_str());
}
