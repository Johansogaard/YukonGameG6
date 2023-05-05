#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char messenge[100] = "";
char input[100] = "";
char parameter[100] = "";
bool playmode = false;
int show=0;
//the struct that symbolize a card
enum Suit{C,D,H,S};
enum Rank { A, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K };
typedef struct Cards {
    enum Rank rank;
    enum Suit suit;
    bool hidden;
    struct Cards *nextCardDec;
    struct Cards *nextCardCol;


}Card;

Card* Deck;


//define c1-c7
Card *c1,*c2,*c3,*c4,*c5,*c6,*c7;
//define f1-f4;
Card *f1, *f2, *f3, *f4;

int isBlack(Card *card) {
    return card->suit == C || card->suit == S;
}

int isRed(Card *card) {
    return card->suit == H || card->suit == D;
}

int isDifferentColor(Card *higher, Card *lower) {
    return isBlack(higher) != isBlack(lower);
}

int inSequence(Card *lower, Card *higher) {
    return higher->rank == lower->rank + 1;
}

int canBePlaced(Card *lower, Card *higher) {
    return isDifferentColor(higher, lower) && inSequence(lower, higher);
}

int isSameSuit(Card *first, Card *second) {
    return first->suit == second->suit;
}

int canBePlacedFoundation(Card *parent, Card *child) {
    return isSameSuit(parent, child) && inSequence(child, parent);
}

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
Card* getCard(char* card);
void gameMove(char* command, char* Parameter);
Card* youPointingAtMe(Card* me);
Card *getCardAtIndexInCol(Card *head, int index);
void saveToFile(char* File);
void loadCards(char* File);
void foundationMove(char* Command, char* Parameter);
bool colPointingToMe(Card* Me);
void hide(Card* head);


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
        if(Deck!=NULL || strcmp(command, "LD")==0) {
            doCommand(command, parameter);
        }
        else{strcpy(messenge, "No deck");}
        //makes a new board

        if (Deck != NULL && !playmode){
            addCards(Deck, playmode);
            if(show>0){
                SW(Deck);}
            else{hide(Deck);}

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
    bool setcard[] = {false,true,true,true,true,true,true};

    if (playmode) {
        for (int j = 0; j < (sizeof(c) / sizeof(c1)); ++j) {
            c[j] = cards;
            getCardAtIndexInCol(c[i], row)->nextCardCol = NULL;
            if(j>0)
            {
                c[j]->hidden=true;

            } else
            {
                c[j]->hidden=false;
            }
            cards = cards->nextCardDec;
        }
        while (cards != NULL) {
            int sethid =1;
            sethid = sethid+row;
            if(i>sethid)
            {
                cards->hidden=true;
            } else
            {
                cards->hidden=false;
            }
            if(setcard[i] ==true) {
                getCardAtIndexInCol(c[i], row)->nextCardCol = cards;
                cards = cards->nextCardDec;
                getCardAtIndexInCol(c[i], row + 1)->nextCardCol = NULL;
            }
            i = (i + 1) % 7;
            if (i == 0) {
                row++;
            }
            switch (row) {
                case 5:
                    setcard[1] = false;
                    break;
                case 6:
                    setcard[2] = false;
                    break;
                case 7:
                    setcard[3] = false;
                    break;
                case 8:
                    setcard[4]=false;
                    break;
                case 9:
                    setcard[5] = false;
                    break;
                default:
                    break;
                
            }
        }
        }
    else {
        for (int j = 0; j < (sizeof(c) / sizeof(c1)); ++j) {
            c[j] = cards;
            cards = cards->nextCardDec;
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
                addCards(Deck, playmode);
            } else {
                sprintf(messenge, "loaded deck from %s", parameter);

                Deck = LD(parameter);
                                   addCards(Deck, playmode);
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


        }  else if (strcmp(command, "SR") == 0){

            shuffleList(Deck);
            strcpy(messenge, "shuffled cards");}


         else if (strcmp(command, "SW") == 0) {
            show++;
            strcpy(messenge, "Here is the deck");}

         else if (strcmp(command, "P") == 0) {
            strcpy(messenge, "Game is in playphase");
            playmode = true;
            addCards(Deck, playmode);
        }

        else {strcpy(messenge, "unknown command");
        }
    }

        else {if((strcmp(command, "SR"))==0 || (strcmp(command, "LD"))==0 || (strcmp(command, "SD"))==0 || (strcmp(command, "P"))==0 || (strcmp(command, "LD"))==0 || (strcmp(command, "QQ"))==0)
            {strcpy(messenge, "Command not available in the PLAY phase");}

            else if (strcmp(command, "Q") == 0) {
                strcpy(messenge, "Game is in startup phase");
                playmode = false;}

            else if (strcmp(command, "S") == 0){
                sprintf(messenge, "saved game to %s", parameter);
                saveToFile(parameter);}

            else if (strcmp(command, "L") == 0){
                sprintf(messenge, "loaded game from %s", parameter);
                loadCards(parameter);}

else if(command!=NULL && parameter!=NULL) {
    if (parameter[0]=='F' && (strlen(command) == 2 && strlen(parameter) == 2)){ foundationMove(command, parameter );}
     else if (strlen(command) == 2 && strlen(parameter) == 2) {gameMove(command, parameter);}

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
                toPrint[0] = RankIntToChar(f1->rank);
                toPrint[1] = SuitIntToChar(f1->suit);
            }
            printf("%8s   F1", toPrint);
            break;
        case 1:
            if (f2!= NULL) {
                toPrint[0] = RankIntToChar(f2->rank);
                toPrint[1] = SuitIntToChar(f2->suit);
            }
            printf("%8s   F2", toPrint);
            break;
        case 2:
            if (f3 != NULL) {
                toPrint[0] = RankIntToChar(f3->rank);
                toPrint[1] = SuitIntToChar(f3->suit);
            }
            printf("%8s   F3", toPrint);
            break;
        case 3:
            if (f4 != NULL) {
                toPrint[0] = RankIntToChar(f4->rank);
                toPrint[1] = SuitIntToChar(f4->suit);
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

void saveToFile(char* File) {
    Card *c[] = {c1, c2, c3, c4, c5, c6, c7};

    Card *head = Deck;
    FILE *fp = fopen(File, "wb");
    if (fp == NULL) {
        strcpy(messenge,"Error opening file");
        return;
    }
    for (int i = 0; i < 7; i++) {
        // Write the column identifier to the file
        fwrite(&i, sizeof(int), 1, fp);

        // Traverse the linked list for this column
        Card *current = c[i];
        while (current != NULL) {
            // Write the Card struct to the file
            fwrite(current, sizeof(Card), 1, fp);

            // Move to the next Card in the linked list
            current = current->nextCardCol;
        }
    }

    fclose(fp);
}

void loadCards(char* file) {
    Card *c[] = {c1, c2, c3, c4, c5, c6, c7};

    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Loop over the file
    while (!feof(fp)) {
        // Read the column identifier from the file
        int columnId;
        fread(&columnId, sizeof(int), 1, fp);

        // Read the Card struct from the file
        Card *newCard = (Card *) malloc(sizeof(Card));
        if (!newCard) {
            printf("Memory allocation failed\n");
            return;
        }
        fread(newCard, sizeof(Card), 1, fp);
        newCard->nextCardCol = NULL;

        // Add the Card struct to the linked list for this column
        if (c[columnId] == NULL) {
            c[columnId] = newCard;
        } else {
            Card *current = c[columnId];
            while (current->nextCardCol != NULL) {
                current = current->nextCardCol;
            }
            current->nextCardCol = newCard;
        }
    }

    fclose(fp);
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

bool colPointingToMe(Card* Me){
    if (c1 != NULL && c1 == Me) {
        c1 = NULL; // Make c1 a null pointer
        return true;
    }
    if (c2 != NULL && c2 == Me) {
        c2 = NULL; // Make c2 a null pointer
        return true;
    }
    if (c3 != NULL && c3 == Me) {
        c3 = NULL; // Make c3 a null pointer
        return true;
    }
    if (c4 != NULL && c4 == Me) {
        c4 = NULL; // Make c4 a null pointer
        return true;
    }
    if (c5 != NULL && c5 == Me) {
        c5 = NULL; // Make c5 a null pointer
        return true;
    }
    if (c6 != NULL && c6 == Me) {
        c6 = NULL; // Make c6 a null pointer
        return true;
    }
    if (c7 != NULL && c7 == Me) {
        c7 = NULL; // Make c7 a null pointer
        return true;
    }
    // none of the pointers point to Me
    return false;
}

//helper function for split
void foundationMove(char* Command, char* Parameter) {
    Card* from = getCard(Command);
    Card **foundation = NULL;

    switch (Parameter[1]) {
        case '1':
            foundation = &f1;
            break;
        case '2':
            foundation = &f2;
            break;
        case '3':
            foundation = &f3;
            break;
        case '4':
            foundation = &f4;
            break;
        default:
            foundation = NULL;
    }



    if (*foundation == NULL) {
        // Handle case where foundation is not found
        if ((strcmp(Command, "AC") == 0 || strcmp(Command, "AD") == 0 ||
            strcmp(Command, "AH") == 0 || strcmp(Command, "AS") == 0) && (from->nextCardCol==NULL))  {
            if(colPointingToMe(from)){
                *foundation = from;
                sprintf(messenge, "Moved %s to %s", Command, Parameter);}



        else if(youPointingAtMe(from)!=NULL){
            if (youPointingAtMe(from)->hidden == true) {
                youPointingAtMe(from)->hidden = false;

            }

            youPointingAtMe(from)->nextCardCol = NULL;}
            *foundation = from;
            sprintf(messenge, "Moved %s to %s", Command, Parameter);
        }
    } else if (from == NULL) {
        // Handle case where card is not found
        strcpy(messenge, "CARD not found");
    } else if (canBePlacedFoundation(from, *foundation)&& (from->nextCardCol==NULL)) {
        // Move the card to the foundation pile
        youPointingAtMe(from)->nextCardCol = foundation;
        *foundation = from;
        colPointingToMe(from);
        if (youPointingAtMe(from)->hidden == true) {
            youPointingAtMe(from)->hidden = false;
        }
        sprintf(messenge, "Moved %s to %s", Command, Parameter);
    } else {
        sprintf(messenge, "Cannot move %s to %s", Command, Parameter);
    }
}


void gameMove(char* Command, char* Parameter){
    Card *from = getCard(Command);
    Card *to;
     to=getCard(Parameter);
    if (from==NULL || to==NULL){
        strcpy(messenge, "CARD not found");
    }
    if (canBePlaced(from, to) && to->nextCardCol==NULL){

        if (youPointingAtMe(from)->hidden==true){youPointingAtMe(from)->hidden=false;}
        youPointingAtMe(from)->nextCardCol=NULL;
        to->nextCardCol=from;
        sprintf(messenge, "Moved %s to %s", Command, Parameter);
        }
        else if(colPointingToMe(from)){
        to->nextCardCol=from;
        sprintf(messenge, "Moved %s to %s", Command, Parameter);
        }
    else{sprintf(messenge, "Cannot move %s to %s", Command, Parameter);}

}

Card* getCard(char* input){
    enum Suit desiredsuit = getValue(input[1]);
    enum Rank desiredrank = getValue(input[0]);
    Card* head=Deck;
    while(head!=NULL){
        if (head->suit==desiredsuit && head->rank==desiredrank){
            return head;
        }

        head=head->nextCardDec;

    }
    strcpy(messenge,"card not found");
    return NULL;
}

Card* youPointingAtMe(Card* me){
    Card* head=Deck;
    while(head!=NULL) {
        if (head->nextCardCol == me) {
            return head;
        }
        head = head->nextCardDec;
    }

}



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
    show--;
}

void hide(Card* head) {
    Card* starthead=head;
    Card* current = head;
    while (current != NULL) {
        current->hidden = true;
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
