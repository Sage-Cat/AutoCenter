#include "networkcommunication.h"

NetworkCommunication::NetworkCommunication() :
    response("")
{

}

QString NetworkCommunication::getResponse() const
{
    return response;
}

void NetworkCommunication::setResponse(QString response)
{
    this->response = response;
}
