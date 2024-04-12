#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
  int		id;
  char	name;
  int		order; 
};

struct HashNode 
{
  struct RecordType * record;
  struct HashNode * next;
};

// Fill out this structure
struct HashType
{

  struct HashNode * hashTable;
  int size_of_hash;

};

// Compute the hash function
int hash(int x, int hashSz)
{
  return x % hashSz;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
  FILE* inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  int i, n;
  char c;
  struct RecordType *pRecord;
  *ppData = NULL;

  if (inFile)
  {
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
    // Implement parse data block
    if (*ppData == NULL)
    {
      printf("Cannot allocate memory\n");
      exit(-1);
    }
    for (i = 0; i < dataSz; ++i)
    {
      pRecord = *ppData + i;
      fscanf(inFile, "%d ", &n);
      pRecord->id = n;
      fscanf(inFile, "%c ", &c);
      pRecord->name = c;
      fscanf(inFile, "%d ", &n);
      pRecord->order = n;
    }

    fclose(inFile);
  }

  return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
  int i;
  printf("\nRecords:\n");
  for (i = 0; i < dataSz; ++i)
  {
    printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
  }
  printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....

void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    if (pHashArray == NULL || pHashArray->hashTable == NULL) {
        return;
    }

    for (int i = 0; i < hashSz; ++i)
    {
        struct HashNode *current = pHashArray->hashTable[i].next;
        while (current != NULL)
        {
            printf("index %d -> id: %d, name: %c, order: %d\n", i, current->record->id, current->record->name, current->record->order);
            current = current->next;
        }
    }
}

// Read hash size from file
int readHashSizeFromFile(const char *fileName)
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    int hashSize;
    fscanf(file, "%d", &hashSize);
    fclose(file);
    return hashSize;
}

//Change nothing above^^
int main(void)
{
    int recordSz;
    struct RecordType *pRecords = NULL;
    recordSz = parseData("input.txt", &pRecords);

    int hashSize = readHashSizeFromFile("input.txt");
    struct HashType hashTable;
    hashTable.size_of_hash = hashSize;
    hashTable.hashTable = (struct HashNode *)malloc(sizeof(struct HashNode) * hashSize);
    if (hashTable.hashTable == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // Initialize hashTable
    for (int i = 0; i < hashSize; ++i) {
        hashTable.hashTable[i].record = NULL;
        hashTable.hashTable[i].next = NULL;
    }

    // Insert records into hash table
    for (int i = 0; i < recordSz; ++i) {
        int index = hash(pRecords[i].id, hashSize);
        struct HashNode *newNode = (struct HashNode *)malloc(sizeof(struct HashNode));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->record = &pRecords[i];
        newNode->next = hashTable.hashTable[index].next;
        hashTable.hashTable[index].next = newNode;
    }

    // Display records in the hash table
    displayRecordsInHash(&hashTable, hashSize);

    // Free allocated memory
    
    free(pRecords);
    for (int i = 0; i < hashSize; ++i) {
        struct HashNode *current = hashTable.hashTable[i].next;
        while (current != NULL) {
            struct HashNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable.hashTable);

    return 0;
}
