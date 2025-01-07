#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

// Class representing a Flight
class Flight
{
public:

    string flightNumber;

    string departure;

    string destination;

    string departureTime;

    int capacity;

    int bookedSeats;

    vector<string> delayReasons;

    // Default constructor
    Flight() : flightNumber(""), departure(""), destination(""), departureTime(""), capacity(0), bookedSeats(0) {}

    // Parameterized constructor
    Flight(string fn, string dep, string dest, string dt, int cap)

        : flightNumber(fn), departure(dep), destination(dest), departureTime(dt), capacity(cap), bookedSeats(0) {}

    bool bookSeat()

    {
        if (bookedSeats < capacity)
        {
            bookedSeats++;

            return true;

        }

        return false;
    }

    bool cancelSeat()

    {
        if (bookedSeats > 0)
        {
            bookedSeats--;

            return true;

        }

        return false;
    }

    void addDelayReason(const string &reason)

    {
        delayReasons.push_back(reason);

    }

    void clearDelayReasons()

    {
        delayReasons.clear();
    }

    void modifyDetails(const string &newDep, const string &newDest, const string &newTime, int newCap)

    {
        departure = newDep;

        destination = newDest;

        departureTime = newTime;

        capacity = newCap;
    }

    void display() const

    {
        cout << "Flight Number: " << flightNumber << "\nDeparture: " << departure

             << "\nDestination: " << destination << "\nDeparture Time: " << departureTime

             << "\nCapacity: " << capacity << "\nBooked Seats: " << bookedSeats << endl;

        if (!delayReasons.empty())

        {
            cout << "Delay Reasons: ";

            for (const string &reason : delayReasons)
            {
                cout << reason << "; ";
            }

            cout << endl;
        }

    }

    string toString() const

    {
        ostringstream oss;

        oss << flightNumber << "," << departure << "," << destination << ","

            << departureTime << "," << capacity << "," << bookedSeats;

        for (const string &reason : delayReasons)

        {
            oss << "," << reason;
        }

        return oss.str();
    }

    static Flight fromString(const string &data)

    {
        istringstream iss(data);

        string fn, dep, dest, dt;

        int cap, booked;

        vector<string> reasons;

        getline(iss, fn, ',');

        getline(iss, dep, ',');

        getline(iss, dest, ',');

        getline(iss, dt, ',');

        iss >> cap;

        iss.ignore();

        iss >> booked;

        iss.ignore();

        string reason;

        while (getline(iss, reason, ','))

        {
            reasons.push_back(reason);
        }

        Flight flight(fn, dep, dest, dt, cap);

        flight.bookedSeats = booked;

        flight.delayReasons = reasons;

        return flight;
    }

};

// Class managing multiple flights
class FlightManager

{
    map<string, Flight> flights;

public:

    void addFlight(const Flight &flight)

    {
        flights[flight.flightNumber] = flight;
    }

    Flight *findFlight(const string &flightNumber)

    {
        if (flights.find(flightNumber) != flights.end())

        {
            return &flights[flightNumber];
        }

        return nullptr;

    }

    void displayAllFlights() const

    {
        for (const auto &pair : flights)

        {
            pair.second.display();

            cout << "---------------------------" << endl;
        }

    }

    void displayFlightsByDestination(const string &destination) const

    {
        bool found = false;

        for (const auto &pair : flights)

        {
            if (pair.second.destination == destination)

            {
                pair.second.display();

                cout << "---------------------------" << endl;

                found = true;
            }

        }
        if (!found)

        {
            cout << "No flights found to destination: " << destination << endl;
        }

    }

    void displayFullyBookedFlights() const

    {
        bool found = false;

        for (const auto &pair : flights)

        {
            if (pair.second.bookedSeats == pair.second.capacity)

            {
                pair.second.display();

                cout << "---------------------------" << endl;

                found = true;
            }

        }

        if (!found)

        {
            cout << "No fully booked flights found." << endl;
        }

    }

    bool bookFlight(const string &flightNumber)

    {
        Flight *flight = findFlight(flightNumber);

        if (flight)

        {
            return flight->bookSeat();
        }

        return false;
    }

    bool cancelFlight(const string &flightNumber)

    {
        Flight *flight = findFlight(flightNumber);

        if (flight)

        {
            return flight->cancelSeat();
        }

        return false;
    }

    bool addFlightDelay(const string &flightNumber, const string &reason)

    {
        Flight *flight = findFlight(flightNumber);

        if (flight)

        {
            flight->addDelayReason(reason);

            return true;
        }

        return false;
    }

    bool modifyFlightDetails(const string &flightNumber, const string &newDep, const string &newDest, const string &newTime, int newCap)

    {
        Flight *flight = findFlight(flightNumber);

        if (flight)

        {
            flight->modifyDetails(newDep, newDest, newTime, newCap);

            return true;
        }

        return false;
    }

    bool removeFlight(const string &flightNumber)

    {
        return flights.erase(flightNumber) > 0;
    }

    void viewDelayReasons(const string &flightNumber) const

    {
        auto it = flights.find(flightNumber);

        if (it != flights.end())

        {
            if (!it->second.delayReasons.empty())

            {
                cout << "Delay Reasons for Flight " << flightNumber << ": ";

                for (const string &reason : it->second.delayReasons)

                {
                    cout << reason << "; ";
                }

                cout << endl;
            }

            else

            {
                cout << "No delay reasons recorded for Flight " << flightNumber << "." << endl;
            }

        }

        else

        {
            cout << "Flight " << flightNumber << " not found." << endl;
        }

    }

    void saveToFile(const string &filename) const

    {
        ofstream file(filename);

        for (const auto &pair : flights)

        {
            file << pair.second.toString() << endl;
        }

        file.close();
    }

    void loadFromFile(const string &filename)

    {
        ifstream file(filename);

        string line;

        while (getline(file, line))

        {
            addFlight(Flight::fromString(line));
        }

        file.close();
    }

    void displayFlightByNumber(const string &flightNumber) const
    {
        auto it = flights.find(flightNumber);

        if (it != flights.end())

        {
            it->second.display();
        }

        else

        {
            cout << "Flight with number " << flightNumber << " not found.\n";
        }

    }

    int availableSeats(const string &flightNumber) const

    {
        auto it = flights.find(flightNumber);

        if (it != flights.end())

        {
            return it->second.capacity - it->second.bookedSeats;
        }

        cout << "Flight not found!\n";

        return 0;
    }

    void displayFlightsByDeparture(const string &departure) const

    {
        bool found = false;

        for (const auto &pair : flights)

        {
            if (pair.second.departure == departure)

            {
                pair.second.display();

                cout << "---------------------------" << endl;

                found = true;
            }

        }

        if (!found)

        {
            cout << "No flights found departing from: " << departure << endl;
        }

    }

    void displayNonFullyBookedFlights() const

    {
        bool found = false;

        for (const auto &pair : flights)
        {

            if (pair.second.bookedSeats < pair.second.capacity)
            {
                pair.second.display();

                cout << "---------------------------" << endl;

                found = true;
            }

        }

        if (!found)

        {
            cout << "No flights are available with unbooked seats.\n";
        }
    }

    void displayFlightsByCapacity(int capacity) const

    {
        bool found = false;

        for (const auto &pair : flights)
        {

            if (pair.second.capacity == capacity)

            {
                pair.second.display();

                cout << "---------------------------" << endl;

                found = true;
            }

        }

        if (!found)

        {
            cout << "No flights found with capacity: " << capacity << endl;
        }
    }

    void displayFlightsByTimeRange(const string &startTime, const string &endTime) const

    {
        bool found = false;

        for (const auto &pair : flights)

        {
            if (pair.second.departureTime >= startTime && pair.second.departureTime <= endTime)

            {
                pair.second.display();

                cout << "---------------------------" << endl;

                found = true;
            }
        }

        if (!found)

        {
            cout << "No flights found within the time range: " << startTime << " to " << endTime << endl;
        }
    }

    bool updateFlightDepartureTime(const string &flightNumber, const string &newTime)

    {
        Flight *flight = findFlight(flightNumber);

        if (flight)

        {
            flight->departureTime = newTime;

            return true;
        }

        return false;
    }

    void displayFlightsWithSpecificDelayReason(const string &reason) const

    {
        bool found = false;

        for (const auto &pair : flights)

        {
            if (find(pair.second.delayReasons.begin(), pair.second.delayReasons.end(), reason) != pair.second.delayReasons.end())

            {
                pair.second.display();

                cout << "---------------------------" << endl;

                found = true;
            }

        }

        if (!found)

        {
            cout << "No flights found with delay reason: " << reason << endl;
        }
    }

};

// Menu display
void menu()
{
    cout << "\nFlight Route Management System\n";

    cout << "1. Add Flight\n";

    cout << "2. Display All Flights\n";

    cout << "3. Book a Flight\n";

    cout << "4. Cancel a Flight\n";

    cout << "5. Add Delay Reason to a Flight\n";

    cout << "6. View Delay Reasons of a Flight\n";

    cout << "7. Modify Flight Details\n";

    cout << "8. Remove Flight\n";

    cout << "9. Display Flights by Destination\n";

    cout << "10. Display Fully Booked Flights\n";

    cout << "11. Save Flights to File\n";

    cout << "12. Load Flights from File\n";

    cout << "13. Display Flight by Flight Number\n";

    cout << "14. Display Available Seats\n";

    cout << "15. Display Flights by Departure\n";

    cout << "16. Display Non-Fully Booked Flights\n";

    cout << "17. Display Flights by Capacity\n";

    cout << "18. Display Flights by Time Range\n";

    cout << "19. Update Flight Departure Time\n";

    cout << "20. Display Flights with Specific Delay Reason\n";

    cout << "Enter your choice: ";
}

// Main function to run the flight management system
int main()
{
    FlightManager flightManager;

    flightManager.loadFromFile("flights.txt");

    int choice;

    do
    {
        menu();

        cin >> choice;

        cin.ignore();  // To clear the input buffer

        switch (choice)

        {
        case 1:

        {
            string fn, dep, dest, dt;

            int cap;

            cout << "Enter Flight Number: ";

            getline(cin, fn);

            cout << "Enter Departure City: ";

            getline(cin, dep);

            cout << "Enter Destination City: ";

            getline(cin, dest);

            cout << "Enter Departure Time: ";

            getline(cin, dt);

            cout << "Enter Capacity: ";

            cin >> cap;

            flightManager.addFlight(Flight(fn, dep, dest, dt, cap));

            cout << "Flight added successfully!" << endl;

            break;
        }

        case 2:

            flightManager.displayAllFlights();

            break;

        case 3:

        {
            string flightNumber;

            cout << "Enter Flight Number to Book: ";

            getline(cin, flightNumber);

            if (flightManager.bookFlight(flightNumber))

            {
                cout << "Flight booked successfully!" << endl;
            }

            else

            {
                cout << "Unable to book the flight. It may be fully booked." << endl;
            }

            break;
        }

        case 4:

        {
            string flightNumber;

            cout << "Enter Flight Number to Cancel: ";

            getline(cin, flightNumber);

            if (flightManager.cancelFlight(flightNumber))

            {
                cout << "Flight cancelled successfully!" << endl;
            }

            else
            {
                cout << "Unable to cancel the flight. No seats were booked." << endl;
            }

            break;

        }

        case 5:

        {
            string flightNumber, reason;

            cout << "Enter Flight Number to Add Delay Reason: ";

            getline(cin, flightNumber);

            cout << "Enter Delay Reason: ";

            getline(cin, reason);

            if (flightManager.addFlightDelay(flightNumber, reason))

            {
                cout << "Delay reason added successfully!" << endl;
            }

            else

            {
                cout << "Unable to add delay reason. Flight not found." << endl;
            }

            break;
        }

        case 6:

        {
            string flightNumber;

            cout << "Enter Flight Number to View Delay Reasons: ";

            getline(cin, flightNumber);

            flightManager.viewDelayReasons(flightNumber);

            break;
        }

        case 7:

        {
            string flightNumber, newDep, newDest, newTime;

            int newCap;

            cout << "Enter Flight Number to Modify: ";

            getline(cin, flightNumber);

            cout << "Enter New Departure City: ";

            getline(cin, newDep);

            cout << "Enter New Destination City: ";

            getline(cin, newDest);

            cout << "Enter New Departure Time: ";

            getline(cin, newTime);

            cout << "Enter New Capacity: ";

            cin >> newCap;

            if (flightManager.modifyFlightDetails(flightNumber, newDep, newDest, newTime, newCap))

            {
                cout << "Flight details modified successfully!" << endl;
            }

            else

            {
                cout << "Unable to modify flight details. Flight not found." << endl;
            }

            break;
        }

        case 8:

        {
            string flightNumber;

            cout << "Enter Flight Number to Remove: ";

            getline(cin, flightNumber);

            if (flightManager.removeFlight(flightNumber))

            {
                cout << "Flight removed successfully!" << endl;
            }

            else

            {
                cout << "Unable to remove flight. Flight not found." << endl;
            }

            break;
        }

        case 9:

        {
            string destination;

            cout << "Enter Destination City to View Flights: ";

            getline(cin, destination);

            flightManager.displayFlightsByDestination(destination);

            break;
        }

        case 10:

            flightManager.displayFullyBookedFlights();

            break;

        case 11:

        {
            string filename;

            cout << "Enter filename to save flights to: ";

            getline(cin, filename);

            flightManager.saveToFile(filename);

            cout << "Flights saved to file successfully!" << endl;

            break;
        }

        case 12:

        {
            string filename;

            cout << "Enter filename to load flights from: ";

            getline(cin, filename);

            flightManager.loadFromFile(filename);

            cout << "Flights loaded from file successfully!" << endl;

            break;
        }

        case 13:

        {
            string flightNumber;

            cout << "Enter Flight Number to Display: ";

            getline(cin, flightNumber);

            flightManager.displayFlightByNumber(flightNumber);

            break;
        }

        case 14:

        {
            string flightNumber;

            cout << "Enter Flight Number to Check Available Seats: ";

            getline(cin, flightNumber);

            int available = flightManager.availableSeats(flightNumber);

            if (available > 0)
            {
                cout << "Available Seats: " << available << endl;
            }

            else

            {
                cout << "No available seats or flight not found." << endl;
            }

            break;
        }

        case 15:

        {
            string departure;

            cout << "Enter Departure City to View Flights: ";

            getline(cin, departure);

            flightManager.displayFlightsByDeparture(departure);

            break;
        }

        case 16:

            flightManager.displayNonFullyBookedFlights();

            break;

        case 17:

        {
            int capacity;

            cout << "Enter Capacity to View Flights: ";

            cin >> capacity;

            flightManager.displayFlightsByCapacity(capacity);

            break;
        }

        case 18:

        {
            string startTime, endTime;

            cout << "Enter Start Time (HH:MM): ";

            getline(cin, startTime);

            cout << "Enter End Time (HH:MM): ";

            getline(cin, endTime);

            flightManager.displayFlightsByTimeRange(startTime, endTime);

            break;
        }

        case 19:

        {
            string flightNumber, newTime;

            cout << "Enter Flight Number to Update Departure Time: ";

            getline(cin, flightNumber);

            cout << "Enter New Departure Time (HH:MM): ";

            getline(cin, newTime);

            if (flightManager.updateFlightDepartureTime(flightNumber, newTime))
            {
                cout << "Flight departure time updated successfully!" << endl;
            }

            else
            {
                cout << "Unable to update departure time. Flight not found." << endl;
            }

            break;
        }

        case 20:

        {
            string reason;

            cout << "Enter Delay Reason to View Flights: ";

            getline(cin, reason);

            flightManager.displayFlightsWithSpecificDelayReason(reason);

            break;
        }

        default:

            cout << "Invalid choice. Please try again." << endl;

            break;
        }

    } while (choice != 0);

    return 0;
}
