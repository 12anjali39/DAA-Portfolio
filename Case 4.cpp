#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;

// Define a struct for Baggage
struct Baggage {
    string id;
    string passengerName;
    string flightNumber;
    string destination;
    string timestamp;
    double weight; // New field to store baggage weight
    bool isDamaged;
    bool isCabinBaggage;
    bool isLongDistance;
    bool isLaptopBag;  // New field to indicate if the baggage is a laptop bag
    bool isTiffinBag;  // New field to indicate if the baggage is a tiffin bag
    bool isSportsBag;  // New field to indicate if the baggage is a sports bag
    bool isMusicalInstrumentBag; // New field to indicate if the baggage is a musical instrument bag
    bool isMedicalEquipmentBag; // New field to indicate if the baggage is a medical equipment bag
    bool isHandbag; // New field to indicate if the baggage is a handbag
    bool isSmallSuitcase; // New field to indicate if the baggage is a small suitcase
};

// Define a class for BaggageHandlingSystem
class BaggageHandlingSystem {
private:
    map<string, Baggage> baggageMap; // Map to store baggage information

    // Helper function to get the current timestamp
    string getCurrentTimestamp() {
        time_t now = time(0);
        char buf[80];
        struct tm* timeinfo = localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
        return string(buf);
    }

    // Helper function to sort baggage by timestamp (ascending order)
    vector<Baggage> sortBaggageByTimestamp() {
        vector<Baggage> sortedBaggage;
        for (const auto& entry : baggageMap) {
            sortedBaggage.push_back(entry.second);
        }

        sort(sortedBaggage.begin(), sortedBaggage.end(), [](const Baggage& a, const Baggage& b) {
            return a.timestamp < b.timestamp;
        });
        return sortedBaggage;
    }

public:
    // Function to add baggage
    void addBaggage(const string& id, const string& passengerName, const string& flightNumber, const string& destination, double weight,
                    bool isLaptopBag = false, bool isTiffinBag = false, bool isSportsBag = false, bool isMusicalInstrumentBag = false, bool isMedicalEquipmentBag = false,
                    bool isHandbag = false, bool isSmallSuitcase = false) {
        Baggage baggage;
        baggage.id = id;
        baggage.passengerName = passengerName;
        baggage.flightNumber = flightNumber;
        baggage.destination = destination;
        baggage.timestamp = getCurrentTimestamp();
        baggage.weight = weight;
        baggage.isDamaged = false; // Default values
        baggage.isCabinBaggage = false; // Default values
        baggage.isLongDistance = false; // Default values
        baggage.isLaptopBag = isLaptopBag;
        baggage.isTiffinBag = isTiffinBag;
        baggage.isSportsBag = isSportsBag;
        baggage.isMusicalInstrumentBag = isMusicalInstrumentBag;
        baggage.isMedicalEquipmentBag = isMedicalEquipmentBag;
        baggage.isHandbag = isHandbag;
        baggage.isSmallSuitcase = isSmallSuitcase;

        baggageMap[id] = baggage;
        cout << "Baggage added successfully!" << endl;
    }

    // Function to remove baggage
    void removeBaggage(const string& id) {
        if (baggageMap.find(id) != baggageMap.end()) {
            baggageMap.erase(id);
            cout << "Baggage removed successfully!" << endl;
        } else {
            cout << "Baggage not found!" << endl;
        }
    }

    // Function to display baggage information
    void displayBaggageInfo(const string& id) const {
        if (baggageMap.find(id) != baggageMap.end()) {
            const Baggage& baggage = baggageMap.at(id);
            cout << "Baggage ID: " << baggage.id << endl;
            cout << "Passenger Name: " << baggage.passengerName << endl;
            cout << "Flight Number: " << baggage.flightNumber << endl;
            cout << "Destination: " << baggage.destination << endl;
            cout << "Timestamp: " << baggage.timestamp << endl;
            cout << "Weight: " << baggage.weight << " kg" << endl;
            cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
            cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
            cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
            cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
            cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
            cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
            cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
            cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
            cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
            cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
        } else {
            cout << "Baggage not found!" << endl;
        }
    }

    // Function to display all baggage information
    void displayAllBaggageInfo() const {
        if (baggageMap.empty()) {
            cout << "No baggage records found!" << endl;
            return;
        }

        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            cout << "Baggage ID: " << baggage.id << endl;
            cout << "Passenger Name: " << baggage.passengerName << endl;
            cout << "Flight Number: " << baggage.flightNumber << endl;
            cout << "Destination: " << baggage.destination << endl;
            cout << "Timestamp: " << baggage.timestamp << endl;
            cout << "Weight: " << baggage.weight << " kg" << endl;
            cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
            cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
            cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
            cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
            cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
            cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
            cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
            cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
            cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
            cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
            cout << "-----------------------------" << endl;
        }
    }

    // Function to update baggage information
    void updateBaggage(const string& id, const string& newPassengerName, const string& newFlightNumber, const string& newDestination, double newWeight,
                       bool newIsLaptopBag = false, bool newIsTiffinBag = false, bool newIsSportsBag = false, bool newIsMusicalInstrumentBag = false, bool newIsMedicalEquipmentBag = false,
                       bool newIsHandbag = false, bool newIsSmallSuitcase = false) {
        if (baggageMap.find(id) != baggageMap.end()) {
            Baggage& baggage = baggageMap[id];
            baggage.passengerName = newPassengerName;
            baggage.flightNumber = newFlightNumber;
            baggage.destination = newDestination;
            baggage.weight = newWeight;
            baggage.isLaptopBag = newIsLaptopBag;
            baggage.isTiffinBag = newIsTiffinBag;
            baggage.isSportsBag = newIsSportsBag;
            baggage.isMusicalInstrumentBag = newIsMusicalInstrumentBag;
            baggage.isMedicalEquipmentBag = newIsMedicalEquipmentBag;
            baggage.isHandbag = newIsHandbag;
            baggage.isSmallSuitcase = newIsSmallSuitcase;
            cout << "Baggage information updated successfully!" << endl;
        } else {
            cout << "Baggage not found!" << endl;
        }
    }

    // Function to display total baggage count
    void displayTotalBaggageCount() const {
        cout << "Total number of baggage records: " << baggageMap.size() << endl;
    }

    // Function to display total baggage weight
    void displayTotalBaggageWeight() const {
        double totalWeight = 0;
        for (const auto& entry : baggageMap) {
            totalWeight += entry.second.weight;
        }
        cout << "Total weight of all baggage: " << totalWeight << " kg" << endl;
    }

    // Function to display the heaviest baggage
    void displayHeaviestBaggage() const {
        if (baggageMap.empty()) {
            cout << "No baggage records found!" << endl;
            return;
        }

        auto heaviest = max_element(baggageMap.begin(), baggageMap.end(), [](const auto& a, const auto& b) {
            return a.second.weight < b.second.weight;
        });

        const Baggage& baggage = heaviest->second;
        cout << "Heaviest Baggage ID: " << baggage.id << endl;
        cout << "Passenger Name: " << baggage.passengerName << endl;
        cout << "Flight Number: " << baggage.flightNumber << endl;
        cout << "Destination: " << baggage.destination << endl;
        cout << "Timestamp: " << baggage.timestamp << endl;
        cout << "Weight: " << baggage.weight << " kg" << endl;
    }

    // Function to display the lightest baggage
    void displayLightestBaggage() const {
        if (baggageMap.empty()) {
            cout << "No baggage records found!" << endl;
            return;
        }

        auto lightest = min_element(baggageMap.begin(), baggageMap.end(), [](const auto& a, const auto& b) {
            return a.second.weight < b.second.weight;
        });

        const Baggage& baggage = lightest->second;
        cout << "Lightest Baggage ID: " << baggage.id << endl;
        cout << "Passenger Name: " << baggage.passengerName << endl;
        cout << "Flight Number: " << baggage.flightNumber << endl;
        cout << "Destination: " << baggage.destination << endl;
        cout << "Timestamp: " << baggage.timestamp << endl;
        cout << "Weight: " << baggage.weight << " kg" << endl;
    }

    // Function to display baggage within a specific weight range
    void displayBaggageWithinWeightRange(double minWeight, double maxWeight) const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.weight >= minWeight && baggage.weight <= maxWeight) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
                cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
                cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No baggage found within the weight range " << minWeight << " kg to " << maxWeight << " kg." << endl;
        }
    }

    // Function to calculate and display the average weight of all baggage
    void displayAverageBaggageWeight() const {
        if (baggageMap.empty()) {
            cout << "No baggage records found!" << endl;
            return;
        }

        double totalWeight = 0;
        for (const auto& entry : baggageMap) {
            totalWeight += entry.second.weight;
        }
        double averageWeight = totalWeight / baggageMap.size();
        cout << "Average weight of all baggage: " << averageWeight << " kg" << endl;
    }

    // Function to search baggage by passenger name
    void searchBaggageByName(const string& name) const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.passengerName == name) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
                cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
                cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No baggage found for passenger: " << name << endl;
        }
    }

    // Function to display baggage information for a specific flight
    void displayBaggageForFlight(const string& flightNumber) const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.flightNumber == flightNumber) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
               cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No baggage found for flight number: " << flightNumber << endl;
        }
    }

    // Function to display the heaviest baggage for a specific flight
    void displayHeaviestBaggageForFlight(const string& flightNumber) const {
        bool found = false;
        double maxWeight = -1;
        Baggage heaviestBaggage;

        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.flightNumber == flightNumber && baggage.weight > maxWeight) {
                maxWeight = baggage.weight;
                heaviestBaggage = baggage;
                found = true;
            }
        }

        if (found) {
            cout << "Heaviest Baggage for Flight Number " << flightNumber << ":\n";
            cout << "Baggage ID: " << heaviestBaggage.id << endl;
            cout << "Passenger Name: " << heaviestBaggage.passengerName << endl;
            cout << "Flight Number: " << heaviestBaggage.flightNumber << endl;
            cout << "Destination: " << heaviestBaggage.destination << endl;
            cout << "Timestamp: " << heaviestBaggage.timestamp << endl;
            cout << "Weight: " << heaviestBaggage.weight << " kg" << endl;
        } else {
            cout << "No baggage found for flight number: " << flightNumber << endl;
        }
    }

    // Function to display the lightest baggage for a specific flight
    void displayLightestBaggageForFlight(const string& flightNumber) const {
        bool found = false;
        double minWeight = numeric_limits<double>::max();
        Baggage lightestBaggage;

        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.flightNumber == flightNumber && baggage.weight < minWeight) {
                minWeight = baggage.weight;
                lightestBaggage = baggage;
                found = true;
            }
        }

        if (found) {
            cout << "Lightest Baggage for Flight Number " << flightNumber << ":\n";
            cout << "Baggage ID: " << lightestBaggage.id << endl;
            cout << "Passenger Name: " << lightestBaggage.passengerName << endl;
            cout << "Flight Number: " << lightestBaggage.flightNumber << endl;
            cout << "Destination: " << lightestBaggage.destination << endl;
            cout << "Timestamp: " << lightestBaggage.timestamp << endl;
            cout << "Weight: " << lightestBaggage.weight << " kg" << endl;
        } else {
            cout << "No baggage found for flight number: " << flightNumber << endl;
        }
    }

    // Function to display sorted baggage information by timestamp
    void displaySortedBaggageByTimestamp() {
        vector<Baggage> sortedBaggage = sortBaggageByTimestamp();
        for (const auto& baggage : sortedBaggage) {
            cout << "Baggage ID: " << baggage.id << endl;
            cout << "Passenger Name: " << baggage.passengerName << endl;
            cout << "Flight Number: " << baggage.flightNumber << endl;
            cout << "Destination: " << baggage.destination << endl;
            cout << "Timestamp: " << baggage.timestamp << endl;
            cout << "Weight: " << baggage.weight << " kg" << endl;
            cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
            cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
            cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
            cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
            cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
            cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
            cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
            cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
            cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
            cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
            cout << "-----------------------------" << endl;
        }
    }

    // Function to filter and display baggage by destination
    void filterBaggageByDestination(const string& destination) const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.destination == destination) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
                cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
                cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No baggage found for destination: " << destination << endl;
        }
    }

    // Function to display laptop bags
    void displayLaptopBags() const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.isLaptopBag) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
                cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
                cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No laptop bags found!" << endl;
        }
    }

    // Function to display tiffin bags
    void displayTiffinBags() const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.isTiffinBag) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance:cout << Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
                cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
                cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No tiffin bags found!" << endl;
        }
    }

    // Function to display sports bags
    void displaySportsBags() const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.isSportsBag) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
                cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
                cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No sports bags found!" << endl;
        }
    }

    // Function to display musical instrument bags
    void displayMusicalInstrumentBags() const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.isMusicalInstrumentBag) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
                cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
                cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No musical instrument bags found!" << endl;
        }
    }

    // Function to display medical equipment bags
    void displayMedicalEquipmentBags() const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.isMedicalEquipmentBag) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
                cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
                cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No medical equipment bags found!" << endl;
        }
    }

    // Function to display handbags
    void displayHandbags() const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.isHandbag) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
                cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
                cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No handbags found!" << endl;
        }
    }

    // Function to display small suitcases
    void displaySmallSuitcases() const {
        bool found = false;
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            if (baggage.isSmallSuitcase) {
                cout << "Baggage ID: " << baggage.id << endl;
                cout << "Passenger Name: " << baggage.passengerName << endl;
                cout << "Flight Number: " << baggage.flightNumber << endl;
                cout << "Destination: " << baggage.destination << endl;
                cout << "Timestamp: " << baggage.timestamp << endl;
                cout << "Weight: " << baggage.weight << " kg" << endl;
                cout << "Is Damaged: " << (baggage.isDamaged ? "Yes" : "No") << endl;
                cout << "Is Cabin Baggage: " << (baggage.isCabinBaggage ? "Yes" : "No") << endl;
                cout << "Is Long Distance: " << (baggage.isLongDistance ? "Yes" : "No") << endl;
                cout << "Is Laptop Bag: " << (baggage.isLaptopBag ? "Yes" : "No") << endl;
                cout << "Is Tiffin Bag: " << (baggage.isTiffinBag ? "Yes" : "No") << endl;
                cout << "Is Sports Bag: " << (baggage.isSportsBag ? "Yes" : "No") << endl;
                cout << "Is Musical Instrument Bag: " << (baggage.isMusicalInstrumentBag ? "Yes" : "No") << endl;
                cout << "Is Medical Equipment Bag: " << (baggage.isMedicalEquipmentBag ? "Yes" : "No") << endl;
                cout << "Is Handbag: " << (baggage.isHandbag ? "Yes" : "No") << endl;
                cout << "Is Small Suitcase: " << (baggage.isSmallSuitcase ? "Yes" : "No") << endl;
                cout << "-----------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No small suitcases found!" << endl;
        }
    }

    // Function to display total number of laptop bags
    void displayTotalLaptopBags() const {
        int count = 0;
        for (const auto& entry : baggageMap) {
            if (entry.second.isLaptopBag) {
                count++;
            }
        }
        cout << "Total number of laptop bags: " << count << endl;
    }

    // Function to display total number of tiffin bags
    void displayTotalTiffinBags() const {
        int count = 0;
        for (const auto& entry : baggageMap) {
            if (entry.second.isTiffinBag) {
                count++;
            }
        }
        cout << "Total number of tiffin bags: " << count << endl;
    }

    // Function to display total number of sports bags
    void displayTotalSportsBags() const {
        int count = 0;
        for (const auto& entry : baggageMap) {
            if (entry.second.isSportsBag) {
                count++;
            }
        }
        cout << "Total number of sports bags: " << count << endl;
    }

    // Function to display total number of musical instrument bags
    void displayTotalMusicalInstrumentBags() const {
        int count = 0;
        for (const auto& entry : baggageMap) {
            if (entry.second.isMusicalInstrumentBag) {
                count++;
            }
        }
        cout << "Total number of musical instrument bags: " << count << endl;
    }

    // Function to display total number of medical equipment bags
    void displayTotalMedicalEquipmentBags() const {
        int count = 0;
        for (const auto& entry : baggageMap) {
            if (entry.second.isMedicalEquipmentBag) {
                count++;
            }
        }
        cout << "Total number of medical equipment bags: " << count << endl;
    }

    // Function to display total number of handbags
    void displayTotalHandbags() const {
        int count = 0;
        for (const auto& entry : baggageMap) {
            if (entry.second.isHandbag) {
                count++;
            }
        }
        cout << "Total number of handbags: " << count << endl;
    }

    // Function to display total number of small suitcases
    void displayTotalSmallSuitcases() const {
        int count = 0;
        for (const auto& entry : baggageMap) {
            if (entry.second.isSmallSuitcase) {
                count++;
            }
        }
        cout << "Total number of small suitcases: " << count << endl;
    }

    // Function to save baggage data to a file
    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error opening file for writing!" << endl;
            return;
        }
        for (const auto& entry : baggageMap) {
            const Baggage& baggage = entry.second;
            outFile << baggage.id << "," << baggage.passengerName << "," << baggage.flightNumber << "," << baggage.destination << ","
                    << baggage.timestamp << "," << baggage.weight << "," << baggage.isDamaged << "," << baggage.isCabinBaggage << ","
                    << baggage.isLongDistance << "," << baggage.isLaptopBag << "," << baggage.isTiffinBag << ","
                    << baggage.isSportsBag << "," << baggage.isMusicalInstrumentBag << "," << baggage.isMedicalEquipmentBag << ","
                    << baggage.isHandbag << "," << baggage.isSmallSuitcase << endl;
        }
        cout << "Baggage data saved to " << filename << " successfully!" << endl;
        outFile.close();
    }

    // Function to load baggage data from a file
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Error opening file for reading!" << endl;
            return;
        }
        string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);
            size_t pos5 = line.find(',', pos4 + 1);
            size_t pos6 = line.find(',', pos5 + 1);
            size_t pos7 = line.find(',', pos6 + 1);
            size_t pos8 = line.find(',', pos7 + 1);
            size_t pos9 = line.find(',', pos8 + 1);
            size_t pos10 = line.find(',', pos9 + 1);
            size_t pos11 = line.find(',', pos10 + 1);
            size_t pos12 = line.find(',', pos11 + 1);
            size_t pos13 = line.find(',', pos12 + 1);
            size_t pos14 = line.find(',', pos13 + 1);
            size_t pos15 = line.find(',', pos14 + 1);

            string id = line.substr(0, pos1);
            string passengerName = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string flightNumber = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string destination = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string timestamp = line.substr(pos4 + 1, pos5 - pos4 - 1);
            double weight = stod(line.substr(pos5 + 1, pos6 - pos5 - 1));
            bool isDamaged = line.substr(pos6 + 1, pos7 - pos6 - 1) == "1";
            bool isCabinBaggage = line.substr(pos7 + 1, pos8 - pos7 - 1) == "1";
            bool isLongDistance = line.substr(pos8 + 1, pos9 - pos8 - 1) == "1";
            bool isLaptopBag = line.substr(pos9 + 1, pos10 - pos9 - 1) == "1";
            bool isTiffinBag = line.substr(pos10 + 1, pos11 - pos10 - 1) == "1";
            bool isSportsBag = line.substr(pos11 + 1, pos12 - pos11 - 1) == "1";
            bool isMusicalInstrumentBag = line.substr(pos12 + 1, pos13 - pos12 - 1) == "1";
            bool isMedicalEquipmentBag = line.substr(pos13 + 1, pos14 - pos13 - 1) == "1";
            bool isHandbag = line.substr(pos14 + 1, pos15 - pos14 - 1) == "1";
            bool isSmallSuitcase = line.substr(pos15 + 1) == "1";

            Baggage baggage{id, passengerName, flightNumber, destination, timestamp, weight, isDamaged, isCabinBaggage, isLongDistance, isLaptopBag, isTiffinBag, isSportsBag, isMusicalInstrumentBag, isMedicalEquipmentBag, isHandbag, isSmallSuitcase};
            baggageMap[id] = baggage;
        }
        cout << "Baggage data loaded from " << filename << " successfully!" << endl;
        inFile.close();
    }
};

int main() {
    BaggageHandlingSystem bhs;

    while (true) {
        cout << "\nBaggage Handling System\n";
        cout << "1. Add Baggage\n";
        cout << "2. Remove Baggage\n";
        cout << "3. Display Baggage Information\n";
        cout << "4. Display All Baggage Information\n";
        cout << "5. Search Baggage by Passenger Name\n";
        cout << "6. Update Baggage Information\n";
        cout << "7. Display Total Baggage Count\n";
        cout << "8. Display Total Baggage Weight\n";
        cout << "9. Display Heaviest Baggage\n";
        cout << "10. Display Lightest Baggage\n";
        cout << "11. Save to File\n";
        cout << "12. Load from File\n";
        cout << "13. Display Sorted Baggage by Timestamp\n";
        cout << "14. Filter Baggage by Destination\n";
        cout << "15. Display Average Baggage Weight\n";
        cout << "16. Display Baggage for Specific Flight\n";
        cout << "17. Display Heaviest Baggage for Specific Flight\n";
        cout << "18. Display Lightest Baggage for Specific Flight\n";
        cout << "19. Display Baggage within Weight Range\n";
        cout << "20. Display Laptop Bags\n";
        cout << "21. Display Tiffin Bags\n";
        cout << "22. Display Total Laptop Bags\n";
        cout << "23. Display Total Tiffin Bags\n";
        cout << "24. Display Sports Bags\n";
        cout << "25. Display Total Sports Bags\n";
        cout << "26. Display Musical Instrument Bags\n";
        cout << "27. Display Total Musical Instrument Bags\n";
        cout << "28. Display Medical Equipment Bags\n";
        cout << "29. Display Total Medical Equipment Bags\n";
        cout << "30. Display Handbags\n";
        cout << "31. Display Total Handbags\n";
        cout << "32. Display Small Suitcases\n";
        cout << "33. Display Total Small Suitcases\n";
        cout << "34. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 34) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
            cout << "Invalid choice. Please choose a valid option." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                string id, passengerName, flightNumber, destination;
                double weight;
                bool isLaptopBag, isTiffinBag, isSportsBag, isMusicalInstrumentBag, isMedicalEquipmentBag, isHandbag, isSmallSuitcase;
                cout << "Enter Baggage ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Passenger Name: ";
                getline(cin, passengerName);
                cout << "Enter Flight Number: ";
                getline(cin, flightNumber);
                cout << "Enter Destination: ";
                getline(cin, destination);
                cout << "Enter Weight (in kg): ";
                cin >> weight;
                cout << "Is Laptop Bag? (1 for Yes, 0 for No): ";
                cin >> isLaptopBag;
                cout << "Is Tiffin Bag? (1 for Yes, 0 for No): ";
                cin >> isTiffinBag;
                cout << "Is Sports Bag? (1 for Yes, 0 for No): ";
                cin >> isSportsBag;
                cout << "Is Musical Instrument Bag? (1 for Yes, 0 for No): ";
                cin >> isMusicalInstrumentBag;
                cout << "Is Medical Equipment Bag? (1 for Yes, 0 for No): ";
                cin >> isMedicalEquipmentBag;
                cout << "Is Handbag? (1 for Yes, 0 for No): ";
                cin >> isHandbag;
                cout << "Is Small Suitcase? (1 for Yes, 0 for No): ";
                cin >> isSmallSuitcase;
                bhs.addBaggage(id, passengerName, flightNumber, destination, weight, isLaptopBag, isTiffinBag, isSportsBag, isMusicalInstrumentBag, isMedicalEquipmentBag, isHandbag, isSmallSuitcase);
                break;
            }
            case 2: {
                string id;
                cout << "Enter Baggage ID: ";
                cin >> id;
                bhs.removeBaggage(id);
                break;
            }
            case 3: {
                string id;
                cout << "Enter Baggage ID: ";
                cin >> id;
                bhs.displayBaggageInfo(id);
                break;
            }
            case 4:
                bhs.displayAllBaggageInfo();
                break;
            case 5: {
                string name;
                cin.ignore();
                cout << "Enter Passenger Name: ";
                getline(cin, name);
                bhs.searchBaggageByName(name);
                break;
            }
            case 6: {
                string id, newPassengerName, newFlightNumber, newDestination;
                double newWeight;
                bool newIsLaptopBag, newIsTiffinBag, newIsSportsBag, newIsMusicalInstrumentBag, newIsMedicalEquipmentBag, newIsHandbag, newIsSmallSuitcase;
                cout << "Enter Baggage ID to update: ";
                cin >> id;
                cin.ignore();
                cout << "Enter New Passenger Name: ";
                getline(cin, newPassengerName);
                cout << "Enter New Flight Number: ";
                getline(cin, newFlightNumber);
                cout << "Enter New Destination: ";
                getline(cin, newDestination);
                cout << "Enter New Weight (in kg): ";
                cin >> newWeight;
                cout << "Is Laptop Bag? (1 for Yes, 0 for No): ";
                cin >> newIsLaptopBag;
                cout << "Is Tiffin Bag? (1 for Yes, 0 for No): ";
                cin >> newIsTiffinBag;
                cout << "Is Sports Bag? (1 for Yes, 0 for No): ";
                cin >> newIsSportsBag;
                cout << "Is Musical Instrument Bag? (1 for Yes, 0 for No): ";
                cin >> newIsMusicalInstrumentBag;
                cout << "Is Medical Equipment Bag? (1 for Yes, 0 for No): ";
                cin >> newIsMedicalEquipmentBag;
                cout << "Is Handbag? (1 for Yes, 0 for No): ";
                cin >> newIsHandbag;
                cout << "Is Small Suitcase? (1 for Yes, 0 for No): ";
                cin >> newIsSmallSuitcase;
                bhs.updateBaggage(id, newPassengerName, newFlightNumber, newDestination, newWeight, newIsLaptopBag, newIsTiffinBag, newIsSportsBag, newIsMusicalInstrumentBag, newIsMedicalEquipmentBag, newIsHandbag, newIsSmallSuitcase);
                break;
            }
            case 7:
                bhs.displayTotalBaggageCount();
                break;
            case 8:
                bhs.displayTotalBaggageWeight();
                break;
            case 9:
                bhs.displayHeaviestBaggage();
                break;
            case 10:
                bhs.displayLightestBaggage();
                break;
            case 11: {
                string filename;
                cout << "Enter filename to save: ";
                cin >> filename;
                bhs.saveToFile(filename);
                break;
            }
            case 12: {
                string filename;
                cout << "Enter filename to load: ";
                cin >> filename;
                bhs.loadFromFile(filename);
                break;
            }
            case 13:
                bhs.displaySortedBaggageByTimestamp();
                break;
            case 14: {
                string destination;
                cin.ignore();
                cout << "Enter Destination: ";
                getline(cin, destination);
                bhs.filterBaggageByDestination(destination);
                break;
            }
            case 15:
                bhs.displayAverageBaggageWeight();
                break;
            case 16: {
                string flightNumber;
                cout << "Enter Flight Number: ";
                cin >> flightNumber;
                bhs.displayBaggageForFlight(flightNumber);
                break;
            }
            case 17: {
                string flightNumber;
                cout << "Enter Flight Number: ";
                cin >> flightNumber;
                bhs.displayHeaviestBaggageForFlight(flightNumber);
                break;
            }
            case 18: {
                string flightNumber;
                cout << "Enter Flight Number: ";
                cin >> flightNumber;
                bhs.displayLightestBaggageForFlight(flightNumber);
                break;
            }
            case 19: {
                double minWeight, maxWeight;
                cout << "Enter Minimum Weight (in kg): ";
                cin >> minWeight;
                cout << "Enter Maximum Weight (in kg): ";
                cin >> maxWeight;
                bhs.displayBaggageWithinWeightRange(minWeight, maxWeight);
                break;
            }
            case 20:
                bhs.displayLaptopBags();
                break;
            case 21:
                bhs.displayTiffinBags();
                break;
            case 22:
                bhs.displayTotalLaptopBags();
                break;
            case 23:
                bhs.displayTotalTiffinBags();
                break;
            case 24:
                bhs.displaySportsBags();
                break;
            case 25:
                bhs.displayTotalSportsBags();
                break;
            case 26:
                bhs.displayMusicalInstrumentBags();
                break;
            case 27:
                bhs.displayTotalMusicalInstrumentBags();
                break;
            case 28:
                bhs.displayMedicalEquipmentBags();
                break;
            case 29:
                bhs.displayTotalMedicalEquipmentBags();
                break;
            case 30:
                bhs.displayHandbags();
                break;
            case 31:
                bhs.displayTotalHandbags();
                break;
            case 32:
                bhs.displaySmallSuitcases();
                break;
            case 33:
                bhs.displayTotalSmallSuitcases();
                break;
            case 34:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }
    return 0;
}
