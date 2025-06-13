#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H

#include "Flight.h"
#include <vector>
#include <fstream>
#include <iostream>

class FlightManager {
public :
    std::vector<Flight> flights;
    std::string filePath = "C:/Users/HP/Documents/FlyTicketSystem/flights.txt"; // File path for flight data
    //C:/Users/AYOUB/CLionProjects/FlyTicketSystem/
    void loadFlights(); // Load from file
    void saveFlights(); // Save to file

public:
    FlightManager() { loadFlights(); }

    // CRUD operations
    void addFlight(const Flight& flight);
    void deleteFlight(int index); // Delete by index in vector
    void updateFlight(int index, const Flight& newFlight);

    static void saveFlightsToFile(const std::string& filename, const std::vector<Flight>& flights);
    std::vector<Flight> getFlights() const {
        std::vector<Flight> result;
        std::ifstream file(filePath); // filePath is assumed to be your .txt file path

        if (!file) {
            std::cerr << "Error: Could not open " << filePath << std::endl;
            return result;
        }

        Flight flight;
        while (file >> flight.flightNo >> flight.start >> flight.end
                    >> flight.duration >> flight.totalTicket >> flight.soldTicket) {
            result.push_back(flight);
                    }

        return result;
    }

    // Search (implement based on your requirements)
    std::vector<Flight> searchByFlightNo(const std::string& flightNo) const;
    std::vector<Flight> searchByStart(const std::string& start) const;
    std::vector<Flight> searchByEnd(const std::string& end) const;
    std::vector<Flight> searchByDuration(float minDur, float maxDur) const;
};

#endif // FLIGHTMANAGER_H
