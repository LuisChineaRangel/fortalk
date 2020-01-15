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
#include "../include/Talk.hpp"

void sendFile(const char*, Socket&, const sockaddr_in&);
void receiveFile(Socket& socketTalk, sockaddr_in& remote);

void help();

/// @brief Main Function
/// @param argc Argument Counter
/// @param argv Argument Vector
int main(int argc, char* argv[]) {
	try {
		Talk myTalk("127.0.0.1", 0);
		sockaddr_in remote = makeIpAddress("127.0.0.1", 10);

		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Write the path of the file you desire to send: ";
		string text;
		cin >> text;
		cout << "-----------------------------------------------------------------------" << endl;
		const char* path = text.c_str();
		myTalk.sendFile(path, remote);
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

/// @brief User's Manual
void help() {
	
}
