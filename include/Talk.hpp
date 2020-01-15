/// @file Talk.hpp
/// @brief Class Talk Declaration
/// @author Luis Marcelo Chinea Rangel\n
/// University of La Laguna\n
/// Higher Polytechnic School of Engineering and Technology\n
/// Undergraduate degree in Computer Engineering\n
/// @date 11/01/2020
/// @see Contact E-mail:
/// alu0101118116@ull.es
//////////////////////////////////////////////////////////////////
#pragma once
#include <thread>

#include "../include/Socket.hpp"

#define BUFFER_SIZE 1023

/// @class Talk
class Talk {
	private:
		/// Indicate if User is a Server or Client
		bool serverMode;
		/// User's Address
		string ip;
		/// User's Port
		int port;
		/// User's Socket
		Socket socketTalk;
	public:
		Talk(const string& = {}, const int& = 0, bool = false);
		~Talk();
		
		void sendFile(const char*, const sockaddr_in&);
		void receiveFile(sockaddr_in&);
};

