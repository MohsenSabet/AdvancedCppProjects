// Utilities Module
// Developer: Mohsen Sabet
// This module supports the parsing of input files, which contain information 
// used to set up and configure the assembly line. It provides the basic 
// functionality required for all objects in the system, including token extraction 
// and field width management.
// Note: This code is written by Mohsen Sabet. It is intended for educational 
// purposes only and must not be used for any form of academic dishonesty.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>
#include <string>


namespace sdds {
	class Utilities {
		size_t m_widthField = 1;
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
	//char Utilities::m_delimiter = ',';

}


#endif // !SDDS_UTILITIES_H
