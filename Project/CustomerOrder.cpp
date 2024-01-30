// CustomerOrder Module
// Developer: Mohsen Sabet
// This module contains all functionality for processing customer orders as they 
// move from Station to Station along the assembly line. It manages the details of 
// each order, including item names, serial numbers, and fill status.
// Note: This code is written by Mohsen Sabet. It is intended for educational 
// purposes only and must not be used for any form of academic dishonesty.

#include "CustomerOrder.h"
#include <iomanip>
#include <vector>

namespace sdds{
	size_t CustomerOrder::m_widthField = 0;
	
	CustomerOrder::CustomerOrder()
	{
		m_lstItem = nullptr;
		m_name = "";
		m_product = "";
		m_cntItem = 0;
	}
	
	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;		
	}
	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities utilities;

		bool more = true;

		size_t pos = 0, begin = 0;
		m_cntItem = 0;
		try
		{
			m_name = utilities.extractToken(str, pos, more);

			m_product = utilities.extractToken(str, pos, more);

			begin = pos;

			std::string item;
			while (more)
			{
				item = utilities.extractToken(str, pos, more);
				m_cntItem++;
			}
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++)
			{
				item = utilities.extractToken(str, begin, more);
				m_lstItem[i] = new Item(item);
			}
			if (m_widthField < utilities.getFieldWidth())
				m_widthField = utilities.getFieldWidth();
		}
		catch (const char* msg)
		{
			throw msg;
		}
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool result = true;

		for (size_t i = 0; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled) {
				result = false; // If any item is not filled, the order is not filled
			}
		}
		return result; // All items are filled
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool result = true;

		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName and !m_lstItem[i]->m_isFilled) {
				result = false; // The specified item is not filled
			}
		}
		return result; // Item is filled or not present in the order
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (station.getItemName() == m_lstItem[i]->m_itemName) {
				if (!m_lstItem[i]->m_isFilled) {
					if (station.getQuantity() > 0) {
						station.updateQuantity();
						m_lstItem[i]->m_isFilled = true;
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();

						os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
						return;
					}
					else {
						os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
					}
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ')
			 << std::setw(m_widthField) << std::left << m_lstItem[i]->m_itemName  << " - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED";
			}
			else {
				os << "TO BE FILLED";
			}
			os << std::endl;
		}
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
		: m_name(std::move(other.m_name)), m_product(std::move(other.m_product)),
		m_cntItem(other.m_cntItem), m_lstItem(other.m_lstItem) {
		other.m_lstItem = nullptr;
		other.m_cntItem = 0;
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
		if (this != &other) {
			// Free existing resources
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			// Transfer resources
			m_name = std::move(other.m_name);
			m_product = std::move(other.m_product);
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;

			// Leave 'other' in a safe state
			other.m_lstItem = nullptr;
			other.m_cntItem = 0;
		}
		return *this;
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& c)
	{
		throw std::runtime_error("Copy operation not allowed");
	}

}

