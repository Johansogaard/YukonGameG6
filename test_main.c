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
    // Create a list of cards that is ordered in a specific way
    Card* head = NULL;
    for (int i = 0; i < 10; i++) {
        Card* newCard = malloc(sizeof(Card));
        newCard->rank = i;
        newCard->suit = 'H';
        newCard->nextCardDec = head;
        head = newCard;
    }

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
void test_createDeck()
{
    Card* testdeck;
    testdeck= createDeck();

    char* missingCards = deckHasAllSuitsAndValues(testdeck);
    if(strlen(missingCards) == 0)
    {
        printf("PASSED: createDeck\n");
    } else {
        printf("File is missing the cards : %s",missingCards);
    }
    printf("\n");

}

int main() {
    // Call the shuffleList() test function
    test_shuffleList();
    test_createDeck();

}

