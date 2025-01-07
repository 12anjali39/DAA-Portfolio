#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <list>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <climits>


using namespace std;

class Flight
{

public:
    string origin;
    string destination;
    string date;
    string time;
    string airline;
    int distance; // Distance in kilometers
    string scheduledTime; // Scheduled departure time

    Flight(string origin, string destination, string date, string time, string airline, int distance, string scheduledTime)
        : origin(origin), destination(destination), date(date), time(time), airline(airline), distance(distance), scheduledTime(scheduledTime) {}

    void display() const
    {

        cout << "Origin: " << origin << ", Destination: " << destination
             << ", Date: " << date << ", Time: " << time
             << ", Airline: " << airline << ", Distance: " << distance << " km"
             << ", Scheduled Time: " << scheduledTime << endl;

    }

    int getDistance() const { return distance; }

    bool isDelayed() const
    {

        // Assuming time format is "HH:MM" and comparing times
        int scheduledHour = stoi(scheduledTime.substr(0, 2));
        int scheduledMinute = stoi(scheduledTime.substr(3, 2));
        int actualHour = stoi(time.substr(0, 2));
        int actualMinute = stoi(time.substr(3, 2));

        int scheduledTotalMinutes = scheduledHour * 60 + scheduledMinute;
        int actualTotalMinutes = actualHour * 60 + actualMinute;

        return actualTotalMinutes > scheduledTotalMinutes + 30;

    }

    static bool compareByOrigin(const Flight &f1, const Flight &f2)
    {

        return f1.origin < f2.origin;
    }

    static bool compareByDestination(const Flight &f1, const Flight &f2)
    {

        return f1.destination < f2.destination;

    }

    static bool compareByDate(const Flight &f1, const Flight &f2)
    {

        if (f1.date != f2.date)
        {

            return f1.date < f2.date;

        }
        return f1.time < f2.time;

    }

    static bool compareByAirline(const Flight &f1, const Flight &f2)
    {

        return f1.airline < f2.airline;

    }

};

class FlightInformationSystem
{

private:

    unordered_map<string, vector<Flight>> flightData;
    unordered_map<string, list<string>> flightRoutes;

public:
    void addFlight(const Flight &flight)
    {

        if (flightData.find(flight.origin) == flightData.end())
        {

            flightData[flight.origin] = vector<Flight>();

        }

        bool isDuplicate = false;

        for (const auto &existingFlight : flightData[flight.origin])
        {

            if (existingFlight.destination == flight.destination &&
                existingFlight.date == flight.date &&
                existingFlight.time == flight.time)
            {

                isDuplicate = true;
                break;

            }

        }

        if (!isDuplicate)
        {

            flightData[flight.origin].push_back(flight);
            sort(flightData[flight.origin].begin(), flightData[flight.origin].end(), Flight::compareByDate);

        }
        else
        {

            cout << "Warning: Duplicate flight found. Flight not added.\n";

        }

    }

    void displayAllFlights()
    {

        for (const auto &entry : flightData)
        {

            for (const auto &flight : entry.second)
            {

                flight.display();

            }

        }

    }

    void searchFlightsByOriginAndDestination(const string &origin, const string &destination)
    {

        bool found = false;

        for (const auto &flight : flightData[origin])
        {

            if (flight.destination == destination)
            {

                flight.display();
                found = true;

            }

        }
        if (!found)
        {

            cout << "No flights found for this route." << endl;

        }

    }

    void sortFlights(int choice)
    {
        vector<Flight> allFlights;

        for (const auto &entry : flightData)
        {

            allFlights.insert(allFlights.end(), entry.second.begin(), entry.second.end());

        }

        switch (choice)
        {

            case 1:

                sort(allFlights.begin(), allFlights.end(), Flight::compareByOrigin);
                break;

            case 2:

                sort(allFlights.begin(), allFlights.end(), Flight::compareByDestination);
                break;

            case 3:

                sort(allFlights.begin(), allFlights.end(), Flight::compareByDate);
                break;

            case 4:

                sort(allFlights.begin(), allFlights.end(), Flight::compareByAirline);
                break;

            default:

                cout << "Invalid choice!" << endl;
                return;

        }

        for (const Flight &f : allFlights)
        {

            f.display();

        }

    }

    void addRoute(const string &origin, const string &destination)
    {

        flightRoutes[origin].push_back(destination);

    }

    void displayRoutes()
    {

        for (const auto &entry : flightRoutes)
        {

            cout << "Routes from " << entry.first << ": ";
            for (const auto &dest : entry.second)
            {

                cout << dest << " ";

            }

            cout << endl;
        }
    }

    void findRoutesBFS(const string &start)
    {

        cout << "BFS Traversal starting from " << start << ":" << endl;
        unordered_map<string, bool> visited;
        queue<string> q;
        q.push(start);
        visited[start] = true;


        while (!q.empty())
        {

            string current = q.front();
            q.pop();
            cout << current << " ";


            for (const string &neighbor : flightRoutes[current])
            {

                if (!visited[neighbor])
                {

                    visited[neighbor] = true;
                    q.push(neighbor);

                }

            }

        }

        cout << endl;
    }

    void findRoutesDFS(const string &start)
    {

        cout << "DFS Traversal starting from " << start << ":" << endl;
        unordered_map<string, bool> visited;
        stack<string> s;
        s.push(start);
        visited[start] = true;

        while (!s.empty())
        {

            string current = s.top();
            s.pop();
            cout << current << " ";

            for (const string &neighbor : flightRoutes[current])
            {

                if (!visited[neighbor])
                {

                    visited[neighbor] = true;
                    s.push(neighbor);

                }

            }

        }

        cout << endl;
    }

    void removeFlight(const string &origin, const string &destination, const string &date, const string &time)
    {

        auto &flights = flightData[origin];
        for (auto it = flights.begin(); it != flights.end(); ++it)
        {

            if (it->destination == destination && it->date == date && it->time == time)
            {

                flights.erase(it);
                cout << "Flight removed successfully.\n";
                return;

            }

        }


        cout << "Flight not found.\n";
    }

    void updateFlightTime(const string &origin, const string &destination, const string &date, const string &oldTime, const string &newTime)
    {

        auto &flights = flightData[origin];
        for (auto &flight : flights)
        {

            if (flight.destination == destination && flight.date == date && flight.time == oldTime)
            {

                flight.time = newTime;
                cout << "Flight time updated successfully.\n";
                return;

            }

        }


        cout << "Flight not found.\n";

    }

    void listFlightsByDate(const string &date)
    {

        bool found = false;
        for (const auto &entry : flightData)
        {

            for (const auto &flight : entry.second)
            {

                if (flight.date == date)
                {

                    flight.display();
                    found = true;

                }

            }

        }
        if (!found)
        {
            cout << "No flights found on this date.\n";
        }
    }

    void listFlightsByAirline(const string &airline)
    {

        bool found = false;
        for (const auto &entry : flightData)
        {

            for (const auto &flight : entry.second)
            {

                if (flight.airline == airline)
                {

                    flight.display();
                    found = true;

                }

            }

        }
        if (!found)
        {
            cout << "No flights found for this airline.\n";
        }
    }

    void findShortestRoute(const string &start, const string &end)
    {

        unordered_map<string, string> previous;
        unordered_map<string, bool> visited;
        queue<string> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {

            string current = q.front();
            q.pop();

            if (current == end)
            {

                stack<string> path;
                for (string at = end; at != ""; at = previous[at])
                {

                    path.push(at);

                }
                cout << "Shortest route: ";
                while (!path.empty())
                {

                    cout << path.top();
                    path.pop();
                    if (!path.empty()) cout << " -> ";

                }
                cout << endl;
                return;

            }

            for (const string &neighbor : flightRoutes[current])
            {

                if (!visited[neighbor])
                {

                    visited[neighbor] = true;
                    previous[neighbor] = current;
                    q.push(neighbor);

                }

            }

        }
        cout << "No route found from " << start << " to " << end << ".\n";
    }

    void searchFlightsByAirlineAndDate(const string &airline, const string &date)
    {

        bool found = false;
        for (const auto &entry : flightData)
        {

            for (const auto &flight : entry.second)
            {

                if (flight.airline == airline && flight.date == date)
                {

                    flight.display();
                    found = true;

                }

            }

        }
        if (!found)
        {
            cout << "No flights found for airline " << airline << " on " << date << ".\n";
        }
    }

    void updateFlightDestination(const string &origin, const string &date, const string &time, const string &newDestination)
    {

        auto &flights = flightData[origin];
        for (auto &flight : flights)
        {

            if (flight.date == date && flight.time == time)
            {

                flight.destination = newDestination;
                cout << "Flight destination updated successfully.\n";
                return;

            }

        }
        cout << "Flight not found.\n";

    }

    int countFlightsByOrigin(const string &origin)
    {

        if (flightData.find(origin) != flightData.end())
        {

            return flightData[origin].size();

        }
        return 0;

    }

    // New functions for additional features

    void listShortDistanceFlights(int maxDistance = 500)
    {

        cout << "Short Distance Flights (distance <= " << maxDistance << " km):\n";
        bool found = false;
        for (const auto &entry : flightData)
        {

            for (const auto &flight : entry.second)
            {

                if (flight.getDistance() <= maxDistance)
                {

                    flight.display();
                    found = true;

                }

            }

        }
        if (!found)
        {

            cout << "No short distance flights found.\n";

        }
    }

    void listLongDistanceFlights(int minDistance = 2000)
    {

        cout << "Long Distance Flights (distance >= " << minDistance << " km):\n";
        bool found = false;
        for (const auto &entry : flightData)
        {

            for (const auto &flight : entry.second)
            {

                if (flight.getDistance() >= minDistance)
                {

                    flight.display();
                    found = true;

                }

            }

        }
        if (!found)
        {

            cout << "No long distance flights found.\n";

        }

    }

    void listLoungeAccessFlights(const string &airline)
    {

        cout << "Flights with lounge access for airline " << airline << ":\n";
        bool found = false;
        for (const auto &entry : flightData)
        {

            for (const auto &flight : entry.second)
            {

                if (flight.airline == airline)
                {

                    if (airline == "Emirates" || airline == "Qatar Airways" || airline == "Singapore Airlines")
                    {

                        flight.display();
                        found = true;

                    }

                }

            }

        }
        if (!found)
        {

            cout << "No flights with lounge access found for airline " << airline << ".\n";

        }
    }

    void listPrivateJetFlights()
    {

        cout << "Private Jet Flights:\n";
        bool found = false;
        for (const auto &entry : flightData)
        {

            for (const auto &flight : entry.second)
            {

                if (flight.airline.find("Private") != string::npos)
                {

                    flight.display();
                    found = true;

                }

            }

        }
        if (!found)
        {

            cout << "No private jet flights found.\n";

        }

    }

    void countDelayedFlights()
    {

        int count = 0;
        for (const auto &entry : flightData)
        {

            for (const auto &flight : entry.second)
            {

                if (flight.isDelayed())
                {

                    count++;

                }

            }

        }

        cout << "Number of delayed flights: " << count << endl;

    }

    void showDelayedFlights()
    {

        cout << "Delayed Flights:\n";
        bool found = false;
        for (const auto &entry : flightData)
        {

            for (const auto &flight : entry.second)
            {

                if (flight.isDelayed())
                {

                    flight.display();
                    found = true;

                }

            }

        }
        if (!found)
        {

            cout << "No delayed flights found.\n";

        }

    }

};


// Predefined flight information and routes
void initializeSystem(FlightInformationSystem &system)
{
    // Adding sample flights
system.addFlight(Flight("New York", "Chicago", "10/01/2024", "09:00", "American Airlines", 1200, "08:00"));
system.addFlight(Flight("Los Angeles", "Chicago", "10/01/2024", "12:00", "United Airlines", 2800, "11:00"));
system.addFlight(Flight("Chicago", "New York", "10/01/2024", "14:00", "JetBlue", 1200, "13:00"));
system.addFlight(Flight("Los Angeles", "New York", "10/01/2024", "16:00", "Delta", 2800, "15:00"));
system.addFlight(Flight("Mumbai", "Delhi", "10/01/2024", "10:00", "Air India", 1400, "09:00"));
system.addFlight(Flight("Delhi", "Mumbai", "10/01/2024", "13:00", "IndiGo", 1400, "12:00"));
system.addFlight(Flight("Bangalore", "Hyderabad", "10/01/2024", "15:00", "SpiceJet", 570, "14:00"));
system.addFlight(Flight("Hyderabad", "Bangalore", "10/01/2024", "18:00", "AirAsia", 570, "17:00"));
system.addFlight(Flight("Kolkata", "Chennai", "10/01/2024", "20:00", "GoAir", 1360, "19:00"));
system.addFlight(Flight("Chennai", "Kolkata", "10/01/2024", "22:00", "Vistara", 1360, "21:00"));
system.addFlight(Flight("London", "Paris", "10/01/2024", "08:00", "British Airways", 340, "07:30"));
system.addFlight(Flight("Paris", "London", "10/01/2024", "10:00", "Air France", 340, "09:30"));
system.addFlight(Flight("Dubai", "Mumbai", "10/01/2024", "12:00", "Emirates", 1920, "11:00"));
system.addFlight(Flight("Mumbai", "Dubai", "10/01/2024", "15:00", "Etihad", 1920, "14:00"));
system.addFlight(Flight("Singapore", "Delhi", "10/01/2024", "17:00", "Singapore Airlines", 4150, "16:00"));
system.addFlight(Flight("Delhi", "Singapore", "10/01/2024", "20:00", "SilkAir", 4150, "19:00"));
system.addFlight(Flight("Sydney", "Melbourne", "10/01/2024", "08:00", "Qantas", 880, "07:00"));
system.addFlight(Flight("Melbourne", "Sydney", "10/01/2024", "10:00", "Virgin Australia", 880, "09:00"));
system.addFlight(Flight("Toronto", "Vancouver", "10/01/2024", "12:00", "Air Canada", 3360, "11:00"));
system.addFlight(Flight("Vancouver", "Toronto", "10/01/2024", "15:00", "WestJet", 3360, "14:00"));
system.addFlight(Flight("Tokyo", "Osaka", "10/01/2024", "07:00", "ANA", 515, "06:00"));
system.addFlight(Flight("Osaka", "Tokyo", "10/01/2024", "09:00", "Japan Airlines", 515, "08:00"));
system.addFlight(Flight("Beijing", "Shanghai", "10/01/2024", "11:00", "China Eastern", 1210, "10:00"));
system.addFlight(Flight("Shanghai", "Beijing", "10/01/2024", "14:00", "Air China", 1210, "13:00"));
system.addFlight(Flight("Cape Town", "Johannesburg", "10/01/2024", "16:00", "South African Airways", 1270, "15:00"));
system.addFlight(Flight("Johannesburg", "Cape Town", "10/01/2024", "18:00", "Mango", 1270, "17:00"));
system.addFlight(Flight("Mumbai", "Chennai", "10/02/2024", "07:00", "Air India", 1030, "06:00"));
system.addFlight(Flight("Chennai", "Mumbai", "10/02/2024", "09:00", "IndiGo", 1030, "08:00"));
system.addFlight(Flight("Bangalore", "Kolkata", "10/02/2024", "11:00", "SpiceJet", 1860, "10:00"));
system.addFlight(Flight("Kolkata", "Bangalore", "10/02/2024", "13:00", "AirAsia", 1860, "12:00"));
system.addFlight(Flight("Hyderabad", "Delhi", "10/02/2024", "15:00", "GoAir", 1260, "14:00"));
system.addFlight(Flight("Delhi", "Hyderabad", "10/02/2024", "17:00", "Vistara", 1260, "16:00"));
system.addFlight(Flight("New York", "Los Angeles", "10/02/2024", "08:00", "American Airlines", 3940, "07:00"));
system.addFlight(Flight("Los Angeles", "New York", "10/02/2024", "11:00", "United Airlines", 3940, "10:00"));
system.addFlight(Flight("Chicago", "San Francisco", "10/02/2024", "13:00", "JetBlue", 2970, "12:00"));
system.addFlight(Flight("San Francisco", "Chicago", "10/02/2024", "16:00", "Delta", 2970, "15:00"));
system.addFlight(Flight("Mumbai", "Bangalore", "10/03/2024", "09:00", "Air India", 840, "08:00"));
system.addFlight(Flight("Bangalore", "Mumbai", "10/03/2024", "12:00", "IndiGo", 840, "11:00"));
system.addFlight(Flight("Kolkata", "Hyderabad", "10/03/2024", "14:00", "SpiceJet", 1500, "13:00"));
system.addFlight(Flight("Hyderabad", "Kolkata", "10/03/2024", "17:00", "AirAsia", 1500, "16:00"));
system.addFlight(Flight("Chennai", "Delhi", "10/03/2024", "19:00", "GoAir", 1750, "18:00"));
system.addFlight(Flight("Delhi", "Chennai", "10/03/2024", "21:00", "Vistara", 1750, "20:00"));
system.addFlight(Flight("Dubai", "London", "10/03/2024", "05:00", "Emirates", 5500, "04:00"));
system.addFlight(Flight("London", "Dubai", "10/03/2024", "08:00", "Etihad", 5500, "07:00"));
system.addFlight(Flight("Singapore", "Mumbai", "10/03/2024", "10:00", "Singapore Airlines", 3920, "09:00"));
system.addFlight(Flight("Mumbai", "Singapore", "10/03/2024", "13:00", "SilkAir", 3920, "12:00"));
system.addFlight(Flight("Sydney", "Brisbane", "10/03/2024", "15:00", "Qantas", 730, "14:00"));
system.addFlight(Flight("Brisbane", "Sydney", "10/03/2024", "17:00", "Virgin Australia", 730, "16:00"));
system.addFlight(Flight("Toronto", "Calgary", "10/03/2024", "19:00", "Air Canada", 2700, "18:00"));
system.addFlight(Flight("Calgary", "Toronto", "10/03/2024", "21:00", "WestJet", 2700, "20:00"));
system.addFlight(Flight("Tokyo", "Nagoya", "10/03/2024", "07:00", "ANA", 350, "06:00"));
system.addFlight(Flight("Nagoya", "Tokyo", "10/03/2024", "09:00", "Japan Airlines", 350, "08:00"));
system.addFlight(Flight("Beijing", "Guangzhou", "10/03/2024", "11:00", "China Eastern", 2180, "10:00"));
system.addFlight(Flight("Guangzhou", "Beijing", "10/03/2024", "13:00", "Air China", 2180, "12:00"));
system.addFlight(Flight("Cape Town", "Durban", "10/03/2024", "15:00", "South African Airways", 1270, "14:00"));
system.addFlight(Flight("Durban", "Cape Town", "10/03/2024", "17:00", "Mango", 1270, "16:00"));
system.addFlight(Flight("Mumbai", "Goa", "10/04/2024", "08:00", "Air India", 570, "07:00"));
system.addFlight(Flight("Goa", "Mumbai", "10/04/2024", "10:00", "IndiGo", 570, "09:00"));
system.addFlight(Flight("Bangalore", "Chennai", "10/04/2024", "12:00", "SpiceJet", 290, "11:00"));
system.addFlight(Flight("Chennai", "Bangalore", "10/04/2024", "14:00", "AirAsia", 290, "13:00"));
system.addFlight(Flight("Hyderabad", "Mumbai", "10/04/2024", "16:00", "GoAir", 710, "15:00"));
system.addFlight(Flight("Mumbai", "Hyderabad", "10/04/2024", "18:00", "Vistara", 710, "17:00"));
system.addFlight(Flight("New York", "Dallas", "10/04/2024", "08:00", "American Airlines", 2200, "07:00"));
system.addFlight(Flight("Dallas", "New York", "10/04/2024", "11:00", "United Airlines", 2200, "10:00"));
system.addFlight(Flight("Chicago", "Los Angeles", "10/04/2024", "13:00", "JetBlue", 2800, "12:00"));
system.addFlight(Flight("Los Angeles", "Chicago", "10/04/2024", "16:00", "Delta", 2800, "15:00"));
system.addFlight(Flight("Mumbai", "Delhi", "10/05/2024", "09:00", "Air India", 1400, "08:00"));
system.addFlight(Flight("Delhi", "Mumbai", "10/05/2024", "12:00", "IndiGo", 1400, "11:00"));
system.addFlight(Flight("Bangalore", "Hyderabad", "10/05/2024", "14:00", "SpiceJet", 570, "13:00"));
system.addFlight(Flight("Hyderabad", "Bangalore", "10/05/2024", "17:00", "AirAsia", 570, "16:00"));
system.addFlight(Flight("Kolkata", "Chennai", "10/05/2024", "19:00", "GoAir", 1360, "18:00"));
system.addFlight(Flight("Chennai", "Kolkata", "10/05/2024", "21:00", "Vistara", 1360, "20:00"));
system.addFlight(Flight("London", "Paris", "10/05/2024", "08:00", "British Airways", 340, "07:30"));
system.addFlight(Flight("Paris", "London", "10/05/2024", "10:00", "Air France", 340, "09:30"));
system.addFlight(Flight("Dubai", "Mumbai", "10/05/2024", "12:00", "Emirates", 1920, "11:00"));
system.addFlight(Flight("Mumbai", "Dubai", "10/05/2024", "15:00", "Etihad", 1920, "14:00"));
system.addFlight(Flight("Singapore", "Delhi", "10/05/2024", "17:00", "Singapore Airlines", 4150, "16:00"));
system.addFlight(Flight("Delhi", "Singapore", "10/05/2024", "20:00", "SilkAir", 4150, "19:00"));
system.addFlight(Flight("Sydney", "Melbourne", "10/05/2024", "08:00", "Qantas", 880, "07:00"));
system.addFlight(Flight("Melbourne", "Sydney", "10/05/2024", "10:00", "Virgin Australia", 880, "09:00"));
system.addFlight(Flight("Toronto", "Vancouver", "10/05/2024", "12:00", "Air Canada", 3360, "11:00"));
system.addFlight(Flight("Vancouver", "Toronto", "10/05/2024", "15:00", "WestJet", 3360, "14:00"));
system.addFlight(Flight("Tokyo", "Osaka", "10/05/2024", "07:00", "ANA", 515, "06:00"));
system.addFlight(Flight("Osaka", "Tokyo", "10/05/2024", "09:00", "Japan Airlines", 515, "08:00"));
system.addFlight(Flight("Beijing", "Shanghai", "10/05/2024", "11:00", "China Eastern", 1210, "10:00"));
system.addFlight(Flight("Shanghai", "Beijing", "10/05/2024", "14:00", "Air China", 1210, "13:00"));
system.addFlight(Flight("Cape Town", "Johannesburg", "10/05/2024", "16:00", "South African Airways", 1270, "15:00"));
system.addFlight(Flight("Johannesburg", "Cape Town", "10/05/2024", "18:00", "Mango", 1270, "17:00"));
system.addFlight(Flight("Mumbai", "Chennai", "10/06/2024", "07:00", "Air India", 1030, "06:00"));
system.addFlight(Flight("Chennai", "Mumbai", "10/06/2024", "09:00", "IndiGo", 1030, "08:00"));
system.addFlight(Flight("Bangalore", "Kolkata", "10/06/2024", "11:00", "SpiceJet", 1860, "10:00"));
system.addFlight(Flight("Kolkata", "Bangalore", "10/06/2024", "13:00", "AirAsia", 1860, "12:00"));
system.addFlight(Flight("Hyderabad", "Delhi", "10/06/2024", "15:00", "GoAir", 1260, "14:00"));
system.addFlight(Flight("Delhi", "Hyderabad", "10/06/2024", "17:00", "Vistara", 1260, "16:00"));
system.addFlight(Flight("New York", "Los Angeles", "10/06/2024", "08:00", "American Airlines", 3940, "07:00"));
system.addFlight(Flight("Los Angeles", "New York", "10/06/2024", "11:00", "United Airlines", 3940, "10:00"));
system.addFlight(Flight("Chicago", "San Francisco", "10/06/2024", "13:00", "JetBlue", 2970, "12:00"));
system.addFlight(Flight("San Francisco", "Chicago", "10/06/2024", "16:00", "Delta", 2970, "15:00"));
system.addFlight(Flight("Mumbai", "Bangalore", "10/07/2024", "09:00", "Air India", 840, "08:00"));
system.addFlight(Flight("Bangalore", "Mumbai", "10/07/2024", "12:00", "IndiGo", 840, "11:00"));
system.addFlight(Flight("Kolkata", "Hyderabad", "10/07/2024", "14:00", "SpiceJet", 1500, "13:00"));
system.addFlight(Flight("Hyderabad", "Kolkata", "10/07/2024", "17:00", "AirAsia", 1500, "16:00"));
system.addFlight(Flight("Chennai", "Delhi", "10/07/2024", "19:00", "GoAir", 1760, "18:00"));
system.addFlight(Flight("Delhi", "Chennai", "10/07/2024", "21:00", "Vistara", 1760, "20:00"));
system.addFlight(Flight("Dubai", "London", "10/07/2024", "05:00", "Emirates", 5500, "04:00"));
system.addFlight(Flight("London", "Dubai", "10/07/2024", "08:00", "Etihad", 5500, "07:00"));





    // Adding routes (graph)
        system.addRoute("New York", "Los Angeles");
        system.addRoute("New York", "Chicago");
        system.addRoute("Los Angeles", "Chicago");
        system.addRoute("Los Angeles", "New York");
        system.addRoute("Chicago", "New York");
        system.addRoute("Chicago", "Los Angeles");
        system.addRoute("Mumbai", "Delhi");
        system.addRoute("Delhi", "Mumbai");
        system.addRoute("Bangalore", "Hyderabad");
        system.addRoute("Hyderabad", "Bangalore");
        system.addRoute("Kolkata", "Chennai");
        system.addRoute("Chennai", "Kolkata");
        system.addRoute("London", "Paris");
        system.addRoute("Paris", "London");
        system.addRoute("Dubai", "Mumbai");
        system.addRoute("Mumbai", "Dubai");
        system.addRoute("Singapore", "Delhi");
        system.addRoute("Delhi", "Singapore");
        system.addRoute("Sydney", "Melbourne");
        system.addRoute("Melbourne", "Sydney");
        system.addRoute("Toronto", "Vancouver");
        system.addRoute("Vancouver", "Toronto");
        system.addRoute("Tokyo", "Osaka");
        system.addRoute("Osaka", "Tokyo");
        system.addRoute("Beijing", "Shanghai");
        system.addRoute("Shanghai", "Beijing");
        system.addRoute("Cape Town", "Johannesburg");
        system.addRoute("Johannesburg", "Cape Town");
        system.addRoute("Mumbai", "Chennai");
        system.addRoute("Chennai", "Mumbai");
        system.addRoute("Bangalore", "Kolkata");
        system.addRoute("Kolkata", "Bangalore");
        system.addRoute("Hyderabad", "Delhi");
        system.addRoute("Delhi", "Hyderabad");
        system.addRoute("New York", "Los Angeles");
        system.addRoute("Los Angeles", "New York");
        system.addRoute("Chicago", "San Francisco");
        system.addRoute("San Francisco", "Chicago");
        system.addRoute("Mumbai", "Bangalore");
        system.addRoute("Bangalore", "Mumbai");
        system.addRoute("Kolkata", "Hyderabad");
        system.addRoute("Hyderabad", "Kolkata");
        system.addRoute("Chennai", "Delhi");
        system.addRoute("Delhi", "Chennai");
        system.addRoute("Dubai", "London");
        system.addRoute("London", "Dubai");
        system.addRoute("Singapore", "Mumbai");
        system.addRoute("Mumbai", "Singapore");
        system.addRoute("Sydney", "Brisbane");
        system.addRoute("Brisbane", "Sydney");
        system.addRoute("Toronto", "Calgary");
        system.addRoute("Calgary", "Toronto");
        system.addRoute("Tokyo", "Nagoya");
        system.addRoute("Nagoya", "Tokyo");
        system.addRoute("Beijing", "Guangzhou");
        system.addRoute("Guangzhou", "Beijing");
        system.addRoute("Cape Town", "Durban");
        system.addRoute("Durban", "Cape Town");
        system.addRoute("Mumbai", "Goa");
        system.addRoute("Goa", "Mumbai");
        system.addRoute("Bangalore", "Chennai");
        system.addRoute("Chennai", "Bangalore");
        system.addRoute("Hyderabad", "Mumbai");
        system.addRoute("Mumbai", "Hyderabad");
        system.addRoute("New York", "Dallas");
        system.addRoute("Dallas", "New York");
        system.addRoute("Chicago", "Los Angeles");
        system.addRoute("Los Angeles", "Chicago");
        system.addRoute("Mumbai", "Delhi");
        system.addRoute("Delhi", "Mumbai");
        system.addRoute("Bangalore", "Hyderabad");
        system.addRoute("Hyderabad", "Bangalore");
        system.addRoute("Kolkata", "Chennai");
        system.addRoute("Chennai", "Kolkata");
        system.addRoute("London", "Paris");
        system.addRoute("Paris", "London");
        system.addRoute("Dubai", "Mumbai");
        system.addRoute("Mumbai", "Dubai");
        system.addRoute("Singapore", "Delhi");
        system.addRoute("Delhi", "Singapore");
        system.addRoute("Sydney", "Melbourne");
        system.addRoute("Melbourne", "Sydney");
        system.addRoute("Toronto", "Vancouver");
        system.addRoute("Vancouver", "Toronto");
        system.addRoute("Tokyo", "Osaka");
        system.addRoute("Osaka", "Tokyo");
        system.addRoute("Beijing", "Shanghai");
        system.addRoute("Shanghai", "Beijing");
        system.addRoute("Cape Town", "Johannesburg");
        system.addRoute("Johannesburg", "Cape Town");
        system.addRoute("Mumbai", "Chennai");
        system.addRoute("Chennai", "Mumbai");
        system.addRoute("Bangalore", "Kolkata");
        system.addRoute("Kolkata", "Bangalore");
        system.addRoute("Hyderabad", "Delhi");
        system.addRoute("Delhi", "Hyderabad");
        system.addRoute("New York", "Los Angeles");
        system.addRoute("Los Angeles", "New York");
        system.addRoute("Chicago", "San Francisco");
        system.addRoute("San Francisco", "Chicago");
        system.addRoute("Mumbai", "Bangalore");
        system.addRoute("Bangalore", "Mumbai");
        system.addRoute("Kolkata", "Hyderabad");
        system.addRoute("Hyderabad", "Kolkata");
        system.addRoute("Chennai", "Delhi");
        system.addRoute("Delhi", "Chennai");
        system.addRoute("Dubai", "London");
        system.addRoute("London", "Dubai");
        system.addRoute("Singapore", "Mumbai");
        system.addRoute("Mumbai", "Singapore");
        system.addRoute("Sydney", "Brisbane");
        system.addRoute("Brisbane", "Sydney");
        system.addRoute("Toronto", "Calgary");
        system.addRoute("Calgary", "Toronto");
        system.addRoute("Tokyo", "Nagoya");
        system.addRoute("Nagoya", "Tokyo");
        system.addRoute("Beijing", "Guangzhou");
        system.addRoute("Guangzhou", "Beijing");
        system.addRoute("Cape Town", "Durban");
        system.addRoute("Durban", "Cape Town");
        system.addRoute("Mumbai", "Goa");
        system.addRoute("Goa", "Mumbai");
        system.addRoute("Bangalore", "Chennai");
        system.addRoute("Chennai", "Bangalore");
        system.addRoute("Hyderabad", "Mumbai");
        system.addRoute("Mumbai", "Hyderabad");
        system.addRoute("New York", "Dallas");
        system.addRoute("Dallas", "New York");
        system.addRoute("Chicago", "Los Angeles");
        system.addRoute("Los Angeles", "Chicago");
        system.addRoute("New York", "Los Angeles");
        system.addRoute("New York", "Chicago");
        system.addRoute("Los Angeles", "Chicago");
        system.addRoute("Los Angeles", "New York");
        system.addRoute("Chicago", "New York");
        system.addRoute("Chicago", "Los Angeles");
        system.addRoute("Mumbai", "Delhi");
        system.addRoute("Delhi", "Mumbai");
        system.addRoute("Bangalore", "Hyderabad");
        system.addRoute("Hyderabad", "Bangalore");
        system.addRoute("Kolkata", "Chennai");
        system.addRoute("Chennai", "Kolkata");
        system.addRoute("London", "Paris");
        system.addRoute("Paris", "London");
        system.addRoute("Dubai", "Mumbai");
        system.addRoute("Mumbai", "Dubai");
        system.addRoute("Singapore", "Delhi");
        system.addRoute("Delhi", "Singapore");
        system.addRoute("Sydney", "Melbourne");
        system.addRoute("Melbourne", "Sydney");
        system.addRoute("Toronto", "Vancouver");
        system.addRoute("Vancouver", "Toronto");
        system.addRoute("Tokyo", "Osaka");
        system.addRoute("Osaka", "Tokyo");
        system.addRoute("Beijing", "Shanghai");
        system.addRoute("Shanghai", "Beijing");
        system.addRoute("Cape Town", "Johannesburg");
        system.addRoute("Johannesburg", "Cape Town");
        system.addRoute("Mumbai", "Chennai");
        system.addRoute("Chennai", "Mumbai");
        system.addRoute("Bangalore", "Kolkata");
        system.addRoute("Kolkata", "Bangalore");

}

int module1()
{
    FlightInformationSystem system;
    initializeSystem(system);  // Initialize with predefined flights and routes

    int choice;

    do
    {
        cout << "\nMenu:\n"
             << "1. Add flight\n"
             << "2. Remove flight\n"
             << "3. Update flight time\n"
             << "4. List flights by date\n"
             << "5. List flights by airline\n"
             << "6. Find shortest route\n"
             << "7. Display all flights\n"
             << "8. Sort flights\n"
             << "9. Search flights by origin and destination\n"
             << "10. Find routes (BFS)\n"
             << "11. Find routes (DFS)\n"
             << "12. Display all flight routes\n"
             << "13. Search flights by airline and date\n"
             << "14. Update flight destination\n"
             << "15. Count flights by origin\n"
             << "16. List short distance flights\n"
             << "17. List long distance flights\n"
             << "18. List flights with lounge access\n"
             << "19. List private jet flights\n"
             << "20. Count delayed flights\n"
             << "21. Show delayed flights\n"
             << "22. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

            case 1:
            {

                string origin, destination, date, time, airline, scheduledTime;
                int distance;
                cout << "Enter flight details:" << endl;
                cout << "Origin: "; cin >> origin;
                cout << "Destination: "; cin >> destination;
                cout << "Date (DD/MM/YYYY): "; cin >> date;
                cout << "Time (HH:MM): "; cin >> time;
                cout << "Airline: "; cin >> airline;
                cout << "Distance (km): "; cin >> distance;
                cout << "Scheduled Time (HH:MM): "; cin >> scheduledTime;

                Flight newFlight(origin, destination, date, time, airline, distance, scheduledTime);
                system.addFlight(newFlight);
                break;

            }
            case 2:
            {

                string origin, destination, date, time;
                cout << "Enter flight details to remove:" << endl;
                cout << "Origin: "; cin >> origin;
                cout << "Destination: "; cin >> destination;
                cout << "Date (DD/MM/YYYY): "; cin >> date;
                cout << "Time (HH:MM): "; cin >> time;

                system.removeFlight(origin, destination, date, time);
                break;

            }
            case 3:
            {

                string origin, destination, date, oldTime, newTime;
                cout << "Enter flight details to update time:" << endl;
                cout << "Origin: "; cin >> origin;
                cout << "Destination: "; cin >> destination;
                cout << "Date (DD/MM/YYYY): "; cin >> date;
                cout << "Old Time (HH:MM): "; cin >> oldTime;
                cout << "New Time (HH:MM): "; cin >> newTime;

                system.updateFlightTime(origin, destination, date, oldTime, newTime);
                break;

            }
            case 4:
            {

                string date;
                cout << "Enter date (DD/MM/YYYY): "; cin >> date;
                system.listFlightsByDate(date);
                break;

            }
            case 5:
            {

                string airline;
                cout << "Enter airline: "; cin >> airline;
                system.listFlightsByAirline(airline);
                break;

            }
            case 6:
            {

                string start, end;
                cout << "Enter starting point: "; cin >> start;
                cout << "Enter destination point: "; cin >> end;
                system.findShortestRoute(start, end);
                break;

            }
            case 7:

                system.displayAllFlights();
                break;

            case 8:
            {

                int sortChoice;
                cout << "Sort by:\n"
                     << "1. Origin\n"
                     << "2. Destination\n"
                     << "3. Date\n"
                     << "4. Airline\n"
                     << "Enter your choice: ";
                cin >> sortChoice;

                system.sortFlights(sortChoice);
                break;

            }
            case 9:
            {

                string origin, destination;
                cout << "Enter origin: "; cin >> origin;
                cout << "Enter destination: "; cin >> destination;

                system.searchFlightsByOriginAndDestination(origin, destination);
                break;

            }
            case 10:
            {

                string start;
                cout << "Enter starting point for BFS: "; cin >> start;
                system.findRoutesBFS(start);
                break;

            }
            case 11:
            {

                string start;
                cout << "Enter starting point for DFS: "; cin >> start;
                system.findRoutesDFS(start);
                break;

            }
            case 12:

                system.displayRoutes();
                break;

            case 13:
            {

                string airline, date;
                cout << "Enter airline: "; cin >> airline;
                cout << "Enter date (DD/MM/YYYY): "; cin >> date;
                system.searchFlightsByAirlineAndDate(airline, date);
                break;

            }
            case 14:
            {

                string origin, date, time, newDestination;
                cout << "Enter flight details to update destination:" << endl;
                cout << "Origin: "; cin >> origin;
                cout << "Date (DD/MM/YYYY): "; cin >> date;
                cout << "Time (HH:MM): "; cin >> time;
                cout << "New Destination: "; cin >> newDestination;

                system.updateFlightDestination(origin, date, time, newDestination);
                break;

            }
            case 15:
            {

                string origin;
                cout << "Enter origin: "; cin >> origin;
                int count = system.countFlightsByOrigin(origin);
                cout << "Number of flights from " << origin << ": " << count << endl;
                break;

            }
            case 16:
            {

                int maxDistance;
                cout << "Enter maximum distance (km): ";
                cin >> maxDistance;
                system.listShortDistanceFlights(maxDistance);
                break;

            }
            case 17:
            {

                int minDistance;
                cout << "Enter minimum distance (km): ";
                cin >> minDistance;
                system.listLongDistanceFlights(minDistance);
                break;

            }
            case 18:
            {

                string airline;
                cout << "Enter airline for lounge access: ";
                cin >> airline;
                system.listLoungeAccessFlights(airline);
                break;

            }
            case 19:

                system.listPrivateJetFlights();
                break;

            case 20:

                system.countDelayedFlights();
                break;

            case 21:

                system.showDelayedFlights();
                break;

            case 22:

                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }

    } while (choice != 22);

    return 0;

}

// Class representing a Flights
class Flights
{
public:

    string FlightsNumber;

    string departure;

    string destination;

    string departureTime;

    int capacity;

    int bookedSeats;

    vector<string> delayReasons;

    // Default constructor
    Flights() : FlightsNumber(""), departure(""), destination(""), departureTime(""), capacity(0), bookedSeats(0) {}

    // Parameterized constructor
    Flights(string fn, string dep, string dest, string dt, int cap)

        : FlightsNumber(fn), departure(dep), destination(dest), departureTime(dt), capacity(cap), bookedSeats(0) {}

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
        cout << "Flights Number: " << FlightsNumber << "\nDeparture: " << departure

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

        oss << FlightsNumber << "," << departure << "," << destination << ","

            << departureTime << "," << capacity << "," << bookedSeats;

        for (const string &reason : delayReasons)

        {
            oss << "," << reason;
        }

        return oss.str();
    }

    static Flights fromString(const string &data)

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

        Flights Flights(fn, dep, dest, dt, cap);

        Flights.bookedSeats = booked;

        Flights.delayReasons = reasons;

        return Flights;
    }

};

// Class managing multiple Flight1
class FlightsManager

{
    map<string, Flights> Flight1;

public:

    void addFlights(const Flights &Flights)

    {
        Flight1[Flights.FlightsNumber] = Flights;
    }

    Flights *findFlights(const string &FlightsNumber)

    {
        if (Flight1.find(FlightsNumber) != Flight1.end())

        {
            return &Flight1[FlightsNumber];
        }

        return nullptr;

    }

    void displayAllFlight1() const

    {
        for (const auto &pair : Flight1)

        {
            pair.second.display();

            cout << "---------------------------" << endl;
        }

    }

    void displayFlight1ByDestination(const string &destination) const

    {
        bool found = false;

        for (const auto &pair : Flight1)

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
            cout << "No Flight1 found to destination: " << destination << endl;
        }

    }

    void displayFullyBookedFlight1() const

    {
        bool found = false;

        for (const auto &pair : Flight1)

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
            cout << "No fully booked Flight1 found." << endl;
        }

    }

    bool bookFlights(const string &FlightsNumber)

    {
        Flights *Flights = findFlights(FlightsNumber);

        if (Flights)

        {
            return Flights->bookSeat();
        }

        return false;
    }

    bool cancelFlights(const string &FlightsNumber)

    {
        Flights *Flights = findFlights(FlightsNumber);

        if (Flights)

        {
            return Flights->cancelSeat();
        }

        return false;
    }

    bool addFlightsDelay(const string &FlightsNumber, const string &reason)

    {
        Flights *Flights = findFlights(FlightsNumber);

        if (Flights)

        {
            Flights->addDelayReason(reason);

            return true;
        }

        return false;
    }

    bool modifyFlightsDetails(const string &FlightsNumber, const string &newDep, const string &newDest, const string &newTime, int newCap)

    {
        Flights *Flights = findFlights(FlightsNumber);

        if (Flights)

        {
            Flights->modifyDetails(newDep, newDest, newTime, newCap);

            return true;
        }

        return false;
    }

    bool removeFlights(const string &FlightsNumber)

    {
        return Flight1.erase(FlightsNumber) > 0;
    }

    void viewDelayReasons(const string &FlightsNumber) const

    {
        auto it = Flight1.find(FlightsNumber);

        if (it != Flight1.end())

        {
            if (!it->second.delayReasons.empty())

            {
                cout << "Delay Reasons for Flights " << FlightsNumber << ": ";

                for (const string &reason : it->second.delayReasons)

                {
                    cout << reason << "; ";
                }

                cout << endl;
            }

            else

            {
                cout << "No delay reasons recorded for Flights " << FlightsNumber << "." << endl;
            }

        }

        else

        {
            cout << "Flights " << FlightsNumber << " not found." << endl;
        }

    }

    void saveToFile(const string &filename) const

    {
        ofstream file(filename);

        for (const auto &pair : Flight1)

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
            addFlights(Flights::fromString(line));
        }

        file.close();
    }

    void displayFlightsByNumber(const string &FlightsNumber) const
    {
        auto it = Flight1.find(FlightsNumber);

        if (it != Flight1.end())

        {
            it->second.display();
        }

        else

        {
            cout << "Flights with number " << FlightsNumber << " not found.\n";
        }

    }

    int availableSeats(const string &FlightsNumber) const

    {
        auto it = Flight1.find(FlightsNumber);

        if (it != Flight1.end())

        {
            return it->second.capacity - it->second.bookedSeats;
        }

        cout << "Flights not found!\n";

        return 0;
    }

    void displayFlight1ByDeparture(const string &departure) const

    {
        bool found = false;

        for (const auto &pair : Flight1)

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
            cout << "No Flight1 found departing from: " << departure << endl;
        }

    }

    void displayNonFullyBookedFlight1() const

    {
        bool found = false;

        for (const auto &pair : Flight1)
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
            cout << "No Flight1 are available with unbooked seats.\n";
        }
    }

    void displayFlight1ByCapacity(int capacity) const

    {
        bool found = false;

        for (const auto &pair : Flight1)
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
            cout << "No Flight1 found with capacity: " << capacity << endl;
        }
    }

    void displayFlight1ByTimeRange(const string &startTime, const string &endTime) const

    {
        bool found = false;

        for (const auto &pair : Flight1)

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
            cout << "No Flight1 found within the time range: " << startTime << " to " << endTime << endl;
        }
    }

    bool updateFlightsDepartureTime(const string &FlightsNumber, const string &newTime)

    {
        Flights *Flights = findFlights(FlightsNumber);

        if (Flights)

        {
            Flights->departureTime = newTime;

            return true;
        }

        return false;
    }

    void displayFlight1WithSpecificDelayReason(const string &reason) const

    {
        bool found = false;

        for (const auto &pair : Flight1)

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
            cout << "No Flight1 found with delay reason: " << reason << endl;
        }
    }

};

// Menu display
void menu()
{
    cout << "\nFlights Route Management System\n";

    cout << "1. Add Flights\n";

    cout << "2. Display All Flight1\n";

    cout << "3. Book a Flights\n";

    cout << "4. Cancel a Flights\n";

    cout << "5. Add Delay Reason to a Flights\n";

    cout << "6. View Delay Reasons of a Flights\n";

    cout << "7. Modify Flights Details\n";

    cout << "8. Remove Flights\n";

    cout << "9. Display Flight1 by Destination\n";

    cout << "10. Display Fully Booked Flight1\n";

    cout << "11. Save Flight1 to File\n";

    cout << "12. Load Flight1 from File\n";

    cout << "13. Display Flights by Flights Number\n";

    cout << "14. Display Available Seats\n";

    cout << "15. Display Flight1 by Departure\n";

    cout << "16. Display Non-Fully Booked Flight1\n";

    cout << "17. Display Flight1 by Capacity\n";

    cout << "18. Display Flight1 by Time Range\n";

    cout << "19. Update Flights Departure Time\n";

    cout << "20. Display Flight1 with Specific Delay Reason\n";

    cout << "Enter your choice: ";
}

// Main function to run the Flights management system
int module2()
{
    FlightsManager FlightsManager;

    FlightsManager.loadFromFile("Flight1.txt");

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

            cout << "Enter Flights Number: ";

            getline(cin, fn);

            cout << "Enter Departure City: ";

            getline(cin, dep);

            cout << "Enter Destination City: ";

            getline(cin, dest);

            cout << "Enter Departure Time: ";

            getline(cin, dt);

            cout << "Enter Capacity: ";

            cin >> cap;

            FlightsManager.addFlights(Flights(fn, dep, dest, dt, cap));

            cout << "Flights added successfully!" << endl;

            break;
        }

        case 2:

            FlightsManager.displayAllFlight1();

            break;

        case 3:

        {
            string FlightsNumber;

            cout << "Enter Flights Number to Book: ";

            getline(cin, FlightsNumber);

            if (FlightsManager.bookFlights(FlightsNumber))

            {
                cout << "Flights booked successfully!" << endl;
            }

            else

            {
                cout << "Unable to book the Flights. It may be fully booked." << endl;
            }

            break;
        }

        case 4:

        {
            string FlightsNumber;

            cout << "Enter Flights Number to Cancel: ";

            getline(cin, FlightsNumber);

            if (FlightsManager.cancelFlights(FlightsNumber))

            {
                cout << "Flights cancelled successfully!" << endl;
            }

            else
            {
                cout << "Unable to cancel the Flights. No seats were booked." << endl;
            }

            break;

        }

        case 5:

        {
            string FlightsNumber, reason;

            cout << "Enter Flights Number to Add Delay Reason: ";

            getline(cin, FlightsNumber);

            cout << "Enter Delay Reason: ";

            getline(cin, reason);

            if (FlightsManager.addFlightsDelay(FlightsNumber, reason))

            {
                cout << "Delay reason added successfully!" << endl;
            }

            else

            {
                cout << "Unable to add delay reason. Flights not found." << endl;
            }

            break;
        }

        case 6:

        {
            string FlightsNumber;

            cout << "Enter Flights Number to View Delay Reasons: ";

            getline(cin, FlightsNumber);

            FlightsManager.viewDelayReasons(FlightsNumber);

            break;
        }

        case 7:

        {
            string FlightsNumber, newDep, newDest, newTime;

            int newCap;

            cout << "Enter Flights Number to Modify: ";

            getline(cin, FlightsNumber);

            cout << "Enter New Departure City: ";

            getline(cin, newDep);

            cout << "Enter New Destination City: ";

            getline(cin, newDest);

            cout << "Enter New Departure Time: ";

            getline(cin, newTime);

            cout << "Enter New Capacity: ";

            cin >> newCap;

            if (FlightsManager.modifyFlightsDetails(FlightsNumber, newDep, newDest, newTime, newCap))

            {
                cout << "Flights details modified successfully!" << endl;
            }

            else

            {
                cout << "Unable to modify Flights details. Flights not found." << endl;
            }

            break;
        }

        case 8:

        {
            string FlightsNumber;

            cout << "Enter Flights Number to Remove: ";

            getline(cin, FlightsNumber);

            if (FlightsManager.removeFlights(FlightsNumber))

            {
                cout << "Flights removed successfully!" << endl;
            }

            else

            {
                cout << "Unable to remove Flights. Flights not found." << endl;
            }

            break;
        }

        case 9:

        {
            string destination;

            cout << "Enter Destination City to View Flight1: ";

            getline(cin, destination);

            FlightsManager.displayFlight1ByDestination(destination);

            break;
        }

        case 10:

            FlightsManager.displayFullyBookedFlight1();

            break;

        case 11:

        {
            string filename;

            cout << "Enter filename to save Flight1 to: ";

            getline(cin, filename);

            FlightsManager.saveToFile(filename);

            cout << "Flight1 saved to file successfully!" << endl;

            break;
        }

        case 12:

        {
            string filename;

            cout << "Enter filename to load Flight1 from: ";

            getline(cin, filename);

            FlightsManager.loadFromFile(filename);

            cout << "Flight1 loaded from file successfully!" << endl;

            break;
        }

        case 13:

        {
            string FlightsNumber;

            cout << "Enter Flights Number to Display: ";

            getline(cin, FlightsNumber);

            FlightsManager.displayFlightsByNumber(FlightsNumber);

            break;
        }

        case 14:

        {
            string FlightsNumber;

            cout << "Enter Flights Number to Check Available Seats: ";

            getline(cin, FlightsNumber);

            int available = FlightsManager.availableSeats(FlightsNumber);

            if (available > 0)
            {
                cout << "Available Seats: " << available << endl;
            }

            else

            {
                cout << "No available seats or Flights not found." << endl;
            }

            break;
        }

        case 15:

        {
            string departure;

            cout << "Enter Departure City to View Flight1: ";

            getline(cin, departure);

            FlightsManager.displayFlight1ByDeparture(departure);

            break;
        }

        case 16:

            FlightsManager.displayNonFullyBookedFlight1();

            break;

        case 17:

        {
            int capacity;

            cout << "Enter Capacity to View Flight1: ";

            cin >> capacity;

            FlightsManager.displayFlight1ByCapacity(capacity);

            break;
        }

        case 18:

        {
            string startTime, endTime;

            cout << "Enter Start Time (HH:MM): ";

            getline(cin, startTime);

            cout << "Enter End Time (HH:MM): ";

            getline(cin, endTime);

            FlightsManager.displayFlight1ByTimeRange(startTime, endTime);

            break;
        }

        case 19:

        {
            string FlightsNumber, newTime;

            cout << "Enter Flights Number to Update Departure Time: ";

            getline(cin, FlightsNumber);

            cout << "Enter New Departure Time (HH:MM): ";

            getline(cin, newTime);

            if (FlightsManager.updateFlightsDepartureTime(FlightsNumber, newTime))
            {
                cout << "Flights departure time updated successfully!" << endl;
            }

            else
            {
                cout << "Unable to update departure time. Flights not found." << endl;
            }

            break;
        }

        case 20:

        {
            string reason;

            cout << "Enter Delay Reason to View Flight1: ";

            getline(cin, reason);

            FlightsManager.displayFlight1WithSpecificDelayReason(reason);

            break;
        }

        default:

            cout << "Invalid choice. Please try again." << endl;

            break;
        }

    } while (choice != 0);

    return 0;
}
