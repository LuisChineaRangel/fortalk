/// @file NetCp.cpp
/// @brief Code for the NetCp Multi-File in C++
/// @author Luis Marcelo Chinea Rangel\n
/// University of La Laguna\n
/// Higher Polytechnic School of Engineering and Technology\n
/// Undergraduate degree in Computer Engineering\n
/// @date 11/01/2020
/// @see Contact E-mail:
/// alu0101118116@ull.es
//////////////////////////////////////////////////////////////////
#include "../include/Socket.hpp"

int main(int argc, char* argv[]) {
	try {
		sockaddr_in local = makeIpAddress("127.0.0.1", 0);
		sockaddr_in remote = makeIpAddress("127.0.0.1", 10);

		Socket socketTalk(local);

		string text("Hello World!");
				
		Message message;
		text.copy(message.text.data(), message.text.size() - 1, 0);
		
		socketTalk.sendTo(message, remote);
	}
	catch(exception& e) {
		cout << "-----------------------------------------------------------------------" << endl;
		cout << e.what() << endl;
		cout << "-----------------------------------------------------------------------" << endl;
	}
	return 0;
}
