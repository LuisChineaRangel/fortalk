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
#include <iostream>
#include <unistd.h>
#include <exception>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DOMAIN AF_INET
#define TYPE SOCK_DGRAM
#define PROTOCOL 0

using namespace std;

/// @brief Message Structure
struct Message {
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
		Socket(const sockaddr_in&);
		~Socket();
		
		void sendTo(const Message&, const sockaddr_in&);
		void receiveFrom(Message&, sockaddr_in&);
};
sockaddr_in makeIpAddress(const string&, int);
