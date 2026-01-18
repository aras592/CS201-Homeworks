//Aras Soylu, Section 1, 22401732
#include <iostream>
using namespace std;
#include "BilkentTourism.h"

BilkentTourism::BusLine::~BusLine() {
    StopNode* currentStop = stopsHead;
    while (currentStop) {
        StopNode* temp = currentStop;
        currentStop = currentStop->next;
        delete temp;
    }

    BusNode* currentBus = busesHead;
    while (currentBus) {
        BusNode* temp = currentBus;
        currentBus = currentBus->next;
        delete temp;
    }
}

BilkentTourism::BilkentTourism() {
    busLinesHead = nullptr;
    stopsHead = nullptr;
    busesHead = nullptr;
}

BilkentTourism::~BilkentTourism() {
    BusLineNode* currLine = busLinesHead;
    while (currLine) {
        BusLineNode* temp = currLine;
        currLine = currLine->next;
        delete temp->line;
        delete temp;
    }
    busLinesHead = nullptr;

    StopNode* currStop = stopsHead;
    while (currStop) {
        StopNode* temp = currStop;
        currStop = currStop->next;
        delete temp->stop;
        delete temp;
    }
    stopsHead = nullptr;

    BusNode* currBus = busesHead;
    while (currBus) {
        BusNode* temp = currBus;
        currBus = currBus->next;
        delete temp->bus;
        delete temp;
    }
    busesHead = nullptr;
}

BilkentTourism::BusLine* BilkentTourism::findBusLine(int lineID) const {
    BusLineNode* currentBusLine = busLinesHead;
    while (currentBusLine) {
        if (currentBusLine->line->lineId == lineID)
            return currentBusLine->line;
        currentBusLine = currentBusLine->next;
    }
    return nullptr;
}

BilkentTourism::Stop* BilkentTourism::findStop(int stopID) const {
    StopNode* currentStop = stopsHead;
    while (currentStop) {
        if (currentStop->stop->stopId == stopID)
            return currentStop->stop;
        currentStop = currentStop->next;
    }
    return nullptr;
}

BilkentTourism::Bus* BilkentTourism::findBus(int busID) const {
    BusNode* currentBus = busesHead;
    while (currentBus) {
        if (currentBus->bus->busId == busID)
            return currentBus->bus;
        currentBus = currentBus->next;
    }
    return nullptr;
}

void BilkentTourism::insertBusLineSorted(BusLine* newLine) {
    BusLineNode* newNode = new BusLineNode(newLine);

    if (busLinesHead == nullptr || busLinesHead->line->lineId > newLine->lineId) {
        newNode->next = busLinesHead;
        busLinesHead = newNode;
        return;
    }

    BusLineNode* current = busLinesHead;
    while (current->next != nullptr && current->next->line->lineId < newLine->lineId) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void BilkentTourism::insertStopSorted(StopNode*& head, Stop* stop) {
    StopNode* newNode = new StopNode(stop);

    if (head == nullptr || head->stop->stopId > stop->stopId) {
        newNode->next = head;
        head = newNode;
        return;
    }

    StopNode* current = head;
    while (current->next != nullptr && current->next->stop->stopId < stop->stopId) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void BilkentTourism::insertBusSorted(BusNode*& head, Bus* bus) {
    BusNode* newNode = new BusNode(bus);

    if (head == nullptr || head->bus->busId > bus->busId) {
        newNode->next = head;
        head = newNode;
        return;
    }

    BusNode* current = head;
    while (current->next != nullptr && current->next->bus->busId < bus->busId) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}
void BilkentTourism::removeBusLineNode(int lineID) {
    if (busLinesHead == nullptr)
        return;

    if (busLinesHead->line->lineId == lineID) {
        BusLineNode* temp = busLinesHead;
        busLinesHead = busLinesHead->next;
        delete temp->line;
        delete temp;
        return;
    }

    BusLineNode* current = busLinesHead;
    while (current->next != nullptr && current->next->line->lineId != lineID) {
        current = current->next;
    }

    if (current->next != nullptr) {
        BusLineNode* temp = current->next;
        current->next = temp->next;
        delete temp->line;
        delete temp;
    }
}

void BilkentTourism::removeStopNode(int stopID) {
    if (stopsHead == nullptr)
        return;

    if (stopsHead->stop->stopId == stopID) {
        StopNode* temp = stopsHead;
        stopsHead = stopsHead->next;
        delete temp->stop;
        delete temp;
        return;
    }

    StopNode* current = stopsHead;
    while (current->next != nullptr && current->next->stop->stopId != stopID) {
        current = current->next;
    }

    if (current->next != nullptr) {
        StopNode* temp = current->next;
        current->next = temp->next;
        delete temp->stop;
        delete temp;
    }
}

void BilkentTourism::removeBusNode(int busID) {
    if (busesHead == nullptr)
        return;

    if (busesHead->bus->busId == busID) {
        BusNode* temp = busesHead;
        busesHead = busesHead->next;
        delete temp->bus;
        delete temp;
        return;
    }

    BusNode* current = busesHead;
    while (current->next != nullptr && current->next->bus->busId != busID) {
        current = current->next;
    }

    if (current->next != nullptr) {
        BusNode* temp = current->next;
        current->next = temp->next;
        delete temp->bus;
        delete temp;
    }
}

bool BilkentTourism::isStopUsedInAnyLine(int stopID) const {
    BusLineNode* currentBusLine = busLinesHead;

    while (currentBusLine) {
        StopNode* currentStop = currentBusLine->line->stopsHead;
        while (currentStop) {
            if (currentStop->stop->stopId == stopID)
                return true;
            currentStop = currentStop->next;
        }
        currentBusLine = currentBusLine->next;
    }

    return false;
}

void BilkentTourism::addBusLine(const int lineID, const string lineName) {
    if (findBusLine(lineID)) {
        cout << "Cannot add line. There is already a bus line with ID " << lineID << "." << endl;
        return;
    }

    BusLine* newLine = new BusLine(lineID, lineName);
    insertBusLineSorted(newLine);

    cout << "Added bus line " << lineID << "." << endl;
}

void BilkentTourism::removeBusLine(const int lineID) {
    BusLine* lineToBeRemoved = findBusLine(lineID);
    if (!lineToBeRemoved) {
        cout << "Cannot remove bus line. There is no bus line with ID " << lineID << "." << endl;
        return;
    }

    BusNode* currentBus = lineToBeRemoved->busesHead;
    while (currentBus) {
        int bid = currentBus->bus->busId;
        currentBus = currentBus->next;
        removeBusNode(bid);
    }

    removeBusLineNode(lineID);
    cout << "Removed bus line " << lineID << "." << endl;
}

void BilkentTourism::printBusLines() const {
    if (busLinesHead == nullptr) {
        cout << "There are no bus lines to show." << endl;
        return;
    }

    cout << "Bus lines in the system:" << endl;
    BusLineNode* curr = busLinesHead;

    while (curr) {
        cout << "Line " << curr->line->lineId << " : " << curr->line->lineName << endl;
        curr = curr->next;
    }
}

void BilkentTourism::addStop(const int stopID, const string stopName) {
    if (findStop(stopID)) {
        cout << "Cannot add stop. BilkentTourism already contains stop " << stopID << "." << endl;
        return;
    }

    Stop* newStop = new Stop(stopID, stopName);
    insertStopSorted(stopsHead, newStop);
    cout << "Added stop " << stopID << "." << endl;
}

void BilkentTourism::removeStop(const int stopID) {
    Stop* stopToRemove = findStop(stopID);
    if (!stopToRemove) {
        cout << "Cannot remove stop " << stopID << ". There is no bus stop with ID " << stopID << "." << endl;
        return;
    }

    if (isStopUsedInAnyLine(stopID)) {
        cout << "Cannot remove stop " << stopID << ". The stop is currently in use." << endl;
        return;
    }

    removeStopNode(stopID);
    cout << "Removed stop " << stopID << "." << endl;
}

void BilkentTourism::addStopToLine(const int stopID, const int lineID) {
    if (!findStop(stopID)) {
        cout << "Cannot add stop. There is no stop with ID " << stopID << "." << endl;
        return;
    }
    if (!findBusLine(lineID)) {
        cout << "Cannot add stop. There is no line with ID " << lineID << "." << endl;
        return;
    }

    Stop* stop = findStop(stopID);
    BusLine* busLine = findBusLine(lineID);

    StopNode* currentStop = busLine->stopsHead;
    while (currentStop) {
        if (currentStop->stop->stopId == stopID) {
            cout << "Cannot add stop. Line " << lineID << " already contains stop " << stopID << "." << endl;
            return;
        }
        currentStop = currentStop->next;
    }

    insertStopSorted(busLine->stopsHead, stop);
    cout << "Added stop " << stopID << " to line " << lineID << " (" << busLine->lineName << ")." << endl;
}

void BilkentTourism::removeStopFromLine(const int stopID, const int lineID) {
    BusLine* busLine = findBusLine(lineID);
    if (!busLine) {
        cout << "Cannot remove stop. There is no line with ID " << lineID << "." << endl;
        return;
    }

    StopNode*& stopHead = busLine->stopsHead;
    if (!stopHead) {
        cout << "Cannot remove stop. Line " << lineID << " does not have stop " << stopID << "." << endl;
        return;
    }

    // remove head
    if (stopHead->stop->stopId == stopID) {
        StopNode* temp = stopHead;
        stopHead = stopHead->next;
        delete temp;
        cout << "Removed stop " << stopID << " from line " << lineID << "." << endl;
        return;
    }

    StopNode* currentStop = stopHead;
    while (currentStop->next && currentStop->next->stop->stopId != stopID) {
        currentStop = currentStop->next;
    }

    if (!currentStop->next) {
        cout << "Cannot remove stop. Line " << lineID << " does not have stop " << stopID << "." << endl;
        return;
    }

    StopNode* stopToRemove = currentStop->next;
    currentStop->next = currentStop->next->next;
    delete stopToRemove;

    cout << "Removed stop " << stopID << " from line " << lineID << "." << endl;
}

void BilkentTourism::printStops(const int lineID) const {
    BusLine* busLine = findBusLine(lineID);

    if (!busLine) {
        cout << "Cannot print stops. There is no line with ID " << lineID << "." << endl;
        return;
    }

    if (!busLine->stopsHead) {
        cout << "Cannot print stops. There is no stop to show." << endl;
        return;
    }

    StopNode* stop = busLine->stopsHead;
    cout << "Stops in bus line " << lineID << " (" << busLine->lineName << ") :" << endl;
    while (stop) {
        cout << "Stop " << stop->stop->stopId << " : " << stop->stop->stopName << endl;
        stop = stop->next;
    }
}

void BilkentTourism::assignBus(const int busID, const string driverName, const int lineID) {
    BusLine* busLine = findBusLine(lineID);
    if (!busLine) {
        cout << "Cannot assign bus. There is no line with ID " << lineID << "." << endl;
        return;
    }

    Bus* bus = findBus(busID);

    if (bus != nullptr && bus->assignedLine != nullptr) {
        cout << "Cannot assign bus. Bus " << busID << " is already assigned to a line." << endl;
        return;
    }

    if (bus == nullptr) {
        bus = new Bus(busID, driverName);
        insertBusSorted(busesHead, bus);
    } else {
        bus->driverName = driverName;
    }

    bus->assignedLine = busLine;
    insertBusSorted(busLine->busesHead, bus);

    cout << "Bus " << busID << " with driver " << driverName << " is assigned to line " << lineID
         << " (" << busLine->lineName << ")." << endl;
}

void BilkentTourism::unassignBus(const int busID) {
    Bus* busToUnassign = findBus(busID);
    if (!busToUnassign) {
        cout << "Cannot unassign bus. There is no bus with ID " << busID << "." <<endl;
        return;
    }

    BusLine* busLine = busToUnassign->assignedLine;
    if (busLine != nullptr) {
        BusNode*& busHead = busLine->busesHead;

        if (busHead && busHead->bus->busId == busID) {
            BusNode* temp = busHead;
            busHead = busHead->next;
            delete temp;
        } else if (busHead) {
            BusNode* currentBus = busHead;
            while (currentBus->next && currentBus->next->bus->busId != busID) {
                currentBus = currentBus->next;
            }
            if (currentBus->next) {
                BusNode* temp = currentBus->next;
                currentBus->next = temp->next;
                delete temp;
            }
        }
    }

    busToUnassign->assignedLine = nullptr;
    cout << "Bus " << busID << " is unassigned from line " << (busLine ? busLine->lineId : 0)
         << " (" << (busLine ? busLine->lineName : "") << ")." << endl;
}

void BilkentTourism::printBussesInLine(const int lineID) const {
    BusLine* busLine = findBusLine(lineID);

    if (busLine == nullptr) {
        cout << "Cannot print busses. There is no line with ID " << lineID << "." << endl;
        return;
    }

    if (busLine->busesHead == nullptr) {
        cout << "There are no bus to show in line " << lineID << " (" << busLine->lineName << ")." << endl;
        return;
    }

    BusNode* bus = busLine->busesHead;
    cout << "Busses and their drivers assigned to the line " << lineID << " (" << busLine->lineName << "):" << endl;
    while (bus) {
        cout << "Bus " << bus->bus->busId << " : " << bus->bus->driverName << endl;
        bus = bus->next;
    }
}

void BilkentTourism::printBussesPassingStop(const int stopID) const {
    Stop* stop = findStop(stopID);
    if (!stop) {
        cout << "Cannot print buses. There is no stop with ID " << stopID << "." << endl;
        return;
    }

    bool foundStop = false;
    BusLineNode* currentBusLine = busLinesHead;

    while (currentBusLine) {
        StopNode* currentStop = currentBusLine->line->stopsHead;
        while (currentStop) {
            if (currentStop->stop->stopId == stopID) {
                foundStop = true;
                break;
            }
            currentStop = currentStop->next;
        }
        if (foundStop)
            break;

        currentBusLine = currentBusLine->next;
    }

    if (!foundStop) {
        cout << "Cannot print buses. No lines pass through the stop." << endl;
        return;
    }

    cout << "Buses and their assigned lines passing the stop " << stopID << " (" << stop->stopName << "):" << endl;

    currentBusLine = busLinesHead;
    while (currentBusLine) {
        bool hasStop = false;
        StopNode* currentStop = currentBusLine->line->stopsHead;
        while (currentStop) {
            if (currentStop->stop->stopId == stopID) {
                hasStop = true;
                break;
            }
            currentStop = currentStop->next;
        }

        if (hasStop) {
            cout << "Line " << currentBusLine->line->lineId << " (" << currentBusLine->line->lineName << ") : ";

            BusNode* currentBus = currentBusLine->line->busesHead;
            if (!currentBus) {
                cout << "None" << endl;
            } else {
                cout << "[";
                bool firstOne = true;
                while (currentBus) {
                    if (!firstOne)
                        cout << ",";
                    cout << currentBus->bus->busId;
                    firstOne = false;
                    currentBus = currentBus->next;
                }
                cout << "]" << endl;
            }
        }
        currentBusLine = currentBusLine->next;
    }
}
