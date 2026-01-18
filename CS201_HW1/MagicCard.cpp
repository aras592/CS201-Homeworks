//Aras Soylu, Section 1, 22401732
#include <iostream>
using namespace std;
#include "MagicCard.h"

MagicCard :: MagicCard( ) {
    playerArr = nullptr;
    numOfCurrentPlayers = 0;

    discardPile = nullptr;
    sizeOfDiscardPile = 0;

    drawPile = nullptr;
    sizeOfDrawPile = 0;
}

MagicCard :: ~MagicCard() {
    for( int  i = 0; i < numOfCurrentPlayers; i++)
    {
        delete[] playerArr[i].playerCards;
    }
    delete[] playerArr;
    delete[] drawPile;
    delete[] discardPile;
}

int MagicCard :: findPlayerIndex(int playerID) const{
    for(int i = 0; i < numOfCurrentPlayers; i++){
        if(playerArr[i].ID == playerID){
            return i;
        }
    }
    return -1;
}

void MagicCard::addPlayer(const int playerID, const string name) {
    if (findPlayerIndex(playerID) == -1) {
        Player* newPlayers = new Player[numOfCurrentPlayers + 1];
    
        for (int i = 0; i < numOfCurrentPlayers; i++) {
            newPlayers[i] = playerArr[i];
        }
    
        newPlayers[numOfCurrentPlayers].ID = playerID;
        newPlayers[numOfCurrentPlayers].name = name;
        newPlayers[numOfCurrentPlayers].playerCards = nullptr;
        newPlayers[numOfCurrentPlayers].numOfCardsInDeck = 0;
    
        delete[] playerArr;
        playerArr = newPlayers;
        numOfCurrentPlayers++;
    
        cout << "Added player " << name << " with ID " << playerID << "." << ::endl;
        return;
    }
    else {
        cout << "Cannot add player. ID " << playerID << " already exists." << endl;
        return;
    }
    
}

void MagicCard :: removePlayer(const int playerID){
    if(findPlayerIndex(playerID) == -1){
        cout << "Cannot remove player. There is no player with ID " << playerID << "." <<endl;
        return;
    }

    delete[] playerArr[findPlayerIndex(playerID)].playerCards;
    Player* newPlayers = new Player[numOfCurrentPlayers-1];
    
    for(int i = 0; i<findPlayerIndex(playerID); i++){
        newPlayers[i] = playerArr[i];
    }

    for(int i = findPlayerIndex(playerID); i < numOfCurrentPlayers - 1; i++){
        newPlayers[i] = playerArr[i+1];
    }

    delete[] playerArr;
    playerArr = newPlayers;
    numOfCurrentPlayers--;

    cout << "Removed player " << playerID  << "." <<endl;
}

void MagicCard :: printPlayers() const {
    if(numOfCurrentPlayers == 0){
        cout << "Cannot print players. There is no player in the game." << endl;
        return;
    }

    Player* listedPlayerList = new Player[numOfCurrentPlayers];
    for(int i = 0; i < numOfCurrentPlayers ; i++){
        listedPlayerList[i] = playerArr[i];
    }

    Player temp;

    for(int i = 0; i < numOfCurrentPlayers -1 ; i++){
        for(int j = i+1; j < numOfCurrentPlayers ; j++){
            if(listedPlayerList[j].ID < listedPlayerList[i].ID){
                temp = listedPlayerList[i];
                listedPlayerList[i] = listedPlayerList[j];
                listedPlayerList[j] = temp;
            }
        }
    }

    cout << "Players :" << endl;
    for(int i = 0; i < numOfCurrentPlayers ; i++){
        cout << "Player " << listedPlayerList[i].ID << " : " << listedPlayerList[i].name << endl;
    }

    delete[] listedPlayerList;
}

void MagicCard :: setDrawPile(const string DrawPile[] , const int size){
    if(drawPile != nullptr){
        delete[] drawPile;
        drawPile = nullptr;
    }

    drawPile = new string[size];

    for(int i = 0; i < size; i++){
        drawPile[i] = DrawPile[i];
    }
    sizeOfDrawPile = size;

    cout << "Draw pile has been initialized." << endl;
}

void MagicCard :: addCardToPlayer(const int playerID, string card){
    int index = findPlayerIndex(playerID);

    string* updatedDeck = new string[playerArr[index].numOfCardsInDeck+1];

    for(int i = 0; i < playerArr[index].numOfCardsInDeck; i++){
        updatedDeck[i] = playerArr[index].playerCards[i];
    }
    updatedDeck[playerArr[index].numOfCardsInDeck] = card;

    delete[] playerArr[index].playerCards;
    playerArr[index].playerCards = updatedDeck;
    playerArr[index].numOfCardsInDeck++;
}

void MagicCard :: removeCardFromPlayer(const int playerID, string card){
    if(findPlayerIndex(playerID) == -1) return;

    int indexOfCard = -1;
    for(int i = 0; i < playerArr[findPlayerIndex(playerID)].numOfCardsInDeck; i++){
        if(playerArr[findPlayerIndex(playerID)].playerCards[i] == card){
            indexOfCard = i;
        }
    }

    if(indexOfCard == -1) return;

    string* updatedPlayerHand = new string[playerArr[findPlayerIndex(playerID)].numOfCardsInDeck-1];
    for(int i = 0; i < indexOfCard; i++){
        updatedPlayerHand[i] = playerArr[findPlayerIndex(playerID)].playerCards[i];
    }
    for(int i = indexOfCard; i<playerArr[findPlayerIndex(playerID)].numOfCardsInDeck-1; i++){
        updatedPlayerHand[i] = playerArr[findPlayerIndex(playerID)].playerCards[i+1];
    }

    delete[] playerArr[findPlayerIndex(playerID)].playerCards;
    playerArr[findPlayerIndex(playerID)].playerCards = updatedPlayerHand;
    playerArr[findPlayerIndex(playerID)].numOfCardsInDeck--;

    string* updatedDiscardPile = new string[sizeOfDiscardPile+1];

    for(int i = 0; i < sizeOfDiscardPile; i++){
        updatedDiscardPile[i] = discardPile[i];
    }
    updatedDiscardPile[sizeOfDiscardPile] = card;

    delete[] discardPile;
    discardPile = updatedDiscardPile;
    sizeOfDiscardPile++;
}

void MagicCard :: drawCardFromDeck(const int playerID, const int n){
    if( n < 0 || n >= sizeOfDrawPile){
        cout << "Cannot draw card. The input index is not valid." << endl;
        return;
    }

    string drawnCard = drawPile[n];
    addCardToPlayer(playerID, drawnCard);

    string* updatedDrawPile = new string[sizeOfDrawPile-1];
    int index = 0;
    for(int i = 0; i < sizeOfDrawPile; i++){
        if(i != n){
            updatedDrawPile[index] = drawPile[i];
            index++;
        }
    }
    
    delete[] drawPile;
    drawPile = updatedDrawPile;
    sizeOfDrawPile--;

    cout << playerArr[findPlayerIndex(playerID)].name << " drew card " << drawnCard << " from the draw pile." << endl;
}

void MagicCard :: switchHands(const int player1ID, const int player2ID){
    if(findPlayerIndex(player1ID) == -1 || findPlayerIndex(player2ID) == -1 ){
        cout << "Cannot switch hands. One or both players do not exist." << endl;
        return;
    }

    Player temp;
    temp = playerArr[findPlayerIndex(player1ID)];
    playerArr[findPlayerIndex(player1ID)].playerCards = playerArr[findPlayerIndex(player2ID)].playerCards;
    playerArr[findPlayerIndex(player2ID)].playerCards = temp.playerCards;

    cout << "Switched hands between " << playerArr[findPlayerIndex(player1ID)].name << " and " << playerArr[findPlayerIndex(player2ID)].name << "." <<endl;
}

void MagicCard :: listDrawPile() const {
    if(sizeOfDrawPile == 0){
        cout << "Draw pile is empty." << endl;
        return;
    }

    cout << "Draw pile: [" ;
    int n = sizeOfDrawPile-1;
    for(int i = 0; i < sizeOfDrawPile; i++){
        if(n!=i){
            cout << drawPile[i] << ", ";
        }
        else{
            cout << drawPile[i];
        }
    }
    cout << "]" << endl;
}

void MagicCard :: listDiscardPile() const {
    if(sizeOfDiscardPile == 0){
        cout << "Discard pile is empty." << endl;
        return;
    }

    cout << "Discard pile: [";
    int n = sizeOfDiscardPile-1;
    for(int i = 0; i < sizeOfDiscardPile; i++){
        if(n!=i){
            cout << discardPile[i] << ", ";
        }
        else{
            cout << discardPile[i];
        }
    }
    cout << "]" << endl;
}

void MagicCard :: listCardsOfPlayer(const int playerID) const{
    if(findPlayerIndex(playerID) == -1){
        cout << "Cannot list cards. Player with ID " << playerID << " does not exist." << endl;
        return;
    }
    
    cout << "Cards of " << playerArr[findPlayerIndex(playerID)].name << ": [";
    for(int i = 0; i < playerArr[findPlayerIndex(playerID)].numOfCardsInDeck; i++){
        if(i != playerArr[findPlayerIndex(playerID)].numOfCardsInDeck-1){
            cout << playerArr[findPlayerIndex(playerID)].playerCards[i] << ", " ;
        }
        else{
            cout << playerArr[findPlayerIndex(playerID)].playerCards[i] ;
        }
    } 
    cout << "]" << endl;
}

void MagicCard::drawCardWhilePlaying(const int playerID, int n){
   
    string drawnCard = drawPile[n];
    addCardToPlayer(playerID, drawnCard);

    string* updatedDrawPile = new string[sizeOfDrawPile-1];

    int index = 0;
    for(int i = 0; i < sizeOfDrawPile; i++){
        if(i != n){
            updatedDrawPile[index] = drawPile[i];
            index++;
        }
    }
    
    delete[] drawPile;
    drawPile = updatedDrawPile;
    sizeOfDrawPile--;
}

bool MagicCard :: isValidCard(const int playerID, const string card){
    if(sizeOfDiscardPile == 0){
        return true;
    }

    string colorOfCard = card.substr(0,1);
    string numberOfCard = card.substr(1);

        if(discardPile[sizeOfDiscardPile-1].substr(0,1) == colorOfCard || 
    discardPile[sizeOfDiscardPile-1].substr(1) == numberOfCard)
            return true;
    

    return false;
}

bool MagicCard :: hasWon(const int playerID){
    if(playerArr[findPlayerIndex(playerID)].numOfCardsInDeck == 0){
        return true;
    }
    else{
        return false;
    }
}

void MagicCard :: play(const int playerID, const string card){
    if(findPlayerIndex(playerID) == -1){
        cout << "There is no player with ID " << playerID << "." <<endl;
        return;
    }

    bool hasCard = false;
    for(int i = 0; i<playerArr[findPlayerIndex(playerID)].numOfCardsInDeck; i++){
        if(playerArr[findPlayerIndex(playerID)].playerCards[i] == card){
            hasCard = true;
        }
    }

    if(!hasCard){
        cout << "The player does not have " << card << " card." << endl;
        return;
    }

    if(sizeOfDrawPile == 0){
        cout << "The game has ended. No cards remain in the draw pile." << endl;
        return;
    }

    if(hasWon(playerID)){
        cout << "The game has ended. Player " << playerID << " won." << endl;
        return;
    }

    if(isValidCard(playerID, card)){
        cout << "Player " << playerID << " played " << card << "."<<endl;
        removeCardFromPlayer(playerID, card);

        if(hasWon(playerID)){
            cout << "The game has ended. Player " << playerID << " won." << endl;
            return;
        }
    }
    else{
        string cardToDraw = drawPile[0];

        drawCardWhilePlaying(playerID, 0);
        removeCardFromPlayer(playerID, card);

        
        cout << "Player " << playerID << " played " << card << " then drew " << cardToDraw << "." <<endl;

        if(sizeOfDrawPile == 0){
            cout << "The game has ended. No cards remain in the draw pile." << endl;
            return;
        }
    }
}

