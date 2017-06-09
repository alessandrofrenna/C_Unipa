#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *nextPtr;
} Node;

//Alias ad una variabile puntatore di tipo struttura
typedef Node *ListPtr;

//Prototipi:
void insertNode (ListPtr *head, int element);
void insertInOrder (ListPtr *head, int element);
int isEmpty (ListPtr head);
void emptyList (ListPtr head);
int deleteElement (ListPtr *head, int value);
void displayList (ListPtr currentPtr);
ListPtr merge (ListPtr const first, ListPtr const second);
int random (int start, int end);

int main () 
{
    ListPtr first = NULL, second = NULL, result = NULL;
    int val;

    
    for(int i = 0; i < 10; i++){
        insertInOrder(&first, i);
        insertInOrder(&second, i);
    } 
    
    puts("Lista uno concatenata inserita");
    displayList(first);

    puts("Lista due concatenata inserita");
    displayList(first);

    puts("Lista merge concatenata inserita");
    result = merge(first, second);     
    displayList(result);   


    emptyList(first);
    emptyList(second);
    emptyList(result);
    
    return 0;
}

//Funzione che inserisce un nuovo elemento in un nuovo nodo
//della lista in ordine. USARE QUESTA COME PREDEFINITA!
void insertInOrder (ListPtr *head, int element){
    ListPtr newPtr, currPtr, prevPtr;
    
    newPtr = malloc(sizeof(Node));
    
    if(newPtr != NULL){
        newPtr->data = element;
        newPtr->nextPtr = NULL;

        currPtr = *head;
        prevPtr = NULL;

        //Prima di questa parte, la funzione � simile a quella di prima.
        //Qui vediamo in pi� se l'elemento da cercare � pi� grande di
        //quello contenuto in currPtr. Finch� la condizione � vera,
        //ci spostiamo all'elemento successivo in lista tenendo il 
        //riferimento a quello precedente. Usciremo dal while quando
        //in currPtr avremo il puntatore al nodo che ha un elemento 
        //pi� grande di quello che stiamo cercando.
        while(currPtr != NULL && element > currPtr->data){
            prevPtr = currPtr;
            currPtr = currPtr->nextPtr;
        }

        //Ovviamente, se la lista � vuota, o il primo elemento � pi� grande di
        //quello da inserire, inseriremo il nuovo elemento in testa
        if(prevPtr == NULL){
            newPtr->nextPtr = *head;
            *head = newPtr;
        } else {
            //Se siamo qui, significa che il while ha trovato un elemento pi�
            //grande di quello cercato, quindi, inseriamo il nuovo nodo tra
            //il prevPtr ed il currPtr.
            prevPtr->nextPtr = newPtr;
            newPtr->nextPtr  = currPtr;
        }
    } else {
        //In questo caso, non potremo inserire nessun elemento, newPtr sar�� NULL
        puts("It is not possible to set a new node");
    }
}

//Funzione che mi permette di conoscere se la lista � vuota
int isEmpty (ListPtr head) {
    return head == NULL;
}

//Funzione che mi fa svuotare tutta la lista
void emptyList (ListPtr head) {
    ListPtr tempPtr;

    while(head != NULL) {
        tempPtr = head;
        head = head->nextPtr;
        free(tempPtr);
    }
}

//Eliminiamo un elemento dalla lista se esiste
int deleteElement (ListPtr *head, int value) {

    ListPtr currentPtr, prevPtr, tempPtr;

    //Controlliamo se l'elemento cercato � in testa alla lista
    if(value == (*head)->data) {
        tempPtr = *head;
        *head = (*head)->nextPtr;
        free(tempPtr);
        return value;
    } else {    

        //Se siamo qui, evidentemente non � il primo elemento della lista
        prevPtr = *head;
        currentPtr = (*head)->nextPtr;

        //Scorriamo la lista fintantoch� non arriviamo alla fine e 
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
            //Non � stato trovato nulla. Insuccesso!
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

//Funzione che fa il merge ordinato di due liste concatenate
ListPtr merge (ListPtr const first, ListPtr const second) {
    ListPtr headFirst, headSecond, resultList, resultPtr;

    headFirst  = first;
    headSecond = second;
    if((resultPtr = malloc(sizeof(Node))) == NULL) {
        return NULL;    
    }

    resultPtr->nextPtr = NULL;
    resultList = resultPtr;

    while(headFirst != NULL && headSecond != NULL){
        if(headFirst->data < headSecond->data){
            resultPtr->data = headFirst->data;
            headFirst = headFirst->nextPtr;
        } else {
            resultPtr->data = headSecond->data;
            headSecond = headSecond->nextPtr;
        }

        if((resultPtr->nextPtr = malloc(sizeof(Node))) == NULL){
            emptyList(resultList);
            return NULL;
        } else {
            resultPtr = resultPtr->nextPtr;
            resultPtr->nextPtr = NULL;
        }
    }

    if(headFirst == NULL){
        resultPtr->data = headSecond->data;
        while ((headSecond = headSecond->nextPtr) != NULL){
            if((resultPtr->nextPtr = malloc(sizeof(Node))) == NULL){
                emptyList(resultList);
                return NULL;
            } else {
                resultPtr = resultPtr->nextPtr;
                resultPtr->data = headSecond->data;
                resultPtr->nextPtr = NULL;
            }
        }
    } else {
        resultPtr->data = headFirst->data;
        while((headFirst = headFirst->nextPtr) != NULL) {
            if((resultPtr->nextPtr = malloc(sizeof(Node))) == NULL) {
                emptyList(resultList);
                return NULL;
            } else {
                resultPtr = resultPtr->nextPtr;
                resultPtr->data = headFirst->data;
                resultPtr->nextPtr = NULL;
            }
        }
    }

    return resultList;
}

int random (int start, int end) {
    return start + rand() % end;
}