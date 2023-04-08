#include <stdio.h>
#include <process.h>
#include <malloc.h>





enum Suit{H,C,D,S};
//the struct that symbolize a card
struct Card {
    int rank;
    enum Suit suit;
    struct Card* nextCard;
};

//decleration of methods used in the program
struct Card* LD(char* filepath);
enum Suit getSuit(char suit);
int getValue(char value);
void printList(struct Card* c);
void swapCards(struct Card* card1, struct Card* card2);
struct Card* getCardAtIndex(struct Card* head, int index);
void shuffleList(struct Card* head);
void makeBoard(struct Card *headarray[]);

int main() {

   struct Card* deck;
   struct Card *headarray[7];
   int num_cards;
   char filepath[] = "C:\\Users\\johan\\CLionProjects\\YukonGameG6\\deckofcards.txt";
  // deck = LD(filepath);
   makeBoard(headarray);
   char s[] = "sdasda";
    printf(s);
    /*printf("\nUnshuffled list\n");
    printList(deck);
    printf("\nshuffled list\n");
    shuffleList(deck);
    printList(deck);
    */

}
void makeBoard( struct Card *carray[])
{
    printf("c1\tc2\tc3\tc4\tc5\tc6\tc7\n");
    int bool[7];
    for (int i = 0; i <7 ; ++i) {
        if(carray[i] !=NULL)
        {
            bool[i] =1;
        }
    }
    int row = 0;
    int max =0;

   while(1){
     for(int f=0;f<7;f++) {
        if(bool[f]==1)
        {
            struct Card* toPrint=getCardAtIndex(carray[f],row);
            printf("%d%d\t",toPrint[f].rank,toPrint[f].suit);
            if(toPrint->nextCard==NULL)
            {
                bool[f]=0;
            }
        } else{
            printf("  \t");
        }

     }
     row++;
    }
}
void printList(struct Card* c)
{
    int i =0;
    while (c != NULL) {
        i++;
        printf("%d, %d, ", i, c->rank);
        switch (c->suit) {
            case H:
                printf("H\n");
                break;
            case C:
                printf("C\n");
                break;
            case D:
                printf("D\n");
                break;
            case S:
                printf("S\n");
                break;
            default:
                printf("Unknown suit\n");
                break;
        }
        c = c->nextCard;
    }
}
struct Card* LD(char* filepath)
{


    char singleLine[3];

    FILE *fPointer;
    fPointer = fopen(filepath, "r");
    //checks if the file is found
    if (fPointer == NULL) {
        printf("Failed to open file.\n");
        fprintf(stderr, "Error: Could not open file '%s'\n", filepath);
        exit(1);

    }
   // struct Card* cards = malloc(capacity* sizeof(struct Card));


    //reading the whole file to end
        struct Card* head = NULL;
        struct Card* cardBefore= NULL;
        int i = 0;
      while  (fgets(singleLine,150,fPointer) !=NULL){

          if(head==NULL)
          {
              head = malloc(sizeof(struct Card));
              head->suit = getSuit(singleLine[2]);
              head->rank = getValue(singleLine[0]);
              cardBefore = head;
          }
          else
          {

              struct  Card* newCard =malloc(sizeof(struct Card));
              cardBefore->nextCard=newCard;
              newCard->suit = getSuit(singleLine[2]);
              newCard->rank = getValue(singleLine[0]);
              cardBefore = newCard;
          }

    };

    return head;
}
enum Suit getSuit(char suit)
{
    enum Suit s;
    //getting the suit
    switch (suit) {
        case 'H':
            s = H;
            break;
        case 'C':
            s= C;
            break;
        case 'D':
            s= D;
            break;
        case 'S':
            s = S;
            break;
        default:
            // handle error condition here
            break;
    }
    return s;
}
int getValue(char value)
{
    int v;
    int valueToCheck = atoi(&value);
    //getting the value
    if(valueToCheck<10 && valueToCheck>1) {
        v = valueToCheck;
    }
    else
    {
        switch (value) {
            case 'T':
                v = 10;
                break;
            case 'A':
                v = 1;
                break;
            case 'J':
                v = 11;
                break;
            case 'Q':
                v = 12;
                break;
            case 'K':
                v = 13;
                break;
            default:
                // handle error condition here
                break;

        }
    }
    return v;

}
void shuffleList(struct Card* head)
{
    int count = 0;
    struct Card* current = head;
    // Count the number of cards in the list
    while (current != NULL) {
        count++;
        current = current->nextCard;
    }
    // Perform the Fisher-Yates shuffle algorithm
    for (int i = count - 1; i > 0; i--) {
        // Generate a random index between 0 and i (inclusive)
        int j = rand() % (i + 1);
        // Swap the cards at index i and j
        struct Card* card_i = getCardAtIndex(head, i);
        struct Card* card_j = getCardAtIndex(head, j);
        swapCards(card_i, card_j);
    }
}

// Helper function to get the card at a given index
struct Card* getCardAtIndex(struct Card* head, int index)
{
    struct Card* current = head;
    for (int i = 0; i < index; i++) {
        current = current->nextCard;
    }
    return current;
}

// Helper function to swap two cards
void swapCards(struct Card* card1, struct Card* card2)
{
    int temp_rank = card1->rank;
    enum Suit temp_suit = card1->suit;
    card1->rank = card2->rank;
    card1->suit = card2->suit;
    card2->rank = temp_rank;
    card2->suit = temp_suit;
}







