/// @file TextMod.hpp
/// @brief TextMod Class Header
#pragma once

#include <iostream>

/** @name Color */
/// @brief Codes for different font colors.
/// @{
enum Color {
  FG_RED = 31,
  FG_GREEN = 32,
  FG_YELLOW = 33,
  FG_BLUE = 34,
  FG_DEFAULT = 39,
  BG_RED = 41,
  BG_GREEN = 42,
  BG_BLUE = 44,
  BG_DEFAULT = 49
};
/// @}

/// @class TextMod
/// @brief Modifies Console Text Properties
/// ### Example
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
/// TextMod red(FG_RED);
/// std::cout << red << "Red Text";
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TextMod {
 private:
  Color color_;

 public:
  /** @name Constructors and Destructor */
  /// @{
  TextMod(Color = FG_DEFAULT);
  ~TextMod();
  /// @}

  /** @name Auxiliar Public Methods */
  /// @{
  friend std::ostream& operator<<(std::ostream&, const TextMod&);
  /// @}
};
