#ifndef PEER_H
#define PEER_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QUdpSocket>
#include <QLayout>

struct connInfo
{
    QHostAddress addr;
    int port;
};

class Peer : public QWidget
{
    Q_OBJECT
    public:
        explicit Peer(QWidget *parent,
                      QLayout *layout,
                      QString name,
                      connInfo my_conn_info,
                      connInfo peer_conn_info);

    private:
        QPushButton *sendInputTextButton;
        QTextEdit *inputText;
        QString text;
        QTextEdit *receivedMessages;
        QUdpSocket *udpSocket;
        connInfo my_conn_info_;
        connInfo peer_conn_info_;

    public slots:
        void sendDatagrams();
        void readDatagrams();

};

#endif // PEER_H
