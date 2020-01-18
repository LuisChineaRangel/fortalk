/// @file Color.cpp
/// @brief Color Modifiers Declaration
/// @author Luis Marcelo Chinea Rangel\n
/// University of La Laguna\n
/// Higher Polytechnic School of Engineering and Technology\n
/// Undergraduate degree in Computer Engineering\n
/// @date 17/01/2020
/// @see Contact E-mail:
/// alu0101118116@ull.es
//////////////////////////////////////////////////////////////////
#pragma once
#include <iostream>

using namespace std;

namespace Color {
	/// @brief Color Codes
	enum Code {
		FG_RED     = 31,
		FG_GREEN   = 32,
		FG_YELLOW  = 33,
		FG_BLUE    = 34,
		FG_DEFAULT = 39,
		BG_RED     = 41,
		BG_GREEN   = 42,
		BG_BLUE    = 44,
		BG_DEFAULT = 49
    };

	/// @class Modifier
	/// @brief Modifies ostream Font Color
	class Modifier {
		Code code;
		public:
			Modifier(Code colorCode = FG_DEFAULT) : code(colorCode) {}
			friend ostream& operator<<(ostream& os, const Modifier& mod) {
				return os << "\033[" << mod.code << "m";
			}
	};
}
