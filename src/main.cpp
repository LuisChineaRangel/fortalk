/// @file main.cpp
/// @brief Main Code
/// @author Luis Marcelo Chinea Rangel\n
/// University of La Laguna\n
/// Higher Polytechnic School of Engineering and Technology\n
/// Undergraduate degree in Computer Engineering\n
/// @date 11/01/2020
/// @see Contact E-mail:
/// alu0101118116@ull.es
//////////////////////////////////////////////////////////////////
#include "../include/Socket.hpp"

#define BUFFER_SIZE 1024

void sendFile(const char*, Socket&, sockaddr_in&);
void receiveFile(Socket& socketTalk, sockaddr_in& remote);

void help();

/// @brief Main Function
/// @param argc Argument Counter
/// @param argv Argument Vector
int main(int argc, char* argv[]) {
	try {
		sockaddr_in local = makeIpAddress("127.0.0.1", 0);
		sockaddr_in remote = makeIpAddress("127.0.0.1", 10);

		Socket socketTalk(local);

		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Write the path of the file you desire to send: ";
		string text;
		cin >> text;
		cout << "-----------------------------------------------------------------------" << endl;
		const char* path = text.c_str();
		sendFile(path, socketTalk, remote);
	}
	catch (bad_alloc&  e) {
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "MyTalk: Insufficent Memory" << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		return 1;
	}
	
	catch (system_error& e) {
		cout << "-----------------------------------------------------------------------" << endl;
		cout << e.what() << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		return 2;
	}
	catch (...) {
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Unknown Error" << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		return 99;
	}

	return 0;
}

/// @brief Send Files Function
/// @param path File's path
/// @param socketTalk User's Socket
/// @param remote Message's Receiver
void sendFile(const char* path, Socket& socketTalk, sockaddr_in& remote) {
	char buffer[BUFFER_SIZE];
	char* b = buffer;
	int  bufferSize = sizeof(buffer) / sizeof(char);
	Message message;
	
	int fdFile = open(path, O_RDONLY);
	
	size_t bytesRead = BUFFER_SIZE;
	while (bytesRead > 0) {
		
		fill(message.user.begin(),message.user.end(), 0);
		fill(message.text.begin(),message.text.end(), 0);
	
		bytesRead = read(fdFile, b, BUFFER_SIZE);
		string text = string(buffer, bufferSize);
		text.copy(message.text.data(), message.text.size() - 1, 0);
		
		socketTalk.sendTo(message, remote);
	}
	
	close(fdFile);
}

/// @brief Receive Files Function
/// @param socketTalk User's Socket
/// @param remote Message's Receiver
void receiveFile(Socket& socketTalk, sockaddr_in& remote) {
	Message message;
	do {
		fill(message.user.begin(),message.user.end(),0);
		fill(message.text.begin(),message.text.end(),0);
	
		socketTalk.receiveFrom(message, remote);
	}
	while (!message.text.empty());
}

/// @brief User's Manual
void help() {
	
}
