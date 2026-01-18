//Aras Soylu, Section 1, 22401732
#ifndef MagicCard_H
#define MagicCard_H
#include <string>
using namespace std;

class MagicCard {
private:
    struct Player{
        int ID;
        string name;
        string* playerCards;
        int numOfCardsInDeck;
    };

    
    Player* playerArr;     
    int numOfCurrentPlayers;

    string* discardPile;
    int sizeOfDiscardPile;

    string* drawPile;
    int sizeOfDrawPile;

    int findPlayerIndex(int playerID) const;

    void updatePlayerNumber();
    void updateDrawPile();
    void updateDiscardPile();

    void addCardToPlayer(const int playerID, string card);
    void removeCardFromPlayer(const int playerID, string card);
    void drawCardWhilePlaying(const int PlayerID, int index);

    bool isValidCard(const int playerID, const string card);
    bool hasWon(const int playerID);


public:
    MagicCard();
    ~MagicCard();

    void addPlayer( const int playerID, const string name);
    void removePlayer ( const int PlayerID);
    void printPlayers () const;

    void setDrawPile ( const string drawPile[], const int size);
    void drawCardFromDeck( const int PlayerID, const int n);
    void switchHands( const int player1ID, const int player2ID);
    void listDrawPile() const;
    void listDiscardPile() const;
    void listCardsOfPlayer( const int playerID) const;
    
    void play( const int playerID, const string card);
    
};

#endif
