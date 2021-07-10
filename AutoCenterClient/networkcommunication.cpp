#include "networkcommunication.h"

#include <QMessageBox>

NetworkCommunication::NetworkCommunication(TcpClient *tcpClient)
{
    connect(this, &NetworkCommunication::requestReady, tcpClient, &TcpClient::sendAndGetResponse);
    connect(tcpClient, &TcpClient::errorDetected, this, &NetworkCommunication::handleCriticalError);
}

QString NetworkCommunication::getResponseWhenReady()
{
    TcpClient::s_semaphore.acquire();
    QString response = TcpClient::s_response;

    return response;
}

void NetworkCommunication::handleCriticalError(QString message)
{
    QMessageBox::critical(nullptr, "Помилка NetworkCommunication", message, QMessageBox::Ok);
}
