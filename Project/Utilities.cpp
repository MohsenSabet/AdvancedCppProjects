// Utilities Module
// Developer: Mohsen Sabet
// This module supports the parsing of input files, which contain information 
// used to set up and configure the assembly line. It provides the basic 
// functionality required for all objects in the system, including token extraction 
// and field width management.
// Note: This code is written by Mohsen Sabet. It is intended for educational 
// purposes only and must not be used for any form of academic dishonesty.

#include"Utilities.h"
#include <sstream>

namespace sdds {

	char Utilities::m_delimiter = ',';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        if (str[next_pos] == m_delimiter) {
            more = false;
            throw std::runtime_error("");
        }

        std::string token;
        size_t start = next_pos;
        size_t end = str.find(m_delimiter, start);

        if (end != std::string::npos) {
            token = str.substr(start, end - start);
            next_pos = end + 1;
        }
        else {
            token = str.substr(start);
            next_pos = str.length();
            more = false;
        }

        size_t first = token.find_first_not_of(' ');
        size_t last = token.find_last_not_of(' ');

        if (first != std::string::npos and last != std::string::npos) {
            token = token.substr(first, last - first + 1);
        }
        else {
            token = "";
        }

        if (token.length() > m_widthField) {
            m_widthField = token.length();
        }

        return token;
    }

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

}