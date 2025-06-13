#include "FlightManager.h"
#include <cstring> // For string comparisons
#include <iostream>
#include "Flight.h"
void FlightManager::loadFlights() {
    flights.clear(); // Clear existing data
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return;

    Flight flight;
    while (file >> flight.flightNo >> flight.start >> flight.end
                >> flight.duration >> flight.totalTicket >> flight.soldTicket) {
        flights.push_back(flight);
                }
}
void saveFlightsToFile(const std::string& filename, const std::vector<Flight>& flights) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& flight : flights) {
        outFile << flight.flightNo << ' '
                << flight.start << ' '
                << flight.end << ' '
                << flight.duration << ' '
                << flight.totalTicket << ' '
                << flight.soldTicket << '\n';
    }

    outFile.close();
}


void FlightManager::saveFlights() {
    std::ofstream file(filePath, std::ios::binary | std::ios::trunc);
    for (const auto& flight : flights) {
        file << flight.flightNo << " "
             << flight.start << " "
             << flight.end << " "
             << flight.duration << " "
             << flight.totalTicket << " "
             << flight.soldTicket << "\n";
    }
}
void FlightManager::saveFlightsToFile(const std::string& filename, const std::vector<Flight>& flights) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& flight : flights) {
        outFile << flight.flightNo << ' '
                << flight.start << ' '
                << flight.end << ' '
                << flight.duration << ' '
                << flight.totalTicket << ' '
                << flight.soldTicket << '\n';
    }

    outFile.close();
}

void FlightManager::addFlight(const Flight& flight) {
    flights.push_back(flight);
    saveFlights();
}

void FlightManager::deleteFlight(int index) {
    if (index >= 0 && index < flights.size()) {
        flights.erase(flights.begin() + index);
        saveFlights();
    }
}

void FlightManager::updateFlight(int index, const Flight& newFlight) {
    if (index >= 0 && index < flights.size()) {
        flights[index] = newFlight;
        saveFlights();
    }
}

// Example search implementation (add others similarly)
std::vector<Flight> FlightManager::searchByFlightNo(const std::string& flightNo) const {
    std::vector<Flight> results;
    for (const auto& flight : flights) {
        if (std::strcmp(flight.flightNo, flightNo.c_str()) == 0) {
            results.push_back(flight);
        }
    }
    return results;
}