#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <stdio.h>
#include "card.h"
#include "player.h"
#include "deck.h"

// This class represents a playing card, i.e., "ace of spades"
// a Card is constructed from a rank (int in range 1..13)
// and a suit (Card::spades, Card::hearts, Card::diamonds,
// Card::clubs)
//
// Cards should be created by a Deck (see deck.h), a Deck returns
// good cards
// The function toString() converts a card to a string, e.g., to print
//
// Accessor functions include
//
// int GetRank()      -- returns 1, 2, ..., 13 for ace, two, ..., king
//
// bool SameSuitAs(c) -- returns true if same suit as Card c
//
// string suitString() -- returns "s", "h", "d" or "c"
//
// Note that the Ace is represented by 1 and the King by 13
// David Rollins, DER2366
// Thu Nov 8, 2018


using namespace std;

Card::Card(){
    myRank = 1;
    mySuit = spades;
}          // default, ace of spades
//enum Card::Suit {spades, hearts, diamonds, clubs};

Card::Card(int rank, Suit s){
    myRank = rank;
    mySuit = s;

}


bool Card::sameSuitAs(const Card& c) const{
    return mySuit == c.mySuit;


}  // true if suit same as c

string Card::suitString(Suit s)      const{
    switch(s){
        case spades   : return "s";
        case hearts   : return "h";
        case diamonds : return "d";
        case clubs    : return "c";
    }

}// return "s", "h",...

string Card::rankString(int r) const{
    if(r == 1) return "A";
    else if(r == 11) return "J";
    else if(r == 12) return "Q";
    else if(r == 13) return "K";
    else {
	if(r==2) return "2";
	if(r==3) return "3";
	if(r==4) return "4";
	if(r==5) return "5";
	if(r==6) return "6";
	if(r==7) return "7";
	if(r==8) return "8";
	if(r==9) return "9";
	if(r==10) return "10";
        return "";
    }
}  // return "A", "2", ..."Q"


bool Card::operator == (const Card& rhs) const{
    if(myRank == rhs.getRank() && this->sameSuitAs(rhs)){
        return true;
    }
    return false;

}
bool Card::operator != (const Card& rhs) const{
    if(myRank == rhs.getRank() && this->sameSuitAs(rhs)) return false;
    return true;

}

string Card::toString() const{
    return rankString(myRank) + suitString(mySuit);
}  // return string version e.g. Ac 4h Js
/*
bool Card::operator < (const Card& rhs)    const{
    if( myRank == rhs.myRank ) {
        return mySuit < rhs.mySuit;
    }
    return myRank < rhs.myRank;
}
*/

ostream& operator << (ostream& out, const Card& c){
    out << c.rankString(c.getRank()) << c.suitString(c.getSuit());
    return out;

}

