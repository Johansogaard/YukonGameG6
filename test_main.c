#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include <assert.h>
bool isDeckEqual(Card* deck1, Card* deck2) {
    while (deck1 != NULL && deck2 != NULL) {
        if (deck1->rank != deck2->rank || deck1->suit != deck2->suit) {
            return false;
        }
        deck1 = deck1->nextCardDec;
        deck2 = deck2->nextCardDec;
    }
    return deck1 == NULL && deck2 == NULL;
}

void test_shuffleList() {

    // Create a deck of cards
    Card* deck = createDeck();

    // Shuffle the deck
    shuffleList(deck);

    // Check if the deck has been shuffled
    bool isShuffled = !isDeckEqual(deck, createDeck());
    printf("Test 01: Shufflelist()\n");
    if (isShuffled) {
        printf("PASSED: shuffleList() shuffled the deck\n");
    } else {
        printf("FAILED: shuffleList() did not shuffle the deck\n");
    }
    printf("\n");
}

void test_split() {
    // Create a deck of cards
    Card* deck = createDeck();
    // Shuffle the deck
    shuffleList(deck);
    // Split the deck
    split(deck, 52, 26);
    // Check that the number of cards in each pile is correct
    assert(getlength(deck) == 51);
    assert(getlength(deck->nextCardDec) == 26);
    assert(getlength(deck->nextCardDec->nextCardDec) == 26);
    // Check that the cards in the original deck are distributed correctly
    Card* current = deck;
    int i;
    for (i = 0; i < split; i++) {
        current = current->nextCardDec;
    }
    Card* pile1 = deck->nextCardDec;
    Card* pile2 = current->nextCardDec;
    for (i = 0; i < split; i++) {
        assert(pile1->rank == deck->rank && pile1->suit == deck->suit);
        assert(pile2->rank == current->rank && pile2->suit == current->suit);
        pile1 = pile1->nextCardDec;
        pile2 = pile2->nextCardDec;
    }
}


int main() {
    // Call the shuffleList() test function
    test_shuffleList();
    // Call the split() test function
    test_split();
return 0;
}
