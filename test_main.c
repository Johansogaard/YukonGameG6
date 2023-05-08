#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include <assert.h>

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

    // Shuffle the list
    shuffleList(head);

    // Check that the list is shuffled in a different order than the original list
    int isShuffled = 0;
    for (int i = 0; i < 10; i++) {
        if (head->rank != i) {
            isShuffled = 1;
            break;
        }
        head = head->nextCardDec;
    }
    if (!isShuffled) {
        printf("Error: shuffleList() did not shuffle the list\n");
    }
    if (isShuffled) {
        printf("PASSED: shuffleList() shuffled the list\n");
    }
}

int main() {
    // Call the shuffleList() test function
    test_shuffleList();

}
