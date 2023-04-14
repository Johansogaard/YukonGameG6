#include <stdio.h>
#include <process.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>



enum Suit{H,C,D,S};
//the struct that symbolize a card
typedef struct Cards {
    int rank;
    enum Suit suit;
    struct Cards* nextCard;

}Card;

//define c1-c7
Card *c1,*c2,*c3,*c4,*c5,*c6,*c7;
//define f1-f4;
Card *f1,*f2,*f3,*f4;


//decleration of methods used in the program
Card *LD(char *filepath);
enum Suit getSuit(char suit);
int getValue(char value);
void printList(Card *c);
void swapCards(Card* card1, Card* card2);
Card *getCardAtIndex(Card *head, int index);
void shuffleList(Card *head);
void makeBoard(char *lc,char *msg);
void printFrow(int row);
char* doCommand(char *command);
void addCards(Card *cards);
char getCharSuit(int Suit);
int main() {


    makeBoard("","");
    while (1)
    {
        char lastCommand[50];
        fgets(lastCommand,sizeof(lastCommand),stdin);
        //removes the newline charcter that fgets adds to the line
         lastCommand[strcspn(lastCommand, "\n")] = '\0';
         //adds a line between each new print gameboard
          printf("\n");
          //does the command

          //makes a new board
          makeBoard(lastCommand, doCommand(&lastCommand));
    }

   struct Card* deck;


   int num_cards;
   char filepath[] = "C:\\Users\\johan\\CLionProjects\\YukonGameG6\\deckofcards.txt";
  // deck = LD(filepath);


    /*printf("\nUnshuffled list\n");
    printList(deck);
    printf("\nshuffled list\n");
    shuffleList(deck);
    printList(deck);
    */

}
void addCards(Card *cards)
{
    int row=0;
    int i =0;
    Card *c[] = {c1,c2,c3,c4,c5,c6,c7};
    for (int j = 0; j < (sizeof(c)/sizeof(c1)) ; ++j) {
        c[j] = cards;

        cards = cards->nextCard;
    }
    while (cards!=NULL)
    {
        getCardAtIndex(c[i],row)->nextCard = cards;
        i = (i+1);
        if(i ==7)
        {
            row = row+1;
        }
        i = i%7;
        cards = cards->nextCard;
    }
    c1 = c[0];
    c2 = c[1];
    c3 = c[2];
    c4 = c[3];
    c5 = c[4];
    c6 = c[5];
    c7 = c[6];
}
char* doCommand(char *command)
{

  if(strcmp(command, "start") == 0){
      return "ok";
    } else if(command[0] == 'L'&& command[1]=='D')
  {
      if(sizeof(command)<3)
      {
          LD(&command[3]);
          //substring
      } else
      {
          addCards(LD("C:\\Users\\johan\\CLionProjects\\YukonGameG6\\deckofcards.txt"));

      }
  }
  else
  {
      return "Command not found";
  }

}
void printFrow(int row)
{

    char toPrint[3] = "[]";
    switch (row) {
        case 0:
            if (f1 != NULL) {
                toPrint[0] = f1->rank;
                toPrint[1] = f1->suit + 'H';
            }
            printf("%s    F1", toPrint);
            break;
        case 1:
            if (f2!= NULL) {
                toPrint[0] =f2->rank;
                toPrint[1] =f2->suit + 'H';
            }
            printf("%s    F2", toPrint);
            break;
        case 2:
            if (f3 != NULL) {
                toPrint[0] = f3->rank;
                toPrint[1] =f3->suit + 'H';
            }
            printf("%s    F3", toPrint);
            break;
        case 3:
            if (f4 != NULL) {
                toPrint[0] = f4->rank;
                toPrint[1] = f4->suit + 'H';
            }
            printf("%s    F4", toPrint);
            break;
        default:
            // handle error condition
            break;
    }

}
bool printCCard(Card *c,int row,bool isEmpty) {
    if(getCardAtIndex(c,row)!=NULL)
    {
        printf("%d%c\t", getCardAtIndex(c,row)->rank, getCharSuit(getCardAtIndex(c,row)->suit));
        return false;
    }else{

        printf("\t");
        return isEmpty;
    }
}
void makeBoard(char *lc,char *msg)
{
    printf("c1\tc2\tc3\tc4\tc5\tc6\tc7\n");


    int row = 0;
    bool isemtpy = false;

   while((isemtpy == false) || (row<4)){
         isemtpy = true;
         isemtpy = printCCard(c1,row,isemtpy);
         isemtpy = printCCard(c2,row,isemtpy);
         isemtpy = printCCard(c3,row,isemtpy);
        isemtpy = printCCard(c4,row,isemtpy);
       isemtpy = printCCard(c5,row,isemtpy);
       isemtpy = printCCard(c6,row,isemtpy);
       isemtpy = printCCard(c7,row,isemtpy);
       printFrow(row);
       printf("\n");
       row++;
     }
    printf("LAST Command:%s",lc);
    printf("\nMessage:%s\n",msg);
    printf("INPUT >");






}
void printList(Card* c)
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
Card* LD(char* filepath)
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
       Card* head = NULL;
      Card* cardBefore= NULL;
        int i = 0;
      while  (fgets(singleLine,150,fPointer) !=NULL){

          if(head==NULL)
          {
              head = malloc(sizeof(Card));
              head->suit = getSuit(singleLine[2]);
              head->rank = getValue(singleLine[0]);
              cardBefore = head;
          }
          else
          {

              Card* newCard =malloc(sizeof( Card));
              cardBefore->nextCard=newCard;
              newCard->suit = getSuit(singleLine[2]);
              newCard->rank = getValue(singleLine[0]);
              cardBefore = newCard;
          }

    };
      cardBefore->nextCard=NULL;
    return head;

}
char getCharSuit(int Suit) {
    char suit;
    switch (Suit) {
        case H:
            suit = 'H';
            break;
        case C:
            suit = 'C';
            break;
        case D:
            suit = 'D';
            break;
        case S:
            suit = 'S';
            break;
        default:
            // handle error condition here
            break;

    }
    return suit;
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
void shuffleList(Card* head)
{
    int count = 0;
    Card* current = head;
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
        Card* card_i = getCardAtIndex(head, i);
        Card* card_j = getCardAtIndex(head, j);
        swapCards(card_i, card_j);
    }
}

// Helper function to get the card at a given index
Card *getCardAtIndex(Card *head, int index)
{
    if(head == NULL)
    {
        return head;
    }
    for (int i = 0; i < index; i++) {
        head = head->nextCard;
        if(head == NULL)
        {
            break;
        }
    }
    return head;
}

// Helper function to swap two cards
void swapCards(Card* card1, Card* card2)
{
    int temp_rank = card1->rank;
    enum Suit temp_suit = card1->suit;
    card1->rank = card2->rank;
    card1->suit = card2->suit;
    card2->rank = temp_rank;
    card2->suit = temp_suit;
}







