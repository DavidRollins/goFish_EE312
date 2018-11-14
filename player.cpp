
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <map>
#include "card.h"
#include "player.h"
#include "deck.h"
// David Rollins, DER2366
// Thu Nov 8, 2018
using namespace std;


template<class InputIterator, class T>
  InputIterator find (InputIterator first, InputIterator last, const T& val)
{
  while (first!=last) {
    if (*first==val) return first;
    ++first;
  }
  return last;
}

Card Player::takeCard(Card &c) {
    vector<Card>::iterator it = find( myHand.begin(), myHand.end(), c );
    swap( ( *it ), myHand.back() );
    Card d = myHand.back();
    myHand.pop_back();
    //hasCards();
    //sort( myHand.begin(), myHand.end() );
    return d;
}


void Player::addCard(Card c){
    myHand.push_back( c );
}  //adds a card to the hand

void Player::bookCards(Card c1, Card c2){
    if(c1.getRank() == c2.getRank())
    {
        myBook.push_back(c1);
        myBook.push_back(c2);
    }
}

//OPTIONAL
// comment out if you decide to not use it
//this function will check a players hand for a pair.
//If a pair is found, it returns true and populates the two variables with the cards tha make the pair.

bool Player::checkHandForBook(Card &c1, Card &c2){
    for(int i = 0; i < myHand.size() - 1; i++)
        for(int j = i + 1; j < myHand.size(); j++)
            if(myHand[i].getRank() == myHand[j].getRank()) {
                c1 = myHand[i];
                c2 = myHand[j];
                //c1 gets card i, c2 gets card j
                return true;
            }

    return false;
}

//OPTIONAL
// comment out if you decide to not use it
//Does the player have a card with the same rank as c in her hand?
//bool rankInHand(Card c) const;

//uses some strategy to choose one card from the player's
//hand so they can say "Do you have a 4?"
Card Player::chooseCardFromHand() const{
    if(myHand.size()==0) return Card();

    for(int i=0; i < myHand.size(); i++){
        int matchCount = 0; // if card in hand is already booked once, 1/2 as likely as a card unbooked
        for(int j=0; j<myBook.size(); j++){
            if(myHand[i] == myBook[j]) matchCount++;

        }
        if(matchCount == 0) return myHand[i]; // if unbooked card then play it... most probable

    }

    return myHand[0]; // otherwise pick the first card for simplicity
}

//Does the player have the card c in her hand?
bool Player::cardInHand(Card c) {
    for( vector<Card>::iterator it = myHand.begin(); it != myHand.end(); it++ ){
        if(c.getRank() == (*it).getRank()) return true;
    }
    return false;
}

//Remove the card c from the hand and return it to the caller
Card Player::removeCardFromHand(Card c){
    Card tempCard;

    for(int i = 0; i < myHand.size(); i++)
        if(myHand[i].getRank() == c.getRank()) {
            tempCard = myHand[i];
            myHand.erase(myHand.begin()+i);
            return tempCard;
        }

    return tempCard;
}

string Player::showHand() const{
    string strHand = "";

    for(int i = 0; i < myHand.size(); i++)
        strHand += myHand[i].toString() + " ";

    return strHand;
}
string Player::showBooks() const{
    string strBooks = "";

    for(int i = 0; i < myBook.size(); i++)
        strBooks += myBook[i].toString() + " ";

    return strBooks;
}

int Player::getHandSize() const{
    return myHand.size();
}
int Player::getBookSize() const{
    return myBook.size();
}

//OPTIONAL
// comment out if you decide to not use it
//this function will check a players hand for a pair.
//If a pair is found, it returns true and populates the two variables with the cards tha make the pair.

//bool Player::checkHandForPair(Card &c1, Card &c2) {return false;}

//OPTIONAL
// comment out if you decide to not use it
//Does the player have a card with the same rank as c in her hand?
//e.g. will return true if the player has a 7d and the parameter is 7c

//bool Player::sameRankInHand(Card c) const { return false;}

