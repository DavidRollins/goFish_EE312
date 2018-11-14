// FILE: card_demo.cpp
// This is a small demonstration program showing how the Card and Deck classes are used.
// David Rollins, DER2366
// Thu Nov 8, 2018
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include "card.h"
#include "player.h"
#include "deck.h"


using namespace std;

void dealHand(Deck &d, Player &p, int numCards)
{
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}

// GameOver takes two players and a writeable file stream as inputs
// pre conditions : players are valid players and output stream is valid
// tests if the game is over, returns true when all 26 books are on the table

bool gameOver(const Player& player1, const Player& player2, ofstream& myFile) {

    if((player1.getBookSize() + player2.getBookSize()) >= 26) {
        if(player1.getHandSize() > player2.getHandSize()) {
           // cout << player1.getName() << " wins!";
            myFile << player1.getName() << " wins!";
        } else {
           // cout << player2.getName() << " wins!";
            myFile << player2.getName() << " wins!";
        }
        return true;
    } else {
        return false;
    }
}

// handToBook takes a player and output stream
// preconditions: valid player and output stream
// handToBook removes the book from a player's hand and puts it in their book pile.
void handToBook(Player& player, ofstream& myFile) {

    Card bookCard1;
    Card bookCard2;
    int rank;

    while (player.checkHandForBook(bookCard1, bookCard2)) {

        player.removeCardFromHand(bookCard1);
        player.removeCardFromHand(bookCard2);
        player.bookCards(bookCard1, bookCard2);
        rank = bookCard1.getRank();

        myFile << player.getName() << " books the " << bookCard1.rankString(rank) << endl;


    } // end loop (looking for books in hand)
}

// takeCard takes a player, deck, and output stream as inputs
// preconditions: valid player, deck, and output stream
// player draws a card from the deck provided the deck is not empty and adds it to their hand
void takeCard(Player& player, Deck& deck, ofstream& myFile) {
    if(deck.size() > 0) { // grab a card if deck is not empty

        Card newCardFromDeck = deck.dealCard();
    //    cout << player.getName() << " draws " << newCardFromDeck << endl;
        myFile << player.getName() << " draws " << newCardFromDeck << endl;
        player.addCard(newCardFromDeck);

    } else {
    //    cout << "There are no cards left in the deck!" << endl;
        myFile << "There are no cards left in the deck!" << endl;
    }
}

// askForCard takes two players, the query card, and an output stream as the inputs
// preconditions: valid inputs
// askForCard will continuously ask for a card as the player continues to ask for cards that the other player has
// main driver for game essentially... if wanting to change rules: come here.
void askForCard(Player& player, Player& otherPlayer, Card questionCard, ofstream& myFile) {

    bool fish = false;
    int rank = questionCard.getRank();

    while(!fish) {


        myFile << player.getName() << " ask, 'Do you have a " << questionCard.rankString(rank) << "?'" << endl;
        if(otherPlayer.cardInHand(questionCard)) {


            myFile << otherPlayer.getName() << " says, 'Yes, I have a " << questionCard.rankString(rank) << ".'" << endl;
            // hand card to player who asked
            player.addCard(otherPlayer.removeCardFromHand(questionCard));

            // player will check for books
            handToBook(player, myFile);

            // after booking cards, check if the game is over.
            if(gameOver(player, otherPlayer, myFile))
                return;

        } else {

            fish = true;
      //      cout << otherPlayer.getName() << " says - Go Fish" << endl;
            myFile << otherPlayer.getName() << " says - Go Fish" << endl;

        }
    }
}

// takeTurn takes the two players, deck, and output stream as inputs
// Preconditions: valid inputs
// puts all the components together... if all hands are booked then game is over,
// if someone takes their turn, then take a card from the deck.
void takeTurn(Player& player, Player& otherPlayer, Deck& deck, ofstream& myFile) {

    handToBook(player, myFile);
    if(gameOver(player, otherPlayer, myFile))
        return;

    if(player.getHandSize() > 0) {
        Card questionCard = player.chooseCardFromHand();
        askForCard(player, otherPlayer, questionCard, myFile);
    }

    takeCard(player, deck, myFile);
}

int main () {
    ofstream myFile;
    myFile.open("gofish_results.txt");
   // Card c(5, (Card::Suit)2);
    //cout << c << endl;
    int numTurns = 0;
    int numCards = 7;
    Deck deck;
    deck.shuffle();
   // Player player1("Joe");
   // dealHand(deck, player1, numCards);
   // cout << player1.showBooks() << endl;
   // cout << player1.showHand() << endl;


    Player player1("Joe");
    Player player2("Jane");

//    Deck deck;
    deck.shuffle();

    dealHand(deck, player1, numCards);
    dealHand(deck, player2, numCards);
    cout << "Joe's Hand: " << player1.showHand() << "\n" << endl;
    cout << "Jane's Hand: " << player2.showHand() << "\n" << endl;

    myFile << "Joe's Hand: " << player1.showHand() << endl;
    myFile << "Jane's Hand: " << player2.showHand() << "\n\n" << endl;


    while (!gameOver(player1, player2, myFile)) {
        //cout << "Here" << endl;


        takeTurn(player1, player2, deck, myFile);
        takeTurn(player2, player1, deck, myFile);




       // numTurns++;
        //cout << numTurns << endl;


    }
    cout << "Game ended" << endl;


}
