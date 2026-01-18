//Aras Soylu, Section 2, 22401732
#ifndef BILKENTTOURISM_H
#define BILKENTTOURISM_H

#include <string>
using namespace std;

class BilkentTourism {
public:
    BilkentTourism();
    ~BilkentTourism();

    void addBusLine(const int lineId, const string lineName);
    void removeBusLine(const int lineId);
    void printBusLines() const;

    void addStop(const int stopId, const string stopName);
    void removeStop(const int stopId);
    void addStopToLine(const int stopId, const int lineId);
    void removeStopFromLine(const int stopId, const int lineId);
    void printStops(const int lineId) const;

    void assignBus(const int busId, const string driverName, const int lineId);
    void unassignBus(const int busId);
    void printBussesInLine(const int lineId) const;
    void printBussesPassingStop(const int stopId) const;

private:
    struct Stop;
    struct Bus;
    struct BusLine;
    
    struct StopNode {
        Stop* stop;
        StopNode* next;
        StopNode(Stop* s) : stop(s), next(nullptr) {}
    };
    
    struct BusNode {
        Bus* bus;
        BusNode* next;
        BusNode(Bus* b) : bus(b), next(nullptr) {}
    };
    
    struct BusLineNode {
        BusLine* line;
        BusLineNode* next;
        BusLineNode(BusLine* l) : line(l), next(nullptr) {}
    };
    
    struct Stop {
        int stopId;
        string stopName;
        Stop(int i, const string& n) : stopId(i), stopName(n) {}
    };
    
    struct Bus {
        int busId;
        std::string driverName;
        BusLine* assignedLine;
        Bus(int i, const string& d) : busId(i), driverName(d), assignedLine(nullptr) {}
    };
    
    struct BusLine {
        int lineId;
        string lineName;
        StopNode* stopsHead;
        BusNode* busesHead;
        BusLine(int i, const std::string& n) : lineId(i), lineName(n), stopsHead(nullptr), busesHead(nullptr) {}
        ~BusLine();
    };
    
    BusLineNode* busLinesHead;
    StopNode* stopsHead;
    BusNode* busesHead;
    
    BusLine* findBusLine(int lineId) const;
    Stop* findStop(int stopId) const;
    Bus* findBus(int busId) const;
    
    void insertBusLineSorted(BusLine* newLine);
    void insertStopSorted(StopNode*& head, Stop* stop);
    void insertBusSorted(BusNode*& head, Bus* bus);
    
    void removeBusLineNode(int lineId);
    void removeStopNode(int stopId);
    void removeBusNode(int busId);
    
    bool isStopUsedInAnyLine(int stopId) const;
};

#endif