// Station Module
// Developer: Mohsen Sabet
// This module manages information about a station on the assembly line. Each 
// station handles a specific item and is responsible for filling customer orders. 
// It includes functionalities for managing serial numbers and stock quantities.
// Note: This code is written by Mohsen Sabet. It is intended for educational 
// purposes only and must not be used for any form of academic dishonesty.


#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
#include "Utilities.h"
namespace sdds{
	class Station {
		int m_id;
		std::string m_name;
		std::string m_description;
		unsigned int m_serialNumber;
		unsigned int m_itemQTY;
		public:
		static size_t m_widthField;
		static int id_generator;
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}


#endif // !SDDS_STATION_H
