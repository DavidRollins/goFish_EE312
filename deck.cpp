#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include "card.h"
#include "player.h"
#include "deck.h"
// David Rollins, DER2366
// Thu Nov 8, 2018
using namespace std;

Deck::Deck()
{
   /* for (int i=0; i < 4; i++)
    {
        for (int j=1; j < 13; j++)
        {
            Card::Suit s;
            if(i==0) s = Card::spades;
            if(i==1) s = Card::hearts;
            if(i==2) s = Card::diamonds;
            if(i==3) s = Card::clubs;
            Card card(j, s);
            //m_deck.push_back(card);
            myCards[j*i+j] = card;
        }
    }
    myIndex = 0;
    */
   // topCardIndex = 0;
    int index = 0;

    for (int intSuit = 0; intSuit < 4; intSuit++) {
        for (int intRank = 0; intRank < 13; intRank++) {
            Card::Suit suit = (Card::Suit)intSuit;

            index = intSuit*13+intRank;
            Card card(intRank+1, suit);
            myCards[index] = card;

        }
    }
    myIndex = SIZE-1;
}         // pristine, sorted deck

void swap (Card *a, Card *b)
{
    Card temp = *a;
    *a = *b;
    *b = temp;
}

// A function to generate a random permutation of arr[]
void randomize (Card arr[], int n )
{   // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);

        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}
void Deck::shuffle(){
    randomize(myCards, SIZE);
}   // shuffle the deck, all 52 cards present


Card Deck::dealCard(){
   // cout << myCards[myIndex-1] << " ";
    //cout << myIndex;

    if(myIndex < 52) {
        Card pickedCard = myCards[myIndex];
        myIndex--;
        return pickedCard;
    }else{
        cout << "All Cards Dealt" << endl;

        Card cNULL(-1, (Card::Suit)0);
        return cNULL;
    }
}   // get a card, after 52 are dealt, fail

int  Deck::size() const{
    return SIZE-myIndex;

} // # cards left in the deck
