#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *nextPtr;
} Node;

//Alias ad una variabile puntatore di tipo struttura
typedef Node *ListPtr;

//Prototipi:
void insertNode (ListPtr *head, char element);
void insertInOrder (ListPtr *head, char element);
int isEmpty (ListPtr head);
void emptyList (ListPtr *head);
char deleteElement (ListPtr *head, char value);
void displayList (ListPtr currentPtr);
void instructions ();

int main () 
{
    ListPtr head = NULL;
    unsigned int choice;
    char value;

    instructions();
    do {
        printf("%s", "Set choice: ");
        scanf("%u", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("%s", "Insert a character to insert (a-z, A-Z, 0-9): ");
                scanf("%c", &value);
                getchar();
                insertInOrder(&head, value);
                break;
            case 2:
                printf("%s", "Insert a character to delete (a-z, A-Z, 0-9): ");
                scanf("%c", &value);
                
                char deleted = deleteElement(&head, value);
                
                if(deleted != 0) {
                    printf("%s %c\n\n", "Deleted element:", deleted);
                } else {
                    puts("Element not found!");
                }

                break;
            case 3:
                displayList(head);
                break;
            case 4:
                emptyList(&head);
                break;
            case 5:
                puts("End of the program!");
                return 0;
            default: 
                puts("Invalid instructions!");
                instructions();
                break;
        }

    } while (choice != 5);

    return 0;
}

//Funzione per inserire un elemento nella lista alla sua fine.
//Non prevede inserimento ordinato degli elementi
void insertNode (ListPtr *head, char element) {
    ListPtr newPtr, prevPtr, currentPtr;
    
    //Alloco il nuovo puntatore a struttura
    newPtr = malloc(sizeof(Node));

    if(newPtr != NULL) {

        newPtr->data = element;
        newPtr->nextPtr = NULL;
        
        currentPtr = *head;
        prevPtr = NULL;

        //Scorro tutta la lista per vedere dove si trova l'ultimo puntatore a struttura noto
        //e faccio sì che il currentPtr punti all'ultimo puntatore che punta all'ultimo elemento
        //della lista
        while(currentPtr != NULL) {
            prevPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        //Se non ho trovato nulla in precedenza, inserisco il nuovo nodo in testa
        if(prevPtr == NULL) {
            newPtr->nextPtr = *head;
            *head = newPtr;
        } else {
            //Altrimenti, aggiungo il nuovo elemento in coda alla lista
            prevPtr->nextPtr = newPtr;
        }
    } else {
        //In questo caso, non potremo inserire nessun elemento, newPtr sarà  NULL
        puts("It is not possible to set a new node");
    }
}

//Funzione che inserisce un nuovo elemento in un nuovo nodo
//della lista in ordine. USARE QUESTA COME PREDEFINITA!
void insertInOrder (ListPtr *head, char element){
    ListPtr newPtr, currPtr, prevPtr;
    
    newPtr = malloc(sizeof(Node));
    
    if(newPtr != NULL){
        newPtr->data = element;
        newPtr->nextPtr = NULL;

        currPtr = *head;
        prevPtr = NULL;

        //Prima di questa parte, la funzione è simile a quella di prima.
        //Qui vediamo in più se l'elemento da cercare è più grande di
        //quello contenuto in currPtr. Finchè la condizione è vera,
        //ci spostiamo all'elemento successivo in lista tenendo il 
        //riferimento a quello precedente. Usciremo dal while quando
        //in currPtr avremo il puntatore al nodo che ha un elemento 
        //più grande di quello che stiamo cercando.
        while(currPtr != NULL && element > currPtr->data){
            prevPtr = currPtr;
            currPtr = currPtr->nextPtr;
        }

        //Ovviamente, se la lista è vuota, o il primo elemento è più grande di
        //quello da inserire, inseriremo il nuovo elemento in testa
        if(prevPtr == NULL){
            newPtr->nextPtr = *head;
            *head = newPtr;
        } else {
            //Se siamo qui, significa che il while ha trovato un elemento più
            //grande di quello cercato, quindi, inseriamo il nuovo nodo tra
            //il prevPtr ed il currPtr.
            prevPtr->nextPtr = newPtr;
            newPtr->nextPtr  = currPtr;
        }
    } else {
        //In questo caso, non potremo inserire nessun elemento, newPtr sarà  NULL
        puts("It is not possible to set a new node");
    }
}

//Funzione che mi permette di conoscere se la lista è vuota
int isEmpty (ListPtr head) {
    return head == NULL;
}

//Funzione che mi fa svuotare tutta la lista
void emptyList (ListPtr *head) {
    ListPtr tempPtr;

    while(*head != NULL) {
        tempPtr = *head;
        *head = (*head)->nextPtr;
        free(tempPtr);
    }
}

//Eliminiamo un elemento dalla lista se esiste
char deleteElement (ListPtr *head, char value) {

    ListPtr currentPtr, prevPtr, tempPtr;

    //Controlliamo se l'elemento cercato è in testa alla lista
    if(value == (*head)->data) {
        tempPtr = *head;
        *head = (*head)->nextPtr;
        free(tempPtr);
        return value;
    } else {    

        //Se siamo qui, evidentemente non è il primo elemento della lista
        prevPtr = *head;
        currentPtr = (*head)->nextPtr;

        //Scorriamo la lista fintantochè non arriviamo alla fine e 
        //non troviamo l'elemento cercato. Nel mentre teniamo conto 
        //dell'elemento precedente della lista.
        while(currentPtr != NULL && value != currentPtr->data) {
            prevPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if(currentPtr != NULL) {
            //Se siamo qui, abbiamo trovato l'elemento, mettiamo l'elemento
            //in un puntatore temporaneo. Facciamo puntare il puntatore precedente
            //al successivo del puntatore in cui si trova il dato da eliminare
            //liberiamo infine la memoria in cui si trova il valore e lo restituiamo.
            tempPtr = currentPtr;
            prevPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return value;
        } else {
            //Non è stato trovato nulla. Insuccesso!
            return 0;
        }
    }
}

//Funzione per visualizzare la lista
void displayList (ListPtr currentPtr) {
    if(isEmpty(currentPtr)) {
        puts("List is empty");
    } else {
        puts("List: \n");

        while(currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }

        puts("NULL \n");
    }
}

void instructions () {
    puts("Make a choice:");
    puts("1: Insert a node;");
    puts("2: Delete element;");
    puts("3: Print List;");
    puts("4: Empty List");
    puts("5: Exit.");
}