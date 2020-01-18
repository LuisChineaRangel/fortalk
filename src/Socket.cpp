/// @file Socket.cpp
/// @brief Class Socket
/// @author Luis Marcelo Chinea Rangel\n
/// University of La Laguna\n
/// Higher Polytechnic School of Engineering and Technology\n
/// Undergraduate degree in Computer Engineering\n
/// @date 11/01/2020
/// @see Contact E-mail:
/// alu0101118116@ull.es
//////////////////////////////////////////////////////////////////
#include "../include/Socket.hpp"

/// @brief Socket's Constructor
/// @param ipAddress Address assigned to Socket
/// @param port Port assigned to Socket
Socket::Socket(const string& ipAddress, const int& port) {
	const sockaddr_in address = makeIpAddress(ipAddress, port);
	createSocket();
	bindSocket(address);
}

/// @brief Socket's Constructor
/// @param address sockaddr_in assigned to Socket
Socket::Socket(const sockaddr_in& address) {
	createSocket();
	bindSocket(address);
}

/// @brief Assigning the file descriptor to Socket
void Socket::createSocket() {
	fd_ = socket(DOMAIN, TYPE, PROTOCOL);
	if (fd_ < 0)
		throw system_error(errno, system_category(), "Couldn't create Socket");
}

/// @brief Binding address to Socket
/// @param address sockaddr_in to bind
void Socket::bindSocket(const sockaddr_in& address) {
	if (bind(fd_, (const sockaddr*) &address, sizeof(address)) < 0)
		throw system_error(errno, system_category(), "Couldn't bind Socket");
}

/// @brief Socket's Destructor
Socket::~Socket() {
	if(close(fd_) == 0)
		fd_= 0;
}

/// @brief Method to send messages
void Socket::sendTo(const Message& message, const sockaddr_in& address) {
	if (sendto(fd_, &message, sizeof(message), 0, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) < 0) {
		throw system_error(errno, system_category(), "Error sending message");
	}
}

/// @brief Method to receive messages
void Socket::receiveFrom(Message& message, sockaddr_in& address) {
	socklen_t src_len = sizeof(address);
	if (recvfrom(fd_, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&address), &src_len) < 0) {
		throw system_error(errno, system_category(), "Error receiving message");
	}
	message.ip[19] = 0x00;
	message.text[1023] = 0x00;
}

/// @brief Assign the Ip Address and Port and returns a sockaddr_in
/// @param ipAdress Ip Address to assign
/// @param port Port to assgin
sockaddr_in makeIpAddress(const string& ipAddress, int port) {
	sockaddr_in localAddress{};
	localAddress.sin_family = AF_INET;
	localAddress.sin_port = htons(port);
	
	if (ipAddress.empty()) {
		localAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else {
		if (inet_aton(ipAddress.c_str(), &localAddress.sin_addr) == 0) {
			throw system_error(errno, system_category(), "Invalid Address");
		}
	}
	return localAddress;
}
