// LineManager Module
// Developer: Mohsen Sabet
// This module oversees the entire assembly line. It configures the line with active 
// stations, manages the flow of orders, and ensures that all customer orders are 
// processed efficiently, tracking both completed and incomplete orders.
// Note: This code is written by Mohsen Sabet. It is intended for educational 
// purposes only and must not be used for any form of academic dishonesty.


#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include "Workstation.h"

namespace sdds {
    class LineManager
    {
    private:
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder;
        Workstation* m_firstStation;
    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;

    };
}

#endif //! SDDS_LINEMANAGER_H
