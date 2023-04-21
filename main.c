#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


enum Suit{H,C,D,S};
enum Rank { A, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K };
char messenge[100] = "";
char input[100] = "";
//the struct that symbolize a card
typedef struct Cards {
    enum Rank rank;
    enum Suit suit;
    bool hidden;
    struct Cards* nextCard;

}Card;

Card* Deck;


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
char* doCommand(char *command, char* parameter);
char RankIntToChar(int rank);
char SuitIntToChar(int suit);
void saveList(Card *head, char *filename);
void split(Card *deck, int n, int split);
int numCards(Card* deck);
int main() {


    makeBoard(input,messenge);
    while (true)
    {

        fgets(input, sizeof(input), stdin);

        // remove the newline character at the end of the input
        input[strcspn(input, "\n")] = 0;

        // tokenize the input string to extract the command and parameter
        char *command = strtok(input, " ");
        char *parameter = strtok(NULL, " ");

        if (strcmp(command, "QQ") == 0) {
            printf("\ngame shutting down\n");
            break;
        }
        //does the commandLD
        //printf("%s",parameter);
        doCommand(command, parameter);
        //makes a new board
        makeBoard(command, messenge);
        printList(Deck);
        saveList(LD("/Users/mikkel/Desktop/C-projekter/YukonGame/Projekt2/deckofcards.txt"),"/Users/mikkel/Desktop/C-projekter/YukonGame/Projekt2/savecards.txt" );
    }

    struct Card* deck;


    int num_cards;
    char filepath[] = "/Users/victor/CLionProjects/YukonGameG6/deckofcards.txt";
    // deck = LD(filepath);


    /*printf("\nUnshuffled list\n");
    printList(deck);
    printf("\nshuffled list\n");
    shuffleList(deck);
    printList(deck);*/


}
char* doCommand(char *command, char* parameter)
{
    char tempstring [100];

    if(strcmp(command, "start") == 0){
        strcpy(messenge, "OK");
    }

    else if(strcmp(command, "LD") == 0)
    {
        if( parameter == NULL)
        {
            Deck=LD("/Users/mikkel/Desktop/C-projekter/YukonGame/Projekt2/deckofcards.txt");
            strcpy(messenge, "loaded normal deck");
        } else
        {
            Deck=LD(parameter);

            sprintf(tempstring, "loaded deck from %s", parameter);
            strcpy(messenge, tempstring);

        }
    }
    else if(strcmp(command, "split") == 0){
        if( parameter == NULL)
        {
            Card *deck = LD("/Users/mikkel/Desktop/C-projekter/YukonGame/Projekt2/deckofcards.txt");
            split(deck, numCards(deck), 26);


            strcpy(messenge, "Loaded and split new deck");
        } else
        {

            split(Deck, numCards(Deck), 26);

            sprintf(tempstring, "Split current deck", parameter);
            strcpy(messenge, tempstring);

        }
    }

    else if(strcmp(command, "SD") == 0){
        saveList(Deck, parameter);
        sprintf(tempstring, "saved deck to %s", parameter); //error
        strcpy(messenge, tempstring);
    }

    else
    {
        strcpy(messenge, "unknown command");
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
        printf("%d%d\t", getCardAtIndex(c1,row)->rank,getCardAtIndex(c1,row)->suit);
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
        printf(" %c, %c\n", RankIntToChar(c->rank), SuitIntToChar(c->suit));

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
            head->hidden=false;
            head->rank = getValue(singleLine[0]);
            cardBefore = head;
        }
        else
        {

            Card* newCard =malloc(sizeof( Card));
            cardBefore->nextCard=newCard;
            newCard->suit = getSuit(singleLine[2]);
            head->hidden=false;
            newCard->rank = getValue(singleLine[0]);
            cardBefore = newCard;
        }

    };

    return head;
}
//saves the deck to a file, takes the deck and the output file as input
void saveList(Card *head, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return;
    }


    while (head != NULL) {
        fprintf(fp, "%c%c \n", RankIntToChar(head->rank), SuitIntToChar(head->suit));
        head = head->nextCard;
    }

    fclose(fp);
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

        switch (value) {
            case 'A':
                return A;
            case '2':
                return TWO;
            case '3':
                return THREE;
            case '4':
                return FOUR;
            case '5':
                return FIVE;
            case '6':
                return SIX;
            case '7':
                return SEVEN;
            case '8':
                return EIGHT;
            case '9':
                return NINE;
            case 'T':
                return TEN;
            case 'J':
                return J;
            case 'Q':
                return Q;
            case 'K':
                return K;
            case 'C':
                return C;
            case 'D':
                return D;
            case 'H':
                return H;
            case 'S':
                return S;
            default:
                printf("Error: invalid rank '%c' in input file\n", value);
                return -1;  // return -1 if the character is not recognized
        }
}

char RankIntToChar(int rank) {
    switch (rank) {
        case A:
            return 'A';
        case TWO:
            return '2';
        case THREE:
            return '3';
        case FOUR:
            return '4';
        case FIVE:
            return '5';
        case SIX:
            return '6';
        case SEVEN:
            return '7';
        case EIGHT:
            return '8';
        case NINE:
            return '9';
        case TEN:
            return 'T';
        case J:
            return 'J';
        case Q:
            return 'Q';
        case K:
            return 'K';
        default:
            return 'Error converting Rank';
    }
}
char SuitIntToChar(int suit) {
    switch (suit) {
        case C:
            return 'C';
        case D:
            return 'D';
        case H:
            return 'H';
        case S:
            return 'S';
        default:
            return 'Error converting suit';  // return an error message if the integer is not recognized
    }
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
//Helper function for split function
int numCards(Card* deck) {
    int count = 0;
    Card* current = deck;
    while (current != NULL) {
        count++;
        current = current->nextCard;
    }
    return count;
}


void split(Card *deck, int n, int split) {
    Card *pile1 = deck;
    Card *pile2 = deck;
    int i, p1_len;

    p1_len = (split > 0 && split < n) ? split : (rand() % n);

    for (i = 1; i < p1_len; i++) {
        pile2 = pile2->nextCard;
    }
    Card *temp = pile2->nextCard;
    pile2->nextCard = NULL;
    pile2 = temp;

    Card *shuffled = NULL;
    Card *current = NULL;
    while (pile1 != NULL && pile2 != NULL) {
        if (rand() % 2 == 0) {
            if (shuffled == NULL) {
                shuffled = pile1;
                current = shuffled;
            } else {
                current->nextCard = pile1;
                current = current->nextCard;
            }
            pile1 = pile1->nextCard;
        } else {
            if (shuffled == NULL) {
                shuffled = pile2;
                current = shuffled;
            } else {
                current->nextCard = pile2;
                current = current->nextCard;
            }
            pile2 = pile2->nextCard;
        }
    }
    if (pile1 != NULL) {
        current->nextCard = pile1;
    } else {
        current->nextCard = pile2;
    }
    Deck = shuffled;
}

