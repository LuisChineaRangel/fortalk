/// @file Socket.hpp
/// @brief Socket Class Source Code
#include "Socket.hpp"

///////////////////////////////////////////////////////
// CLASS MEMBER FUNCTIONS
///////////////////////////////////////////////////////

/// @brief Default Constructor
/// @param ip_address Address assigned to Socket
/// @param port Port assigned to Socket
Socket::Socket(const std::string& ip_address, const int& port) {
  const sockaddr_in i_address = MakeInternetAddress(ip_address, port);
  Build();
  Bind(i_address);
}

/// @brief Parameterized  Constructor
/// @param i_address Internet Address
Socket::Socket(const sockaddr_in& i_address) {
  Build();
  Bind(i_address);
}

/// @brief Destructor
Socket::~Socket() {
  if (close(fd_) == 0) fd_ = 0;
}

/// @brief Build Method. Initializes the socket attributes
/// @return Void
void Socket::Build(void) {
  fd_ = socket(DOMAIN, TYPE, PROTOCOL);
  if (fd_ < 0)
    throw std::system_error(errno, std::system_category(),
                            "Couldn't create Socket");
}

/// @brief Bind Method. Binds socket to the user's address
/// @param i_address sockaddr_in to bind
/// @return Void
void Socket::Bind(const sockaddr_in& i_address) {
  if (bind(fd_, (const sockaddr*)&i_address, sizeof(i_address)) < 0)
    throw std::system_error(errno, std::system_category(),
                            "Couldn't bind Socket");
}

/// @brief SendTo Method. Sends a message to an specified address
/// @param message Message to send
/// @param i_address Receiver's address
/// @return Void
void Socket::SendTo(const Message& message, const sockaddr_in& i_address) {
  if (sendto(fd_, &message, sizeof(message), 0,
             reinterpret_cast<const sockaddr*>(&i_address),
             sizeof(i_address)) < 0) {
    throw std::system_error(errno, std::system_category(),
                            "Error sending message");
  }
}

/// @brief ReceiveFrom Method. Receives a message from an specified address
/// @param message Message to receive
/// @param i_address Sender's address
/// @return Void
void Socket::ReceiveFrom(Message& message, sockaddr_in& i_address) {
  socklen_t src_len = sizeof(i_address);
  if (recvfrom(fd_, &message, sizeof(message), 0,
               reinterpret_cast<sockaddr*>(&i_address), &src_len) < 0) {
    throw std::system_error(errno, std::system_category(),
                            "Error receiving message");
  }
  // Last characters from arrays should end in '/0'
  message.ip[19] = 0x00;
  message.text[1023] = 0x00;
}

///////////////////////////////////////////////////////
// EXTERNAL FUNCTIONS
///////////////////////////////////////////////////////

/// @brief MakeInternetAddress Function. Creates a sockaddr_in with an specified
/// address and port assigned
/// @param ip_address Ip Address to assign
/// @param port Port to assign
/// @return Void
sockaddr_in MakeInternetAddress(const std::string& ip_address, int port) {
  sockaddr_in localAddress{};
  localAddress.sin_family = DOMAIN;
  localAddress.sin_port = htons(port);

  if (ip_address.empty())
    localAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  else if (inet_aton(ip_address.c_str(), &localAddress.sin_addr) == 0)
    throw std::system_error(errno, std::system_category(), "Invalid Address");

  return localAddress;
}
