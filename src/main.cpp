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

void threadHandler(Talk&);
void intSignalHandler(int signal);
void request_cancellation(thread& talkThread);

void help();

/// @brief Main Function
/// @param argc Argument Counter
/// @param argv Argument Vector
int main(int argc, char* argv[]) {
	try {
		system("clear");
		Talk myTalk("127.0.0.1", 0);
		threadHandler(myTalk);
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
	catch (const exception& e) {
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Unknown Error" << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		return 99;
	}
	return 0;
}

/// @brief Talk Thread Handler
/// @param myTalk User's Talk
void threadHandler(Talk& myTalk) {
		signal(SIGINT, &intSignalHandler);
		
		sockaddr_in remote = makeIpAddress("127.0.0.1", 10);
		
		thread sendThread(Talk::sendControl, ref(myTalk), ref(remote));
		thread receiveThread(Talk::receiveControl, ref(myTalk), ref(remote));
		
		while(!quit);
		
		request_cancellation(sendThread);
		request_cancellation(receiveThread);
		
		sendThread.join();
		receiveThread.join();
}

/// @brief Interrupt Signal Handler
/// @param signal Interrupt Signal
void intSignalHandler(int signal) {
	Modifier def;
	Modifier red(FG_RED);
	cerr << red << "Interrupting program..." << def;
	quit = true;
}

/// @brief Thread cancellation
/// @param talkThread Thread to cancel
void request_cancellation(thread& talkThread) {
	pthread_cancel(talkThread.native_handle());
}

/// @brief User Manual
void help() {

}
