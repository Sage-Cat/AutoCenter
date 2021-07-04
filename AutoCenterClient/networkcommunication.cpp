#include "networkcommunication.h"

#include <QMessageBox>

NetworkCommunication::NetworkCommunication(const TcpClient *tcpClient) :
    response("")
{
    connect(this, &NetworkCommunication::requestReady, tcpClient, &TcpClient::sendAndGetResponse);
    connect(tcpClient, &TcpClient::responseReceived, this, &NetworkCommunication::setResponse);
    connect(tcpClient, &TcpClient::errorDetected, this, &NetworkCommunication::handleCriticalError);
}

QString NetworkCommunication::getResponse() const
{
    return response;
}

void NetworkCommunication::setResponse(QString response)
{
    this->response = response;
}

void NetworkCommunication::handleCriticalError(QString message)
{
    QMessageBox::critical(nullptr, "Помилка", message, QMessageBox::Ok);
}
