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

int main() {
    // Call the shuffleList() test function
    test_shuffleList();

}
