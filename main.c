#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

enum Suit{H,C,D,S};
enum Rank { A, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K };
char messenge[100] = "";
char input[100] = "";
char parameter[100] = "";
bool playmode = false;
//the struct that symbolize a card
typedef struct Cards {
    enum Rank rank;
    enum Suit suit;
    bool hidden;
    struct Cards *nextCardDec;
    struct Cards *nextCardCol;

/*int isBlack(Cards card) {
	return card.Suit == C || card.Suit == S;
}

int isRed(Cards card) {
	return card.Suit == H || card.Suit == D;
}

int isDifferentColor(Cards higher, Cards lower) {
	return isBlack(higher) != isBlack(lower);
}

int inSequence(Cards lower, Cards higher) {
	return higher.Rank == lower.Rank + 1;
}

int CanBePlaced(Cards lower, Cards higher) {
	return isDifferentColor(higher, lower) && inSequence(lower, higher);
}

int isSameSuit(card first, card second) {
	return first.suit == second.suit;
}

int canBePlacedFoundation(card parent, card child) {
	return isSameSuit(parent, child) && isInSequence(parent, child);
}*/
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
int numCards(Card* deck);
void printList(Card *c);
void swapCards(Card* card1, Card* card2);
Card *getCardAtIndexInDeck(Card *head, int index);
void makeBoard(char *lc,char *msg, char *parameter);
void printFrow(int row);
char* doCommand(char *command, char* parameter);
char RankIntToChar(int rank);
char SuitIntToChar(int suit);
void saveList(Card *head, char *filename);
void shuffleList(Card* head);
void split(Card *deck, int n, int split);
int getlength(Card* head);
void addCards(Card *cards, bool playmode);
char getCharSuit(int Suit);
void SW(Card* head);
Card *getCardAtIndexInCol(Card *head, int index);


int main() {


    makeBoard(input,messenge, parameter);
    while (true)
    {

        fgets(input, sizeof(input), stdin);

        // remove the newline character at the end of the input
        input[strcspn(input, "\n")] = 0;

        // tokenize the input string to extract the command and parameter
        char *command = strtok(input, " ");
        char *parameter = strtok(NULL, " ");
        if(!playmode){
        if (strcmp(command, "QQ") == 0) {
            printf("\ngame shutting down\n");
            break;
        }
        }
        //does the commandLD
        //printf("%s",parameter);
        doCommand(command, parameter);
        //makes a new board
        if (Deck != NULL) {
            if (playmode) {
                addCards(Deck, true);
            } else {
                addCards(Deck, false);
            }
        }

        makeBoard(command, messenge, parameter);

        /*saveList(LD("/Users/victor/CLionProjects/YukonGameG6/deckofcards.txt"),"/Users/victor/CLionProjects/YukonGameG6/savecards.txt" );*/
    }

    struct Card* deck;


    int num_cards;
    char filepath[] = "/Users/victor/CLionProjects/YukonGameG6/deckofcards.txt";
    // deck = LD(filepath);


    /*printf("\nUnshuffled list\n");
    printList(deck);
    printf("\nshuffled list\n");
    shuffleList(deck);
    printList(deck);
    */

}
void addCards(Card *cards, bool playmode)
{
    int row = 0;
    int i = 0;
    Card *c[] = {c1, c2, c3, c4, c5, c6, c7};

    if (playmode) {
        int numCards[] = {1, 6, 7, 8, 9, 10, 11};
        for (int j = 6; j >= 0; j--) {
            for (int k = 0; k < numCards[j]; k++) {
                c[j] = cards;
                cards = cards->nextCardDec;
            }
        }
    } else {
        for (int j = 0; j < (sizeof(c) / sizeof(c1)); ++j) {
            c[j] = cards;
            cards = cards->nextCardDec;
        }
    }

    while (cards != NULL) {
        getCardAtIndexInCol(c[i], row)->nextCardCol = cards;
        cards = cards->nextCardDec;
        getCardAtIndexInCol(c[i], row + 1)->nextCardCol = NULL;
        i = (i + 1) % 7;
        if (i == 0) {
            row++;
        }
    }

    c1 = c[0];
    c2 = c[1];
    c3 = c[2];
    c4 = c[3];
    c5 = c[4];
    c6 = c[5];
    c7 = c[6];
}


char* doCommand(char *command, char* parameter) {
    if (!playmode) {


         if (strcmp(command, "LD") == 0) {
            if (parameter == NULL) {
                strcpy(messenge, "loaded normal deck");
                Deck = LD("/Users/victor/CLionProjects/YukonGameG6/deckofcards.txt");

            } else {
                sprintf(messenge, "loaded deck from %s", parameter);

                Deck = LD(parameter);

            }

        } else if (strcmp(command, "split") == 0) {
            if (parameter == NULL) {
                strcpy(messenge, "split loaded deck");
                Card *deck = LD("/Users/mikkel/Desktop/C-projekter/YukonGame/Projekt2/deckofcards.txt");
                split(deck, numCards(deck), 26);

            } else {
                sprintf(messenge, "split current deck", parameter);
                split(Deck, numCards(Deck), 26);

            }

        } else if (strcmp(command, "SL") == 0) {

            if (Deck == NULL)
            {strcpy(messenge, "No deck");
                return NULL;}

            if (parameter == NULL) {
                srand ( time(NULL) );
                split(Deck, numCards(Deck), rand() % getlength(Deck));

            } else {
                int splitvalid = true;
                for (int i = 0; parameter[i] != '\0'; i++) {
                    if (!isdigit(parameter[i])) {
                        splitvalid = false;
                    }
                }
                if (splitvalid) {

                    split(Deck, numCards(Deck),  atoi(parameter));
                } else { strcpy(messenge, "SL takes int as parameter"); }
            }

        } else if (strcmp(command, "SD") == 0) {
            saveList(Deck, parameter);


        }  else if (strcmp(command, "SR") == 0) {
            if (Deck == NULL)
            {strcpy(messenge, "No deck");
                return NULL;}
            else shuffleList(Deck);
            strcpy(messenge, "shuffled cards");
        } else if (strcmp(command, "SW") == 0) {
            SW(Deck);

            strcpy(messenge, "Here is the deck");
        } else if (strcmp(command, "P") == 0) {
            strcpy(messenge, "Game is in playphase");


            playmode = true;

        }
        else {
            strcpy(messenge, "unknown command");
        }}


        else {
            if((strcmp(command, "SR"))==0 || (strcmp(command, "LD"))==0 || (strcmp(command, "SD"))==0 || (strcmp(command, "P"))==0 || (strcmp(command, "LD"))==0 || (strcmp(command, "QQ"))==0)
            {strcpy(messenge, "Command not available in the PLAY phase");}

            else if (strcmp(command, "Q") == 0) {
                strcpy(messenge, "Game is in startup phase");
                playmode = false;

            }
else if(command==!NULL && parameter==!NULL) {
     if (strlen(command) == 2 && strlen(parameter) == 2) {  }
                strcpy(messenge, "unknown command");
}
            else {
                strcpy(messenge, "unknown command");
            }
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
            printf("%8s   F1", toPrint);
            break;
        case 1:
            if (f2!= NULL) {
                toPrint[0] =f2->rank;
                toPrint[1] =f2->suit + 'H';
            }
            printf("%8s   F2", toPrint);
            break;
        case 2:
            if (f3 != NULL) {
                toPrint[0] = f3->rank;
                toPrint[1] =f3->suit + 'H';
            }
            printf("%8s   F3", toPrint);
            break;
        case 3:
            if (f4 != NULL) {
                toPrint[0] = f4->rank;
                toPrint[1] = f4->suit + 'H';
            }
            printf("%8s   F4", toPrint);
            break;
        default:
            // handle error condition
            break;
    }

}
bool printCCard(Card *c,int row,bool isEmpty) {
    if(getCardAtIndexInCol(c,row)!=NULL)
    {
        if(getCardAtIndexInCol(c,row)->hidden==false) {
            printf("%c%c\t", RankIntToChar(getCardAtIndexInCol(c, row)->rank), SuitIntToChar(getCardAtIndexInCol(c, row)->suit));
            return false;
        } else
        {
            printf("[]\t");
            return false;
        }
    }else{

        printf("\t");
        return isEmpty;
    }
}
void makeBoard(char *lc,char *msg, char *parameter)
{
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");


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
    if(playmode && parameter!=NULL){
    printf("LAST Command:%s %s",lc, parameter);}
    else {printf("LAST Command:%s ",lc);}

    printf("\nMessage: %s\n",msg);
    printf("INPUT >");



}
void printList(Card* c)
{
    int i =0;
    while (c != NULL) {
        i++;
        printf(" %c, %c\n", RankIntToChar(c->rank), SuitIntToChar(c->suit));

        c = c->nextCardDec;
    }
}
Card* LD(char* filepath)
{


    char singleLine[3];

    FILE *fPointer;
    fPointer = fopen(filepath, "r");
    //checks if the file is found
    if (fPointer == NULL) {

        sprintf(messenge, "file does not exist %s", filepath);

        return fPointer;

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
            head->hidden=true;
            head->rank = getValue(singleLine[0]);
            cardBefore = head;
        }
        else
        {

            Card* newCard =malloc(sizeof( Card));
            newCard->hidden=true;
            cardBefore->nextCardDec=newCard;
            newCard->suit = getSuit(singleLine[2]);
            newCard->rank = getValue(singleLine[0]);
            cardBefore = newCard;
        }

    }
      cardBefore->nextCardDec=NULL;
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
//saves the deck to a file, takes the deck and the output file as input
void saveList(Card *head, char *filename) {
    if (head==NULL){
        strcpy(messenge, "No deck");
        return;
    }
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        sprintf(messenge, "Wrong filepath %s", filename);
        return;
    }


    while (head != NULL) {
        fprintf(fp, "%c%c \n", RankIntToChar(head->rank), SuitIntToChar(head->suit));
        head = head->nextCardDec;
    }
    sprintf(messenge, "Saved deck to %s", filename);
    fclose(fp);
}



//ShuffleList - using double pointers, because
void shuffleList(Card* head) {
    if (head==NULL){
        strcpy(messenge, "No deck");
        return;
    }
    //initialiser unshuffled and shuffled list. unshuffled set to original card deck, shuffled set to NULL
    Card* unshuffled = head;
    Card* shuffled = NULL;

    //loop until unshuffled is empty, ie. original list
    while (unshuffled != NULL) {
        // Remove the top card from the unshuffled list, and store in new pointer: top_card
        Card* top_card = unshuffled;
        unshuffled = unshuffled->nextCardDec;
        top_card->nextCardDec = NULL;

        // Generate a random index between 0 and the current length of the shuffled list
        int rand_index = 0;
        int length = 0;
        Card* current = shuffled;
        while (current != NULL) {
            length++;
            //move current to next node on list
            current = current->nextCardDec;
        }
        //generates a random integer between 0 and length
        srand ( time(NULL) );
        rand_index = rand() % (length + 1);

        // Insert the removed card at the rand_index position in the shuffled list
        if (rand_index == 0) {
            top_card->nextCardDec = shuffled;
            shuffled = top_card;
        } else {
            Card* prev = getCardAtIndexInDeck(shuffled, rand_index - 1);
            top_card->nextCardDec = prev->nextCardDec;
            prev->nextCardDec = top_card;
        }
    }

    // Replace the original unshuffled list with the shuffled list
    Deck = shuffled;
}

//helper function for split
int numCards(Card* deck) {
    int count = 0;
    Card* current = deck;
    while (current != NULL) {
        count++;
        current = current->nextCardDec;
    }
    return count;
}

void split(Card *deck, int n, int split) {
    Card *pile1 = deck;
    Card *pile2 = deck;
    int i, p1_len;

    p1_len = (split > 0 && split < n) ? split : (rand() % n);

    for (i = 1; i < p1_len; i++) {
        pile2 = pile2->nextCardDec;
    }
    Card *temp = pile2->nextCardDec;
    pile2->nextCardDec = NULL;
    pile2 = temp;

    Card *shuffled = NULL;
    Card *current = NULL;
    while (pile1 != NULL && pile2 != NULL) {
        if (rand() % 2 == 0) {
            if (shuffled == NULL) {
                shuffled = pile1;
                current = shuffled;
            } else {
                current->nextCardDec = pile1;
                current = current->nextCardDec;
            }
            pile1 = pile1->nextCardDec;
        } else {
            if (shuffled == NULL) {
                shuffled = pile2;
                current = shuffled;
            } else {
                current->nextCardDec = pile2;
                current = current->nextCardDec;
            }
            pile2 = pile2->nextCardDec;
        }
    }
    if (pile1 != NULL) {
        current->nextCardDec = pile1;
    } else {
        current->nextCardDec = pile2;
    }
    Deck = shuffled;
    sprintf(messenge, "shuffled deck using split method, with parameter %d", p1_len);
}

void SW(Card* head) {
    Card* starthead=head;
    Card* current = head;
    while (current != NULL) {
        current->hidden = false;
        current = current->nextCardDec;
    }
    Deck=starthead;
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

// Helper function to get the card at a given index
Card *getCardAtIndexInDeck(Card *head, int index)
{
    if(head == NULL)
    {
        return head;
    }
    for (int i = 0; i < index; i++) {
        head = head->nextCardDec;
        if(head == NULL)
        {
            break;
        }
    }
    return head;
}
// Helper function to get the card at a given index
Card *getCardAtIndexInCol(Card *head, int index)
{
    if(head == NULL)
    {
        return head;
    }
    for (int i = 0; i < index; i++) {
        head = head->nextCardCol;
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

int getlength(Card* head) {
    int count = 0;
    Card* current = head;
    while (current != NULL) {
        count++;
        current = current->nextCardDec;
    }
    return count;
}
