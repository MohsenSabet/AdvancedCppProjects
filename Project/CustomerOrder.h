
// CustomerOrder Module
// Developer: Mohsen Sabet
// This module contains all functionality for processing customer orders as they 
// move from Station to Station along the assembly line. It manages the details of 
// each order, including item names, serial numbers, and fill status.
// Note: This code is written by Mohsen Sabet. It is intended for educational 
// purposes only and must not be used for any form of academic dishonesty.


#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include <string>
#include "Station.h"
#include "Utilities.h"
namespace sdds{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;

	public:

		CustomerOrder();
		
		~CustomerOrder();
		
		CustomerOrder(const std::string& str);
		
		//returns true if all the items in the order have been filled; false otherwise
		bool isOrderFilled() const; 

		//returns true if all items specified by itemName have been filled. 
		// If the item doesn't exist in the order, this query returns true.
		bool isItemFilled(const std::string& itemName) const; 

		// – this modifier fills one item in the current order that the Station 
		//specified in the first parameter handles.
		void fillItem(Station& station, std::ostream& os); 

		void display(std::ostream& os) const;

		CustomerOrder(const CustomerOrder& other);
		CustomerOrder& operator=(CustomerOrder& other) = delete;
		CustomerOrder(CustomerOrder&& other) noexcept;
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;


	};

}

#endif // !SDDS_CUSTOMERORDER_H
