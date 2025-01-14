#include "peer.h"

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>
#include <QVBoxLayout>

Peer::Peer(QWidget *parent, QLayout *layout, QString name, connInfo my_conn_info, connInfo peer_conn_info) : QWidget(parent)
{
    sendInputTextButton = new QPushButton(name);
    inputText = new QTextEdit();
    receivedMessages = new QTextEdit();
    receivedMessages->setReadOnly(true);

    layout->addWidget(sendInputTextButton);
    layout->addWidget(inputText);
    layout->addWidget(receivedMessages);

    udpSocket = new QUdpSocket();
    udpSocket->bind(my_conn_info.addr, my_conn_info.port);

    my_conn_info_ = my_conn_info;
    peer_conn_info_ = peer_conn_info;

    connect(sendInputTextButton, SIGNAL (clicked()), this, SLOT (sendDatagrams()));
    connect(udpSocket, SIGNAL (readyRead()), this, SLOT (readDatagrams()));
}

void Peer::sendDatagrams()
{
    std::string stdtxt = inputText->toPlainText().toStdString();
    const char* txt = stdtxt.c_str();

    size_t txt_sz = 0;
    while (txt_sz < strlen(txt))
    {
        const char* chunk_of_txt = (txt+txt_sz);
        udpSocket->writeDatagram(chunk_of_txt, 512, peer_conn_info_.addr, peer_conn_info_.port);
        txt_sz += 512;
    }
}

void Peer::readDatagrams()
{
    if (peer_conn_info_.port == 50001)
    {
        text.append("Message from Bob at [");
    }
    else
    {
        text.append("Message from Alice at [");
    }

    text.append(QDateTime::currentDateTime().toString().toStdString().c_str());
    text.append("]\n");

    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        text.append(datagram.data().toStdString().c_str());
    }
    text.append("\n\n");
    receivedMessages->setText(text.toStdString().c_str());
}
