#ifndef FLIGHT_H
#define FLIGHT_H

struct Flight {
    char flightNo[10];    // Flight number (e.g., "AA123")
    char start[10];       // Departure station (e.g., "Paris")
    char end[10];         // Destination station (e.g., "Tokyo")
    int duration;       // Flight duration (hours)
    int totalTicket;      // Total tickets available
    int soldTicket;       // Tickets sold
};

#endif // FLIGHT_H