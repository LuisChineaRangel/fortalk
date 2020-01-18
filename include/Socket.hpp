/// @file Socket.hpp
/// @brief Class Socket Declaration
/// @author Luis Marcelo Chinea Rangel\n
/// University of La Laguna\n
/// Higher Polytechnic School of Engineering and Technology\n
/// Undergraduate degree in Computer Engineering\n
/// @date 11/01/2020
/// @see Contact E-mail:
/// alu0101118116@ull.es
//////////////////////////////////////////////////////////////////
#pragma once

#include <array>
#include <string>
#include <cstdlib>
#include <exception>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/Color.hpp"

#define DOMAIN AF_INET
#define TYPE SOCK_DGRAM
#define PROTOCOL 0

using namespace Color;

/// @brief Message Structure
struct Message {
	/// @brief Indicates if it's File or Text Message
	bool file = false;
	/// @brief Sender's Ip
	array<char, 20> ip;
	/// @brief Sender's port
	int port;
	/// @brief Sender
	array<char, 100> user;
	/// @brief Message to sent
	array<char, 1024> text;
};

/// @class Socket
class Socket {
	private:
		/// File Descriptor
		int fd_;
	public:
		Socket(const string&, const int&);
		Socket(const sockaddr_in& = sockaddr_in{});
		~Socket();
		
		void sendTo(const Message&, const sockaddr_in&);
		void receiveFrom(Message&, sockaddr_in&);
	private:
		void createSocket();
		void bindSocket(const sockaddr_in&);
};
sockaddr_in makeIpAddress(const string&, int);
