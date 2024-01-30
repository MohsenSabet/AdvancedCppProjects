// Workstation Module
// Developer: Mohsen Sabet
// The Workstation module defines the structure of an active station on the 
// assembly line. It is responsible for order processing and managing the flow of 
// orders through the assembly line, including filling items and moving orders to the next station.
// Note: This code is written by Mohsen Sabet. It is intended for educational 
// purposes only and must not be used for any form of academic dishonesty.


#include "Workstation.h"
#include <fstream>

using namespace std;
namespace sdds {

    deque<CustomerOrder> g_pending{};
    deque<CustomerOrder> g_completed{};
    deque<CustomerOrder> g_incomplete{};


    Workstation::Workstation(const string& record) : Station(record), m_pNextStation(nullptr)
	{
		m_order.resize(0);
	}

	void Workstation::fill(ostream& os)
	{
		if (!m_order.empty()) {
			m_order.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
        if (m_order.empty()) {
            return false;
        }

        // Determine if the order can be moved
        bool canMove = m_order.front().isItemFilled(getItemName()) || getQuantity() == 0;
        if (!canMove) {
            return false; // Order cannot be moved yet
        }

        // Move order to next station or appropriate queue
        if (m_pNextStation) {
            *m_pNextStation += move(m_order.front()); // Move to next station
        }
        else {
            // Determine complete or incomplete
            auto& targetQueue = m_order.front().isOrderFilled() ? g_completed : g_incomplete;
            targetQueue.push_back(move(m_order.front())); // Move to completed or incomplete queue
        }

        m_order.pop_front(); // Remove the order from the current workstation
        return true; // Order was successfully moved


	}

    void Workstation::setNextStation(Workstation* station = nullptr)
    {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(ostream& os) const
    {
        if (m_pNextStation != nullptr) {
            os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;;
        }
        else {
            os << getItemName() << " --> End of Line" << endl;
        }
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        this->m_order.push_back(move(newOrder));  // Move the newOrder to the back of the queue
        return *this;  // Return a reference to the current instance
    }

}

