// Workstation Module
// Developer: Mohsen Sabet
// The Workstation module defines the structure of an active station on the 
// assembly line. It is responsible for order processing and managing the flow of 
// orders through the assembly line, including filling items and moving orders to the next station.
// Note: This code is written by Mohsen Sabet. It is intended for educational 
// purposes only and must not be used for any form of academic dishonesty.


#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <string>
#include <deque>
#include "CustomerOrder.h"

namespace sdds {

    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;


    class Workstation : public Station {
    private:
        std::deque<CustomerOrder> m_order;
        Workstation* m_pNextStation{};

    public:
        Workstation(const std::string& record);

        void fill(std::ostream& os);


        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;

        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);

        Workstation(const Workstation& w) = delete;
        Workstation(Workstation&& w) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation& operator=(Workstation&&) = delete;

    };
}



#endif //!SDDS_WORKSTATION_H 

