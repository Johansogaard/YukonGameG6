#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

char messenge[200] = "";
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
    bool inFoundation;
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
Card* createDeck();
Card* createCard(int rank, int suit);
enum Suit getSuit(char suit);
enum Rank getRank(char value);
int numCards(Card* deck);
void printList(Card *c);
void swapCards(Card* card1, Card* card2);
Card *getCardAtIndexInDeck(Card *head, int index);
void makeBoard(char *lc,char *msg, char *parameter);
void printFrow(int row);
char* doCommand(char *command, char* parameter, char* subcommand);
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
void gameMove(char* command, char* Parameter, char*Subcommand);
Card* youPointingAtMe(Card* me);
Card *getCardAtIndexInCol(Card *head, int index);
void saveToFile(char* File);
void loadCards(char* File);
void foundationMove(char* Command, char* Parameter);
bool colPointingToMe(Card* Me);
void hide(Card* head);
const char *SuitIntToCharTermial(int suit);
void TakeOutOfFoundation(Card* head);
bool isUnderMe(Card *from, Card *to);
bool cardInCol(Card* col,Card* me);
Card* cardAtEndOfCol(Card* col);
Card* getCol(char* colName);
void placeSafe(Card* from);
Card ** getFoundation(char* Parameter);
char* deckHasAllSuitsAndValues(Card* deck);
bool isACol(char* colName);


int main() {

    makeBoard(input,messenge, parameter);
    while (true)
    {

            char *command=NULL;
            char *subcommand=NULL;
            char *parameter;
        fgets(input, sizeof(input), stdin);

        // remove the newline character at the end of the input
        input[strcspn(input, "\n")] = 0;
        char *originput=input;
        // tokenize the input string to extract the command and parameter
        if (!playmode) {
            command = strtok(input, " ");
            parameter = strtok(NULL, " ");
            }
            else if (input[2]!=':'){
            subcommand = strtok(input, "-");
            parameter = strtok(NULL, ">");
                }
         else {
            subcommand = strtok(input, ":");
            command = strtok(NULL, "-");
            parameter = strtok(NULL, ">");

        }


        if(command==NULL){command=" ";}
        if(subcommand==NULL){subcommand=" ";}
        if(!playmode){
        if (strcmp(command, "QQ") == 0) {
            printf("\ngame shutting down\n");
            break;
        }
        }
        //does the commandLD
        //printf("%s",parameter);
        if(Deck!=NULL || strcmp(command, "LD")==0) {
            doCommand(command, parameter, subcommand);
        }
        else{strcpy(messenge, "No deck");}
        //makes a new board

        if (Deck != NULL && !playmode){
            addCards(Deck, playmode);
            if(show>0){
                SW(Deck);}
            else{hide(Deck);}

        }

        makeBoard(command, messenge, originput);


    }



}
/*
Adds cards to the columns based on the specified game mode.
cards: pointer to the head of the linked list of cards to be added to the columns.
playmode: boolean that determines whether cards are added for playing or dealing purposes.
 */
void addCards(Card *cards, bool playmode)
{
    // row counter and index counter variables
    int row = 0;
    int i = 0;

    // array of pointers to each column
    Card *c[] = {c1, c2, c3, c4, c5, c6, c7};

    // array to keep track of whether a column has been set
    bool setcard[] = {false,true,true,true,true,true,true};

    if (playmode) {
        // loop through each column
        for (int j = 0; j < (sizeof(c) / sizeof(c1)); ++j) {
            // set the current column to the head of the cards list
            c[j] = cards;

            // set the nextCardCol pointer of the last card in the current column to NULL
            getCardAtIndexInCol(c[i], row)->nextCardCol = NULL;

            // set the hidden attribute of all cards in columns 2 through 7 to true
            if(j>0)
            {
                c[j]->hidden=true;

                // set the hidden attribute of the first card in column 1 to false
            } else
            {
                c[j]->hidden=false;
            }

            // move to the next card in the list
            cards = cards->nextCardDec;
        }
        // loop through the remaining cards in the list
        while (cards != NULL) {

            // calculate the value of sethid, which determines how many cards should be hidden
            int sethid =1;
            sethid = sethid+row;

            // set the hidden attribute of the current card based on its position in the layout
            if(i>sethid)
            {
                cards->hidden=true;
            } else
            {
                cards->hidden=false;
            }

            // if the current column has not been set, add the current card to it
            if(setcard[i] ==true) {
                getCardAtIndexInCol(c[i], row)->nextCardCol = cards;

                // move to the next card in the list
                cards = cards->nextCardDec;
                // set the nextCardCol pointer of the last card in the current column to NULL
                getCardAtIndexInCol(c[i], row + 1)->nextCardCol = NULL;
            }
            // increment the index counter and handle the wrapping
            i = (i + 1) % 7;

            // increment the row counter if the index has wrapped around
            if (i == 0) {
                row++;
            }

            // set the corresponding element in the setcard array to false if the row has reached a certain value
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
// loop through each column and assign a card to each column
        for (int j = 0; j < (sizeof(c) / sizeof(c1)); ++j) {
            c[j] = cards;
            cards = cards->nextCardDec;
        }

// Loop through remaining cards and assign them to the columns
        while (cards != NULL) {
            // assign the next card in the deck to the specified column and row
            getCardAtIndexInCol(c[i], row)->nextCardCol = cards;
            cards = cards->nextCardDec;
            // set the next card in the row to NULL
            getCardAtIndexInCol(c[i], row + 1)->nextCardCol = NULL;
            i = (i + 1) % 7;
            if (i == 0) {
                row++;
            }
        }


    }
    // Assign each column to its respective variable
    c1 = c[0];
    c2 = c[1];
    c3 = c[2];
    c4 = c[3];
    c5 = c[4];
    c6 = c[5];
    c7 = c[6];
}



char* doCommand(char *command, char* parameter, char* subcommand) {
    if (!playmode) {

        // Execute command based on input
         if (strcmp(command, "LD") == 0) {// Load deck
            if (parameter == NULL) {// If no parameter is given, create a new deck
                strcpy(messenge, "OK");
                Deck = createDeck();
                addCards(Deck, playmode);
            } else {// Load deck from file
                strcpy(messenge, "OK");

                Deck = LD(parameter);
                if (Deck!=NULL){addCards(Deck, playmode);     }

            }
        }
         else if (strcmp(command, "SL") == 0) {// Split deck
            if (parameter == NULL) {// If no parameter is given, split the deck randomly
                srand ( time(NULL) );
                split(Deck, numCards(Deck), rand() % getlength(Deck));

            } else {// If parameter is given, split the deck at the given index
                int splitvalid = true;
                for (int i = 0; parameter[i] != '\0'; i++) {
                    if (!isdigit(parameter[i])) {// Check if parameter is a valid integer
                        splitvalid = false;
                        splitvalid = false;
                    }
                }
                if (splitvalid) {

                    split(Deck, numCards(Deck),  atoi(parameter));
                } else {// If parameter is not a valid integer, show an error message
                    strcpy(messenge, "SL takes int as parameter"); }
            }

        } else if (strcmp(command, "SD") == 0) {// Save deck
             if (parameter == NULL) {// If no parameter is given, save deck to default file
                 saveList(Deck, "relativ filepath");}
             // If parameter is given, save deck to the given file
            saveList(Deck, parameter);


        }  else if (strcmp(command, "SR") == 0){// Shuffle deck
            shuffleList(Deck);
            strcpy(messenge, "shuffled cards");}


         else if (strcmp(command, "SW") == 0) {// Show deck
            show++;
            strcpy(messenge, "OK");}

         else if (strcmp(command, "P") == 0) {// Play mode
            strcpy(messenge, "Game is in playphase");
            playmode = true;
            addCards(Deck, playmode);
        }

        else {// If the input command is not recognized, show an error message
            strcpy(messenge, "unknown command");
        }
    }

        else {if((strcmp(subcommand, "SR"))==0 || (strcmp(subcommand, "LD"))==0
        || (strcmp(subcommand, "SD"))==0 || (strcmp(subcommand, "P"))==0 || (strcmp(subcommand, "LD"))==0
        || (strcmp(subcommand, "QQ"))==0 ||(strcmp(subcommand, "SW"))==0)
            {strcpy(messenge, "Command not available in the PLAY phase");}

            else if (strcmp(subcommand, "Q") == 0) {
                strcpy(messenge, "Game is in startup phase");
                playmode = false;
                f1=f2=f3=f4=NULL;
                TakeOutOfFoundation(Deck);}

            else if (strcmp(subcommand, "S") == 0){
                sprintf(messenge, "saved game to %s", parameter);
                saveToFile(parameter);}

            else if (strcmp(subcommand, "L") == 0){
                sprintf(messenge, "loaded game from %s", parameter);
                loadCards(parameter);}


else if(subcommand!=NULL && parameter!=NULL /*&& (!(strcmp(command, parameter)))==0*/) {

     if (strlen(subcommand) == 2 && strlen(parameter) == 2) {gameMove(command, parameter, subcommand);}
    else {
        strcpy(messenge, "unknown command/illegal move");
    }

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
                toPrint[0] = RankIntToChar(cardAtEndOfCol(f1)->rank);
                toPrint[1] = SuitIntToChar(cardAtEndOfCol(f1)->suit);
            }
            printf("%8s   F1", toPrint);
            break;
        case 1:
            if (f2!= NULL) {
                toPrint[0] = RankIntToChar(cardAtEndOfCol(f2)->rank);
                toPrint[1] = SuitIntToChar(cardAtEndOfCol(f2)->suit);
            }
            printf("%8s   F2", toPrint);
            break;
        case 2:
            if (f3 != NULL) {
                toPrint[0] = RankIntToChar(cardAtEndOfCol(f3)->rank);
                toPrint[1] = SuitIntToChar(cardAtEndOfCol(f3)->suit);
            }
            printf("%8s   F3", toPrint);
            break;
        case 3:
            if (f4 != NULL) {
                toPrint[0] = RankIntToChar(cardAtEndOfCol(f4)->rank);
                toPrint[1] = SuitIntToChar(cardAtEndOfCol(f4)->suit);
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
            printf("%c%s\t", RankIntToChar(getCardAtIndexInCol(c, row)->rank)
                   , SuitIntToCharTermial(getCardAtIndexInCol(c, row)->suit));
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
void makeBoard(char *lc,char *msg, char *input)
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
    if(playmode){
    printf("LAST Command:%s",input);}
    else {printf("LAST Command:%s ",lc);}

    printf("\nMessage: %s\n",msg);
    printf("INPUT >");


}
/*void printList(Card* c)
{
    int i =0;
    while (c != NULL) {
        i++;
        printf(" %c, %c\n", RankIntToChar(c->rank), SuitIntToChar(c->suit));

        c = c->nextCardDec;
    }
}*/
Card* createDeck() {
    Card* head = NULL;
    Card* last = NULL;

    // create a card object for each rank/suit combination and add it to the end of the linked list
    for (int suit = C; suit <= S; suit++) {
        for (int rank = A; rank <= K; rank++) {
            Card* newcard = createCard(rank, suit);
            if (newcard == NULL) {
                printf("Error creating new card.\n");
                return NULL;
            }

            if (head == NULL) {
                head = newcard;
                last = newcard;
            } else {
                last->nextCardDec = newcard;
                last = newcard;
            }
        }
    }
    return head;
    }

Card* LD(char* filepath)
{
    char singleLine[3];

    FILE *fPointer;
    fPointer = fopen(filepath, "r");
    //checks if the file is found
    if (fPointer == NULL) {
        sprintf(messenge, "the file does not exist %s", filepath);
        return NULL;
    }

    //reading the whole file to end
    Card* head = NULL;
    Card* cardBefore= NULL;
    int i = 0;

    // Read the file line by line
    while  (fgets(singleLine,150,fPointer) !=NULL){


        if(head==NULL) {
                if(singleLine[0]!=' '&&singleLine[1]!=' ') {
                    i++;
                    head = malloc(sizeof(Card));
                    head->suit = getSuit(singleLine[1]);
                    head->hidden = true;
                    head->rank = getRank(singleLine[0]);
                    cardBefore = head;
                }

        }
            // If the current line is not the first line, create a new linked list node and link it to the previous node

        else
        {
            if (singleLine[0]!=' '&&singleLine[1]!=' ') {
                Card* newCard =malloc(sizeof( Card));
                i++;
                newCard->hidden = true;
                cardBefore->nextCardDec = newCard;
                newCard->suit = getSuit(singleLine[1]);
                newCard->rank = getRank(singleLine[0]);
                cardBefore = newCard;
                cardBefore->nextCardDec = NULL;
            }
        }

    }
    char* missingCards = deckHasAllSuitsAndValues(head);

    // Check if the deck contains more than 52 cards
    if(i>52)
    {
        sprintf(messenge, "File contains more than 52 cards and cannot be used", filepath);
        return NULL;
    }

    else if(strlen(missingCards) != 0)
    {
        sprintf(messenge, "File is missing the cards : %s",missingCards, filepath);
        return NULL;

        // If the deck is valid, return the head of the linked list
    } else {

        cardBefore->nextCardDec = NULL;
        return head;
    }

}
// This function checks if the deck contains all 52 cards and returns a string of missing cards
char* deckHasAllSuitsAndValues(Card* deck) {
    bool seen[4][13] = { false };
    Card* curr = deck;
    while (curr != NULL) {
        if(curr->suit>=0&&curr->suit<4&&curr->rank>=0&&curr->rank<13) {
            seen[curr->suit][curr->rank] = true;
        }
        curr = curr->nextCardDec;
    }
    char* missingCards = malloc(sizeof(char) * 156);
    missingCards[0] = '\0'; // initialize the string to an empty string
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            if (!seen[i][j]) {
                char value = RankIntToChar(j);
                char suit = getCharSuit(i);
                char valueSuit[3];
                sprintf(valueSuit, "%c%c ", value, suit);
                strcat(missingCards, valueSuit);
            }
        }
    }
    return missingCards;
}

Card* createCard(int rank, int suit) {
    Card* newcard = malloc(sizeof(Card));
    newcard->rank = rank;
    newcard->suit = suit;
    newcard->hidden = 0;   // initialize the hidden flag to false
    newcard->nextCardDec = NULL;  // initialize the next pointer to NULL
    return newcard;}

// This function takes an integer representing the suit of a playing card,
// and returns the corresponding character
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
    return suit; // Return the suit character
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
    //check if the list is empty
    if (head==NULL){
        strcpy(messenge, "No deck");
        return;
    }
    // Try to open the file for writing.
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        sprintf(messenge, "Wrong filepath %s", filename);
        return;
    }

    // Traverse the linked list and write each card to the file.
    while (head != NULL) {
        fprintf(fp, "%c%c \n", RankIntToChar(head->rank), SuitIntToChar(head->suit));
        head = head->nextCardDec;
    }
    sprintf(messenge, "Saved deck to %s", filename);
    fclose(fp);
}

//Shuffle cards
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

bool cardInCol(Card* col,Card* me){
    Card* current=col;
    if(current==me){return true;}
    while(current->nextCardCol!=NULL){
        if (current==me||current->nextCardCol==me){
            return true;
        }
        current=current->nextCardCol;
    }
    return false;
}

Card* cardAtEndOfCol(Card* col){
    Card* current=col;
    if(current==NULL){return NULL;}
    while(current->nextCardCol!=NULL){
        current=current->nextCardCol;
    }
    return current;
}

Card* getCol(char* colName) {
    if (strcmp(colName, "C1") == 0) {
        return c1;
    } else if (strcmp(colName, "C2") == 0) {
        return c2;
    } else if (strcmp(colName, "C3") == 0) {
        return c3;
    } else if (strcmp(colName, "C4") == 0) {
        return c4;
    } else if (strcmp(colName, "C5") == 0) {
        return c5;
    } else if (strcmp(colName, "C6") == 0) {
        return c6;
    } else if (strcmp(colName, "C7") == 0) {
        return c7;
    } else if (strcmp(colName, "F1") == 0) {
        return f1;
    } else if (strcmp(colName, "F2") == 0) {
        return f2;
    } else if (strcmp(colName, "F3") == 0) {
        return f3;
    } else if (strcmp(colName, "F4") == 0) {
        return f4;
    } else {
        return NULL;
    }
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
    if (f1 != NULL && f1 == Me) {
        f1 = NULL; // Make c7 a null pointer
        return true;}
    if (f2 != NULL && f2 == Me) {
        f2 = NULL; // Make c7 a null pointer
        return true;}
    if (f3 != NULL && f3 == Me) {
        f3 = NULL; // Make c7 a null pointer
        return true;}
    if (f4 != NULL && f4 == Me) {
        f4 = NULL; // Make c7 a null pointer
        return true;}
    // none of the pointers point to Me
    return false;
}

void placeSafe(Card* from){
    if (!colPointingToMe(from)) {
        if (youPointingAtMe(from)->hidden == true) {
            youPointingAtMe(from)->hidden = false;
        }
        youPointingAtMe(from)->nextCardCol = NULL;

    }strcpy(messenge, "OK");}

Card ** getFoundation(char* Parameter){
    switch (Parameter[1]) {
        case '1':
            return &f1;
            case '2':
                return &f2;
                case '3':
                    return &f3;
                    case '4':
                        return &f4;
                        default:
                            return NULL;
    }}

    bool isACol(char* colName){
        if (strcmp(colName, "C1") == 0) {
            return true;
        } else if (strcmp(colName, "C2") == 0) {
            return true;
        } else if (strcmp(colName, "C3") == 0) {
            return true;
        } else if (strcmp(colName, "C4") == 0) {
            return true;
        } else if (strcmp(colName, "C5") == 0) {
            return true;
        } else if (strcmp(colName, "C6") == 0) {
            return true;
        } else if (strcmp(colName, "C7") == 0) {
            return true;
        } else if (strcmp(colName, "F1") == 0) {
            return true;
        } else if (strcmp(colName, "F2") == 0) {
            return true;
        } else if (strcmp(colName, "F3") == 0) {
            return true;
        } else if (strcmp(colName, "F4") == 0) {
            return true;
        } else {
            return false;
        }
}

void gameMove(char* Command, char* Parameter, char*Subcommand){

    Card **foundation = NULL;

    if(Command==" "){
        Card* from=cardAtEndOfCol(getCol(Subcommand));

        Card* to=cardAtEndOfCol(getCol(Parameter));

    if(from==NULL || !isACol(Parameter)){strcpy(messenge, "wrong input"); return;}

    if(Parameter[0]=='F' && from->inFoundation==false) {

        Card **foundation=getFoundation(Parameter);

        if (*foundation == NULL) {
            // Handle case where foundation is not found
            if (from->rank==A && (from->nextCardCol==NULL))  {

                placeSafe(from);
            *foundation = from;
            from->inFoundation=true;
            }
            else{strcpy(messenge, "illegal move");}
        }

        else if (canBePlacedFoundation(from, to)&& (from->nextCardCol==NULL)) {
            // Move the card to the foundation pile

                placeSafe(from);
                to->nextCardCol = from;
                from->inFoundation=true;

            }

        else{strcpy(messenge, "illegal move");}

    }


        else if(Parameter[0]!='F' && getCol(Parameter)&& canBePlaced(from, to) && getCol(Parameter)) {
        if(from->inFoundation==true){from->inFoundation=false;}
            placeSafe(from);
            to->nextCardCol = from;

    }
        else{strcpy(messenge, "illegal move");}
    }




    else{
            Card* from=getCard(Command);

            Card* to=cardAtEndOfCol(getCol(Parameter));

        if(from==NULL || !isACol(Parameter)){strcpy(messenge, "wrong input"); return;}

        if(Parameter[0]=='F'&& from->inFoundation==false) {

            if(!cardInCol(getCol(Subcommand), from)){
                sprintf(messenge, "Card %s not in column %s", Command, Subcommand);
                return;}

            Card **foundation=getFoundation(Parameter);

            if (*foundation == NULL) {
                // Handle case where foundation is not found
                if (from->rank==A && (from->nextCardCol==NULL))  {

                    placeSafe(from);
                    *foundation = from;
                    from->inFoundation=true;
                }

                else if (canBePlacedFoundation(from, to)&& (from->nextCardCol==NULL)) {
                    // Move the card to the foundation pile

                    placeSafe(from);
                    to->nextCardCol = from;
                    from->inFoundation=true;
                }
                else{strcpy(messenge, "illegal move");}
            }}


        else if(Parameter[0]!='F' && Subcommand[0]!='F'){
         if(!cardInCol(getCol(Subcommand), from)){
            sprintf(messenge, "Card %s not in column %s", Command, Subcommand);
            return;}

         if(getCol(Parameter)&&canBePlaced(from, to) && !isUnderMe(from, to)) {

            placeSafe(from);
            to->nextCardCol = from;
            from->inFoundation=false;
        }
         else{strcpy(messenge, "illegal move");}
        }
         else{strcpy(messenge, "illegal move");}
    }
    }

    /*Card *from = getCard(Command);
    Card *to;
     to=getCard(Parameter);
    if (from==NULL || to==NULL){
        strcpy(messenge, "CARD not found");
        return;
    }
    // If the move is valid and the destination column is empty, move the card to the new column and update the messenge string
    if (canBePlaced(from, to) && to->nextCardCol==NULL){

        // If the card being moved was hidden, unhide it
        if (youPointingAtMe(from)->hidden==true){youPointingAtMe(from)->hidden=false;}

        // Update the pointers to move the card to the new column.
        youPointingAtMe(from)->nextCardCol=NULL;
        to->nextCardCol=from;
        sprintf(messenge, "Moved %s to %s", Command, Parameter);
        }
        // If the move is valid but the destination column is not empty, move the card anyway(places it on top of another card, and update the messenge string
    else if(colPointingToMe(from)){
        to->nextCardCol=from;
        sprintf(messenge, "Moved %s to %s", Command, Parameter);
        }
    //if move is invalid, error message
    else{sprintf(messenge, "Cannot move %s to %s", Command, Parameter);}
*/

Card* getCard(char* input){

    // Parsing the input string to get the desired rank and suit of the card.
    enum Suit desiredsuit = getSuit(input[1]);
    enum Rank desiredrank = getRank(input[0]);

    //Start at the beginning of the deck and search for a card with the desired rank and suit.
    Card* head=Deck;
    while(head!=NULL){
        if (head->suit==desiredsuit && head->rank==desiredrank){
            return head; // Return the card if it is found.
        }
        head=head->nextCardDec;
    }
    // if card is not found return error message and NULL
    strcpy(messenge,"card not found");
    return NULL;
}

// This function searches for the card in the deck that is pointing at the given card. It returns a pointer to the card that is pointing at the given card
Card* youPointingAtMe(Card* me){

    // Start at the beginning of the deck and search for a card that is pointing at the given card
    Card* head=Deck;
    while(head!=NULL) {
        if (head->nextCardCol == me) {
            return head; // Return the card that is pointing at the given card
        }
        head = head->nextCardDec;
    }
}
//counts the number of cards in the deck and returns integer with the count
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

void TakeOutOfFoundation(Card* head) {
    Card* starthead=head;
    Card* current = head;
    while (current != NULL) {
        current->inFoundation = false;
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
enum Rank getRank(char value)
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
            default:
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
         // return an error message if the integer is not recognized
    }
}

bool isUnderMe(Card *from, Card *to){
    Card *current = from;
    while (current!=NULL) {
        if (current->nextCardCol == to) {
            return true;
        }
        current = current->nextCardCol;
    }
        return false;
    }


const char *SuitIntToCharTermial(int suit) {
    switch (suit) {
        case C:
            return "\u2663";
        case D:
            return "\u2666";
        case H:
            return "\u2665";
        case S:
            return "\u2660";
         // return an error message if the integer is not recognized
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
/*void swapCards(Card* card1, Card* card2)
{
    int temp_rank = card1->rank;
    enum Suit temp_suit = card1->suit;
    card1->rank = card2->rank;
    card1->suit = card2->suit;
    card2->rank = temp_rank;
    card2->suit = temp_suit;
}
*/
int getlength(Card* head) {
    int count = 0;
    Card* current = head;
    while (current != NULL) {
        count++;
        current = current->nextCardDec;
    }
    return count;
}
