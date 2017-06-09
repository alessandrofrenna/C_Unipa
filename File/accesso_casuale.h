typedef struct clientData Costumer;

FILE * openFile (char *, char *);
bool initDefaultFile(FILE *);
unsigned int insertCostumer(Costumer, size_t, FILE *);
void setMaxCostumers(unsigned long int);
unsigned long int getMaxCostumers();
void setActualFileCostumers(FILE *); 
unsigned long int getActualCostumers();
void getAllCostumers(FILE *, Costumer *);