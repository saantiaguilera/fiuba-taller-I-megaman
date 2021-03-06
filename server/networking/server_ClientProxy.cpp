/*
 * server_ClientProxy.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include <netinet/in.h>
#include <syslog.h>
#include <cstring>
#include <iostream>

#include "server_ClientProxy.h"

#define MAX_BUFFER_SIZE 10

// Initialize ids value
unsigned int ClientProxy::globalCount = 0;

ClientProxy::ClientProxy() {
	++globalCount;
	id = globalCount;
	connected = false;
	socket = Socket();
}

bool ClientProxy::isConnected() const {
	return connected;
}

ClientProxy::~ClientProxy() {
	--globalCount;
}

void ClientProxy::acceptNewConnection(const Socket& dispatcherSocket) {
	if (dispatcherSocket.accept(&socket) == 0) {
		connected = true;
	}
}

void ClientProxy::receive(int& messageCode, unsigned int& messageLength, std::string& incomingData) {
	incomingData = "";
	// Receive message code
	socket.receive((char*) &messageCode, sizeof(int));
	// TODO: Log receive error
	messageCode = ntohl(messageCode);

	// Receive message length
	socket.receive((char*) &messageLength, sizeof(unsigned int));
	// TODO: Log receive error
	messageLength = ntohl(messageLength);

	// Done workaround of size + 1 to avoid valgrind error
	char* buffer = new char[messageLength + 1];
	buffer[messageLength] = 0;
	memset(&buffer[0], 0, sizeof(*buffer));
	if (socket.receive(&buffer[0], messageLength) == -1) {
		syslog(LOG_ERR, "There was an error receiving from socket");
	} else {
		incomingData += buffer;
	}
	delete buffer;
}

unsigned int ClientProxy::getId() const {
	return id;
}

void ClientProxy::send(Serializer* serializer) {
	// Send message code
	int sendResult;
	int messageCode = htonl(serializer->getMessageCode());
	sendResult = socket.send((char*) &messageCode, sizeof(int));
	checkConnection(sendResult);

	// Send message length
	int messageLength = htonl(serializer->getMessageLength());
	sendResult =socket.send((char*) &messageLength, sizeof(unsigned int));
	checkConnection(sendResult);

	sendResult = socket.send((char*) serializer->getSerialized().c_str(), serializer->getMessageLength());
	checkConnection(sendResult);
}

void ClientProxy::checkConnection(int sendResult){
	if(sendResult == -1)
		connected = false;

}
