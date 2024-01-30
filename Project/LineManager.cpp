// LineManager Module
// Developer: Mohsen Sabet
// This module oversees the entire assembly line. It configures the line with active 
// stations, manages the flow of orders, and ensures that all customer orders are 
// processed efficiently, tracking both completed and incomplete orders.
// Note: This code is written by Mohsen Sabet. It is intended for educational 
// purposes only and must not be used for any form of academic dishonesty.

#include <fstream>
#include <sstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
    LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {
        m_cntCustomerOrder = g_pending.size();

        std::ifstream inFile(file);
        if (!inFile) {
            throw std::runtime_error("Error: Unable to open file " + file);
        }

        Utilities utilities;
        Utilities::setDelimiter('|');
        std::string strTemp;
        while (getline(inFile, strTemp)) {
            size_t next = 0;
            bool more = true;

            std::string first = utilities.extractToken(strTemp, next, more);
            auto it1 = std::find_if(stations.begin(), stations.end(), [&first](Workstation* w) {
                return w->getItemName() == first;
                });

            if (more) {
                std::string last = utilities.extractToken(strTemp, next, more);
                auto it2 = std::find_if(stations.begin(), stations.end(), [&last](Workstation* w) {
                    return w->getItemName() == last;
                    });

                if (it1 != stations.end() && it2 != stations.end()) {
                    (*it1)->setNextStation(*it2);
                }
            }
            if (it1 != stations.end()) {
                m_activeLine.push_back(*it1);
            }
        }

        // Identify the first station
        for (auto& station : stations) {
            bool is_first = true;
            for (auto& other : stations) {
                if (other->getNextStation() == station) {
                    is_first = false;
                    break;
                }
            }
            if (is_first) {
                m_firstStation = station;
                break;
            }
        }
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> temp;
        auto it = std::find_if(m_activeLine.begin(), m_activeLine.end(), [](Workstation* ws) {
            return ws->getNextStation() == nullptr;
            });

        if (it != m_activeLine.end()) {
            temp.push_back(*it);

            while (temp.size() < m_activeLine.size()) {
                it = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&temp](Workstation* w) {
                    return w->getNextStation() == temp.back();
                    });

                if (it != m_activeLine.end()) {
                    temp.push_back(*it);
                }
            }

            std::reverse(temp.begin(), temp.end());
            m_activeLine = temp;

            m_firstStation = m_activeLine.front();
        }
    }



    bool LineManager::run(ostream& os)
    {
        static size_t counter = 1;  // Static variable to track the iteration number
        os << "Line Manager Iteration: " << counter << endl;  // Display iteration
        counter++;

        // Process the pending order, if any
        if (!g_pending.empty()) {

            *m_firstStation += move(g_pending.front());  // Move order to first station
            g_pending.pop_front();  // Remove the order from pending queue
        }

        // Execute fill operations for each station
        for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* wStation) {
            wStation->fill(os);
            });

        // Attempt to move orders down the line
        for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* wStation) {
            wStation->attemptToMoveOrder();
            });

        // Check if all customer orders have been processed
        return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
    }

    void LineManager::display(ostream& os) const
    {
        for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* workStation) {
            workStation->display(os);
         });

        
    }
}