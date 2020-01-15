/// @file Talk.cpp
/// @brief Class Talk
/// @author Luis Marcelo Chinea Rangel\n
/// University of La Laguna\n
/// Higher Polytechnic School of Engineering and Technology\n
/// Undergraduate degree in Computer Engineering\n
/// @date 11/01/2020
/// @see Contact E-mail:
/// alu0101118116@ull.es
//////////////////////////////////////////////////////////////////
#include "../include/Talk.hpp"

/// @brief Talk's Constructor
/// @param mode Server or Client mode
/// @param ipAddress User's Ip Address
/// @param port User's Port
Talk::Talk(const string& ipAddress, const int& port, bool mode) :
serverMode(mode),
socketTalk(Socket(ipAddress, port)) 
{}

/// @brief Talk's Destructor
Talk::~Talk() {}

/// @brief Send Files Function
/// @param path File's path
/// @param remote Message's Receiver
void Talk::sendFile(const char* path, const sockaddr_in& remote) {
	char buffer[BUFFER_SIZE];
	char* b = buffer;
	int  bufferSize = sizeof(buffer) / sizeof(char);	
	int fdFile = open(path, O_RDONLY);

	size_t bytesRead = BUFFER_SIZE;
	bytesRead = read(fdFile, b, BUFFER_SIZE);

	while (bytesRead > 0) {
		Message message;

		int port = ntohs(remote.sin_port);
		string ip = inet_ntoa(remote.sin_addr);
		string text = string(buffer, bufferSize);

		message.port = port;
		ip.copy(message.ip.data(), message.ip.size() - 1, 0);
		text.copy(message.text.data(), message.text.size() - 1, 0);
		message.text[bytesRead] = 0x00;

		socketTalk.sendTo(message, remote);
		bytesRead = read(fdFile, b, BUFFER_SIZE);
	}
	close(fdFile);
}

/// @brief Receive Files Function
/// @param remote Message's Receiver
void Talk::receiveFile(sockaddr_in& remote) {
	Message message;
	do {
		socketTalk.receiveFrom(message, remote);
	}
	while (!message.text.empty());
}
