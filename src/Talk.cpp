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

/// Condition to exit Talk
atomic<bool> quit(false);

/// @brief Talk's Constructor
/// @param mode Server or Client mode
/// @param ipAddress User's Ip Address
/// @param port User's Port
Talk::Talk(const string& ipAddress, const int& AddressPort, bool mode) :
serverMode(mode),
ip(ipAddress),
port(AddressPort),
socketTalk(Socket(ipAddress, AddressPort))
{}

/// @brief Talk's Destructor
Talk::~Talk() {}

/// @brief Send Text Messages and Files, depending on the user's choice
/// @param remote Message's Receiver
void Talk::sendControl(const sockaddr_in& remote) {
	const string exit = "/quit";
	do {
		string text;
		getline(cin, text);
			
		size_t pos = text.find(WHITESPACE);
		string command = text.substr(0, pos);
		
		if(text == exit) {
			Modifier yellow(FG_YELLOW); 
			Modifier def;
			cout << yellow << "See you soon!" << def << endl;
			quit = true;
		}
		else if (command == "/Send") {
			const string path = text.substr(pos);
			sendFile(remote, path);
		}
		else {
			sendMessage(remote, text);
		}
	} while(!quit);
}

/// @brief Receive Text Messages or Files
/// @param remote Message's Sender
void Talk::receiveControl(sockaddr_in& remote) {
	do {
		Message message;
		socketTalk.receiveFrom(message, remote);
		
		if(!message.file) {
			writeMessage(message);
		}
		else {
			//receiveFile();
		}
		message = {};
	}
	while (!quit);
}

/// @brief Send Text Messages Function
/// @param remote Message's Receiver
/// @param text Message to send
void Talk::sendMessage(const sockaddr_in& remote, const string& text) {
	Message message;
	message.port = port;
	ip.copy(message.ip.data(), message.ip.size() - 1, 0);
	text.copy(message.text.data(), message.text.size() - 1, 0);
	message.text[text.size()] = 0x00;
	socketTalk.sendTo(message, remote);
}

/// @brief Write Text Messages Function
/// @param message Message
void Talk::writeMessage(const Message& message) {
	Modifier green(FG_GREEN); 
	Modifier def;
	cout << green << message.user.data() << "[" << message.ip.data() << ", " << message.port << "]: " << def << message.text.data() << endl;
}

/// @brief Send Files Function
/// @param remote Message's Receiver
/// @param filePath File Path/Name
void Talk::sendFile(const sockaddr_in& remote, const string& filePath) {
	const char* path = filePath.c_str();
		
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
		string text(buffer, bufferSize);

		message.file = true;
		message.port = port;
		ip.copy(message.ip.data(), message.ip.size() - 1, 0);
		text.copy(message.text.data(), message.text.size() - 1, 0);
		message.text[bytesRead] = 0x00;
	
		socketTalk.sendTo(message, remote);
		bytesRead = read(fdFile, b, BUFFER_SIZE);
	}
	close(fdFile);
}
