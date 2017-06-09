#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "accesso_casuale.h"

static unsigned long int maxCostumers = 0;
static unsigned long int actualCostumers = 0;
struct clientData {
    unsigned int id;
    char *name;
    char *lastname;
    unsigned int age;
};

/*
 * Funzioni di utilità dichiarate statiche non usabili fuori da questa implementazione.
 */

//Funzioni per visualizzazioni di messaggi 
static void NotFoundFile () {
    puts("File not found!");
}

static void CreatedFile () {
    puts("File was not in the system. File created!");
}

static void CantOverrideMax() {
    puts("Max has already been set!");
}

static void warningMaxCostumerMissing() {
    puts("Max costumers was not entered! Please edit your client, insert the function setMaxCostumers(unsigned long int)");
}

static void youShallNotAdd() {
    puts("You reached the limit! No more record will be added! Consider create a new file instead!");
}

//Funzioni helper
static bool exists(char *name) {
    return !access(name, F_OK);
}

static bool isNull (FILE *ptr) {
    return ptr == NULL;
}

static bool ReadMode (char *mode) {
    return !strcmp(mode, "r");
}

static bool issetMaxCostumers() {
    return maxCostumers != 0;
}

static bool reachedLimit() {
    return ( getMaxCostumers() - getActualCostumers() ) == 0;   
}

/*
 * Funzioni libreria implementate
 */

FILE * openFile (char *name, char *mode) {
    FILE *ptr;

    if(!exists(name) && !ReadMode(mode)){
        
        if(!issetMaxCostumers()){
            warningMaxCostumerMissing();
            return NULL;
        }

        ptr = fopen(name, mode);
        initDefaultFile(ptr);
        CreatedFile();
    } else if (!exists(name) && ReadMode(mode)) {
        NotFoundFile();
    } else {
        ptr = fopen(name, mode);
        setActualFileCostumers(ptr);
    }
    
    if(isNull(ptr)) {
        return NULL;
    } 

    return ptr;
}

bool initDefaultFile(FILE *ptr){
    Costumer defaultCostumer = {0, "", "", 0};
    if(insertCostumer(defaultCostumer, maxCostumers, ptr) > 0) {
        return true;
    } else { 
         return false;
    }
}

unsigned int insertCostumer(Costumer person, size_t howMany, FILE *ptr) {
    setActualFileCostumers(ptr);
    if(reachedLimit()) {
        youShallNotAdd();
        return 0;  
    } 

    return fwrite(&person, sizeof(Costumer), howMany, ptr);
}

void setActualFileCostumers(FILE *ptr) {
    fseek(ptr, 0, SEEK_END);
    unsigned long int number = ftell(ptr) / sizeof(Costumer);
    actualCostumers = number;
}

void setMaxCostumers(unsigned long int max) {
    if(maxCostumers == 0){
        maxCostumers = max;
    } else {
        CantOverrideMax();
    }
}

unsigned long int getActualCostumers() {
    return actualCostumers;
}

unsigned long int getMaxCostumers() {
    return maxCostumers;
}

void getAllCostumers(FILE *ptr, Costumer *result) {
    unsigned long int size = getActualCostumers();    

    fseek(ptr, 0, SEEK_SET);
    size_t found = fread(result, sizeof(Costumer), size, ptr);
    printf("Size %lu\n\n", found);
}


int main(){
    setMaxCostumers(100);
    FILE *costumers = openFile("costumers.txt", "r");
    Costumer person = {1, "Alessandro", "Frenna", 21};
    insertCostumer(person, 1, costumers);
        
    printf("Actual Costumers i've found: %lu\n", getActualCostumers());
    Costumer result[getActualCostumers()];
    getAllCostumers(costumers, result);
}