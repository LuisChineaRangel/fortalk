/// @file Socket.hpp
/// @brief Socket Class Header
#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cstdlib>
#include <exception>
#include <string>

#include "TextMod.hpp"

/// Socket Attribute Macros
#define DOMAIN AF_INET
#define TYPE SOCK_DGRAM
#define PROTOCOL 0

/** @name Message */
/// @brief Structure for text messages of Fortalk
struct Message {
  bool file = false;

  // Sender's Ip address and Port
  std::array<char, 20> ip;
  int port;

  // Sender's Nickname and Text to send
  std::array<char, 100> user;
  std::array<char, 1024> text;
};

/// @class Socket
class Socket {
 private:
  int fd_;

 public:
  /** @name Constructors and Destructor */
  /// @{
  Socket(const std::string& = "", const int& = 0);
  Socket(const sockaddr_in& = sockaddr_in{});
  ~Socket();
  /// @}

  /** @name Auxiliar Public Methods */
  /// @{
  void SendTo(const Message&, const sockaddr_in&);
  void ReceiveFrom(Message&, sockaddr_in&);
  /// @}

 private:
  /** @name Auxiliar Private Methods */
  /// @{
  void Build(void);
  void Bind(const sockaddr_in&);
  /// @}
};
sockaddr_in MakeInternetAddress(const std::string&, int);