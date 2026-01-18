// Aras Soylu, Section 2, 22401732
#ifndef TIMETRAVELENGINE_H
#define TIMETRAVELENGINE_H

#include <iostream>
#include <string>
using namespace std;

class TimeBranch {
private:
    int branchId;
    string currentLocation;

    class Stack {
    private:
        string* data;
        int capacity;
        int topIndex;
        bool unlimited;

        void resize(int newCap);

    public:
        Stack(int cap = 10, bool isUnlimited = false);
        Stack(const Stack& other);
        Stack& operator=(const Stack& other);
        ~Stack();

        bool push(const string& item);
        string pop();
        string peek() const;

        bool isEmpty() const;
        bool isFull() const;          
        int size() const;
        int getCapacity() const;

        void clear();
        string getElementAt(int index) const;

        bool contains(const string& item) const;
        int findPositionFromTop(const string& item) const;
    };

    Stack past;
    Stack future;
    Stack timeStones; 

public:
    TimeBranch(int id, int pastCap, int futureCap, const string& startLocation);

    int getBranchId() const { return branchId; }
    string getCurrentLocation() const { return currentLocation; }

    int fastForward(int k);
    int rewind(int k);      
    bool travelTo(const string& newLocation);

    void placeTimeStone();
    int activateTimeStone(); 

    void printTimeBranch() const;

    int getPastCapacity() const { return past.getCapacity(); }
    int getFutureCapacity() const { return future.getCapacity(); }

    void appendPast(const Stack& otherPast);
    void appendFuture(const Stack& otherFuture);
    void appendTimeStones(const Stack& otherStones);

    const Stack& getPast() const { return past; }
    const Stack& getFuture() const { return future; }
    const Stack& getTimeStones() const { return timeStones; }
};

class TimeTravelEngine {
private:
    struct BranchNode {
        TimeBranch* branch;
        BranchNode* next;
        BranchNode(TimeBranch* b) : branch(b), next(nullptr) {}
    };

    BranchNode* head;
    int branchCount;

    TimeBranch* findBranch(int branchId) const;

    bool removeBranch(int branchId, bool verbose);

public:
    TimeTravelEngine();
    ~TimeTravelEngine();

    int createTimeBranch(const int pastCapacity, const int futureCapacity,
                         const string startLocation, const int branchId);

    void deleteTimeBranch(const int branchId);
    void printAllBranches() const;

    void travelTo(const int branchId, const string newLocation);
    void fastForward(const int branchId, const int k);
    void rewind(const int branchId, const int k);

    void placeTimeStone(const int branchId);
    void activateTimeStone(const int branchId);

    void printTimeBranch(const int branchId) const;

    int mergeBranches(const int branchId1, 
                        const int branchId2, 
                        const int newBranchId);
};

#endif
