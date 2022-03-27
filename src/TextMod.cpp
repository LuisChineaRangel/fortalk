/// @file TextMod.cpp
/// @brief TextMod Class Source Code
#include "TextMod.hpp"

///////////////////////////////////////////////////////
// CLASS MEMBER FUNCTIONS
///////////////////////////////////////////////////////

/// @brief Default Constructor
/// @param color Color Code for customizing text
TextMod::TextMod(Color color) : color_(color) {}

/// @brief Destructor
TextMod::~TextMod() {}

/// @brief Output operator Overload
/// @param os Outputstream
/// @param mod Text Modifier
/// @return Custom Text
std::ostream& operator<<(std::ostream& os, const TextMod& mod) {
  return os << "\033[" << mod.color_ << "m";
}