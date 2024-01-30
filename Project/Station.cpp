// Station Module
// Developer: Mohsen Sabet
// This module manages information about a station on the assembly line. Each 
// station handles a specific item and is responsible for filling customer orders. 
// It includes functionalities for managing serial numbers and stock quantities.
// Note: This code is written by Mohsen Sabet. It is intended for educational 
// purposes only and must not be used for any form of academic dishonesty.

#include <iomanip>
#include "Station.h"


namespace sdds {
	
	int Station::id_generator = 0;
	size_t Station::m_widthField = 0;

	Station::Station(const std::string& record)
	{
		Utilities util;
		bool more = true;
		size_t next_pos = 0;

			// Extract the item name
			m_name = util.extractToken(record, next_pos, more);

			// Extract the serial number
			std::string serialStr = util.extractToken(record, next_pos, more);
			m_serialNumber = std::stoi(serialStr);

			// Extract the quantity in stock
			std::string quantityStr = util.extractToken(record, next_pos, more);
			m_itemQTY = std::stoi(quantityStr);

			// Update the width field if necessary
			m_widthField = std::max(m_widthField, util.getFieldWidth());

			// Extract the description
			m_description = util.extractToken(record, next_pos, more);

			// Set the ID for this station
			m_id = ++id_generator;

	}

	const std::string& Station::getItemName() const
	{
		return m_name;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return m_itemQTY;
	}

	void Station::updateQuantity()
	{
		if (m_itemQTY > 0) {
			m_itemQTY--;
		}
	}

	void Station::display(std::ostream& os, bool full) const
	{
		if (full) {
			os
				<< std::right << std::setfill('0') << std::setw(3) << m_id << " | "
				<< std::left << std::setfill(' ') << std::setw(m_widthField) << m_name << " | "
				<< std::right << std::setfill('0') << std::setw(6) << m_serialNumber << " | " 
				<< std::setfill(' ') << std::setw(4) << m_itemQTY << " | "
				<< m_description << std::endl;
		}
		else {
			os
			<< std::right << std::setfill('0') << std::setw(3) << m_id << " | "
			<< std::left  << std::setfill(' ') << std::setw(m_widthField) << m_name << " | "
			<< std::right << std::setfill('0') << std::setw(6) << m_serialNumber << " | " << std::endl;
			
		}
		

	}

}

