// Aras Soylu, Section 2, 22401732
#include "TimeTravelEngine.h"
#include <iostream>
#include <string>
using namespace std;

TimeBranch::Stack::Stack(int cap, bool isUnlimited)
    : data(nullptr), capacity(cap), topIndex(-1), unlimited(isUnlimited) {
    if (capacity < 0) capacity = 0;
    if (capacity > 0) data = new string[capacity];
}

TimeBranch::Stack::Stack(const Stack& other)
    : data(nullptr), capacity(other.capacity), topIndex(other.topIndex), unlimited(other.unlimited) {
    if (capacity > 0) {
        data = new string[capacity];
        for (int i = 0; i <= topIndex; i++) data[i] = other.data[i];
    }
}

TimeBranch::Stack& TimeBranch::Stack::operator=(const Stack& other) {
    if (this == &other) return *this;

    delete[] data;
    data = nullptr;

    capacity = other.capacity;
    topIndex = other.topIndex;
    unlimited = other.unlimited;

    if (capacity > 0) {
        data = new string[capacity];
        for (int i = 0; i <= topIndex; i++) data[i] = other.data[i];
    }
    return *this;
}

TimeBranch::Stack::~Stack() {
    delete[] data;
}

void TimeBranch::Stack::resize(int newCap) {
    if (newCap <= capacity) return;
    string* newData = new string[newCap];
    for (int i = 0; i <= topIndex; i++) newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCap;
}

bool TimeBranch::Stack::isEmpty() const {
    return topIndex == -1;
}

bool TimeBranch::Stack::isFull() const {
    return topIndex == capacity - 1;
}

int TimeBranch::Stack::size() const {
    return topIndex + 1;
}

int TimeBranch::Stack::getCapacity() const {
    return capacity;
}

bool TimeBranch::Stack::push(const string& item) {
    if (isFull()) {
        if (!unlimited) return false;
        int newCap = (capacity == 0) ? 1 : capacity * 2;
        resize(newCap);
    }
    data[++topIndex] = item;
    return true;
}

string TimeBranch::Stack::pop() {
    if (isEmpty()) return "";
    return data[topIndex--];
}

string TimeBranch::Stack::peek() const {
    if (isEmpty()) return "";
    return data[topIndex];
}

void TimeBranch::Stack::clear() {
    topIndex = -1;
}

string TimeBranch::Stack::getElementAt(int index) const {
    if (index < 0 || index > topIndex) return "";
    return data[index];
}

bool TimeBranch::Stack::contains(const string& item) const {
    for (int i = 0; i <= topIndex; i++) {
        if (data[i] == item) return true;
    }
    return false;
}

int TimeBranch::Stack::findPositionFromTop(const string& item) const {
    for (int i = topIndex; i >= 0; i--) {
        if (data[i] == item) return topIndex - i; 
    }
    return -1;
}

TimeBranch::TimeBranch(int id, int pastCap, int futureCap, const string& startLocation)
    : branchId(id),
      currentLocation(startLocation),
      past(pastCap, false),
      future(futureCap, false),
      timeStones(0, true)
    {
}

int TimeBranch::fastForward(int k) {
    if (k <= 0) return 0;

    int availableSteps = (k < future.size()) ? k : future.size();
    if (availableSteps == 0) return 0;

    if (past.size() + availableSteps > past.getCapacity()) return -1;

    for (int i = 0; i < availableSteps; i++) {
        past.push(currentLocation);
        currentLocation = future.pop();
    }
    return availableSteps;
}

int TimeBranch::rewind(int k) {
    if (k <= 0) return 0;

    int availableSteps = (k < past.size()) ? k : past.size();
    if (availableSteps == 0) return 0;

    if (future.size() + availableSteps > future.getCapacity()) {
        return -1;
    }

    for (int i = 0; i < availableSteps; i++) {
        future.push(currentLocation);

        currentLocation = past.pop();
    }

    return availableSteps;
}



bool TimeBranch::travelTo(const string& newLocation) {
    if (past.isFull()) return false;
    past.push(currentLocation);
    currentLocation = newLocation;
    future.clear();
    return true;
}

void TimeBranch::placeTimeStone() {
    timeStones.push(currentLocation);
}

int TimeBranch::activateTimeStone() {
    if (timeStones.isEmpty()) return 1;

    string target = timeStones.peek();

    if (currentLocation == target) {
        timeStones.pop();
        future.clear();
        return 0;
    }

    bool inPast = past.contains(target);
    bool inFuture = future.contains(target);

    if (!inPast && !inFuture) {
        timeStones.pop();
        return 2; 
    }

    if (inPast) {
        int stepsNeeded = past.findPositionFromTop(target) + 1;
        int r = rewind(stepsNeeded);
        timeStones.pop();

        if (r >= 0) {
            future.clear();        
            return 0;
    }
    return 3;

    }

    int stepsNeeded = future.findPositionFromTop(target) + 1;
    if (past.size() + stepsNeeded > past.getCapacity()) {
        timeStones.pop();
        return 3;
    }

    int f = fastForward(stepsNeeded);
    timeStones.pop();

    if (f >= 0) {
        future.clear();          
        return 0;
    }
    return 3;
    }

void TimeBranch::printTimeBranch() const {
    cout << "Past   : [";
    if (past.size() == 0) {
        cout << "  ]" << endl;
    } else {
        cout << " ";
        for (int i = 0; i < past.size(); i++) {
            cout << past.getElementAt(i);
            if (i < past.size() - 1) cout << ", ";
            else cout << " ]" << endl;
        }
    }

    cout << "Current: ( " << currentLocation << " )" << endl;

    cout << "Future : [";
    if (future.size() == 0) {
        cout << "  ]" << endl;
    } else {
        cout << " ";
        for (int i = 0; i < future.size(); i++) {
            cout << future.getElementAt(i);
            if (i < future.size() - 1) cout << ", ";
            else cout << " ]" << endl;
        }
    }


    cout << "Stones : [";
    if (timeStones.size() == 0) {
        cout << "  ]" << endl;
    } else {
        cout << " ";
        for (int i = 0; i < timeStones.size(); i++) {
            cout << timeStones.getElementAt(i);
            if (i < timeStones.size() - 1) cout << ", ";
            else cout << " ]" << endl;
        }
    }
}


void TimeBranch::appendPast(const Stack& otherPast) {
    for (int i = 0; i < otherPast.size(); i++) past.push(otherPast.getElementAt(i));
}

void TimeBranch::appendFuture(const Stack& otherFuture) {
    for (int i = 0; i < otherFuture.size(); i++) future.push(otherFuture.getElementAt(i));
}

void TimeBranch::appendTimeStones(const Stack& otherStones) {
    for (int i = 0; i < otherStones.size(); i++) timeStones.push(otherStones.getElementAt(i));
}

TimeTravelEngine::TimeTravelEngine() : head(nullptr), branchCount(0) {}

TimeTravelEngine::~TimeTravelEngine() {
    BranchNode* cur = head;
    while (cur != nullptr) {
        BranchNode* nxt = cur->next;
        delete cur->branch;
        delete cur;
        cur = nxt;
    }
}

TimeBranch* TimeTravelEngine::findBranch(int branchId) const {
    BranchNode* cur = head;
    while (cur != nullptr) {
        if (cur->branch->getBranchId() == branchId) return cur->branch;
        cur = cur->next;
    }
    return nullptr;
}

bool TimeTravelEngine::removeBranch(int branchId, bool verbose) {
    BranchNode* cur = head;
    BranchNode* prev = nullptr;

    while (cur != nullptr) {
        if (cur->branch->getBranchId() == branchId) {
            if (prev == nullptr) head = cur->next;
            else prev->next = cur->next;

            delete cur->branch;
            delete cur;
            branchCount--;

            if (verbose) cout << "Deleted time branch " << branchId << "." << endl;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }

    if (verbose) cout << "Cannot delete branch. There is no branch with ID " << branchId << "." << endl;
    return false;
}

int TimeTravelEngine::createTimeBranch(int pastCapacity, int futureCapacity,
                                      string startLocation, int branchId) {
    if (findBranch(branchId) != nullptr) {
        cout << "Cannot create time branch. A branch with ID " << branchId << " already exists." << endl;
        return -1;
    }

    TimeBranch* b = new TimeBranch(branchId, pastCapacity, futureCapacity, startLocation);
    BranchNode* n = new BranchNode(b);
    n->next = head;
    head = n;
    branchCount++;

    cout << "Created time branch with ID " << branchId << "." << endl;
    return branchId;
}

void TimeTravelEngine::deleteTimeBranch(int branchId) {
    removeBranch(branchId, true);
}

void TimeTravelEngine::travelTo(const int branchId, const string newLocation) {
    TimeBranch* b = findBranch(branchId);
    if (b == nullptr) {
        cout << "Cannot travel. There is no branch with ID " << branchId << "." << endl;
        return;
    }

    if (b->travelTo(newLocation)) {
        cout << "Traveled to " << newLocation << " in branch " << branchId << "." << endl;
    } else {
        cout << "Cannot travel to " << newLocation << " in branch " << branchId
             << ". Past stack capacity exceeded." << endl;
    }
}

void TimeTravelEngine::fastForward(int branchId, int k) {
    TimeBranch* b = findBranch(branchId);
    if (b == nullptr) return;

    int steps = b->fastForward(k);

    if (steps >= 0) {
        cout << "Fast forwarded " << steps << " steps in branch " << branchId << "." << endl;
    } else {
        int m = k;
        int futureCnt = b->getFuture().size();
        if (m > futureCnt) m = futureCnt;

        cout << "Cannot fast forward " << m << " steps in branch " << branchId
             << ". Past stack capacity exceeded." << endl;
    }
}


void TimeTravelEngine::rewind(int branchId, int k) {
    TimeBranch* b = findBranch(branchId);
    if (b == nullptr) return;

    int steps = b->rewind(k);

    if (steps >= 0) {
        cout << "Rewound " << steps << " steps in branch " << branchId << "." << endl;
    } else {
        int m = k;
        int pastCnt = b->getPast().size();
        if (m > pastCnt) m = pastCnt;

        cout << "Cannot rewind " << m << " steps in branch " << branchId
             << ". Future stack capacity exceeded." << endl;
    }
}



void TimeTravelEngine::placeTimeStone(int branchId) {
    TimeBranch* b = findBranch(branchId);
    if (b == nullptr) return;

    b->placeTimeStone();
    cout << "Time stone placed at " << b->getCurrentLocation() << "." << endl;
}

void TimeTravelEngine::activateTimeStone(int branchId) {
    TimeBranch* b = findBranch(branchId);
    if (b == nullptr) return;

    int res = b->activateTimeStone();
    if (res == 0) {
        cout << "Time stone activated. The traveler is now at " << b->getCurrentLocation() << "." << endl;
    } else if (res == 1) {
        cout << "Cannot activate time stone. No time stones available." << endl;
    } else if (res == 2) {
        cout << "Time stone discarded. The recorded moment is no longer reachable." << endl;
    } else {
        cout << "Time stone discarded. Past stack capacity exceeded." << endl;
    }
}

void TimeTravelEngine::printTimeBranch(int branchId) const {
    TimeBranch* b = findBranch(branchId);
    if (b == nullptr) return;
    b->printTimeBranch();
}

void TimeTravelEngine::printAllBranches() const {
    int actualCount = 0;
    for (BranchNode* cur = head; cur != nullptr; cur = cur->next) actualCount++;

    if (actualCount == 0) {
        cout << "There are no time branches to show." << endl;
        return;
    }

    TimeBranch** branches = new TimeBranch*[actualCount];
    BranchNode* current = head;
    for (int i = 0; i < actualCount; i++) {
        branches[i] = current->branch;
        current = current->next;
    }

    for (int i = 0; i < actualCount - 1; i++) {
        for (int j = 0; j < actualCount - i - 1; j++) {
            if (branches[j]->getBranchId() > branches[j + 1]->getBranchId()) {
                TimeBranch* tmp = branches[j];
                branches[j] = branches[j + 1];
                branches[j + 1] = tmp;
            }
        }
    }

    cout << "Time branches in the system:" << endl;
    for (int i = 0; i < actualCount; i++) {
        cout << "Branch " << branches[i]->getBranchId() << ":" << endl;
        branches[i]->printTimeBranch();
        if (i != actualCount - 1) cout << endl;
    }

    delete[] branches;
}

int TimeTravelEngine::mergeBranches(int branchId1, int branchId2, int newBranchId) {
    TimeBranch* b1 = findBranch(branchId1);
    TimeBranch* b2 = findBranch(branchId2);

    if (b1 == nullptr || b2 == nullptr) {
        cout << "Cannot merge branches. Missing branch IDs." << endl;
        return -1;
    }

    if (findBranch(newBranchId) != nullptr) {
        cout << "Cannot merge branches. A branch with ID " << newBranchId << " already exists." << endl;
        return -1;
    }

    if (b1->getCurrentLocation() != b2->getCurrentLocation()) {
        cout << "Cannot merge branches. Current locations do not match." << endl;
        return -1;
    }

    int newPastCap = b1->getPastCapacity() + b2->getPastCapacity();
    int newFutureCap = b1->getFutureCapacity() + b2->getFutureCapacity();
    string commonLoc = b1->getCurrentLocation();

    TimeBranch* merged = new TimeBranch(newBranchId, newPastCap, newFutureCap, commonLoc);

    merged->appendPast(b1->getPast());
    merged->appendPast(b2->getPast());
    merged->appendFuture(b1->getFuture());
    merged->appendFuture(b2->getFuture());
    merged->appendTimeStones(b1->getTimeStones());
    merged->appendTimeStones(b2->getTimeStones());

    removeBranch(branchId1, false);
    removeBranch(branchId2, false);

    BranchNode* node = new BranchNode(merged);
    node->next = head;
    head = node;
    branchCount++;

    cout << "Time branches " << branchId1 << " and " << branchId2
         << " merged into new branch " << newBranchId << "." << endl;

    return newBranchId;
}
