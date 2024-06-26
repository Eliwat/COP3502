#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct trieNode
{	
char word[100];
int count;
struct trieNode* child[26];
};

// Initializes a trie structure
struct trieNode *create_Trie()
{
  struct trieNode* newNode = (struct trieNode*)malloc(sizeof(struct trieNode));
  if (newNode) {
      newNode->count = 0;
      for (int i = 0; i < 26; i++)
          newNode->child[i] = NULL;
  }
  return newNode;
}

// Inserts the word to the trie structure
void insert(struct trieNode *pTrie, char *word)
{
  struct trieNode* current = pTrie;
  for (int i = 0; word[i] != '\0'; i++) {
      int index = word[i] - 'a';
      if (!current->child[index])
          current->child[index] = create_Trie();
      current = current->child[index];
  }
  strcpy(current->word, word);
  current->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct trieNode *pTrie, char *word)
{
  struct trieNode* current = pTrie;
      for (int i = 0; word[i] != '\0'; i++) {
          int index = word[i] - 'a';
          if (!current->child[index])
              return 0;
          current = current->child[index];
      }
      return (current && strcmp(current->word, word) == 0) ? current->count : 0;
  }


// deallocate the trie structure
// Deallocates memory allocated for the Trie
struct trieNode* deallocateTrie(struct trieNode *pTrie) {
  if(pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            if (pTrie->child[i])
                deallocateTrie(pTrie->child[i]);
        }
        free(pTrie);
  }
  return NULL;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
  FILE* file = fopen(filename, "r");
  if (!file) {
      printf("Error opening file.\n");
      return 0;
  }
  int numWords = 0;
  char word[100];
  while (fscanf(file, "%s", word) != EOF) {
      pInWords[numWords] = (char*)malloc((strlen(word) + 1) * sizeof(char));
      strcpy(pInWords[numWords], word);
      numWords++;
  }
  fclose(file);
  return numWords;
}

int main(void)
{
  char *inWords[256];

  //read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i=0;i<numWords;++i)
  {
    printf("%s\n",inWords[i]);
  }

  struct trieNode *pTrie = create_Trie();
  for (int i=0;i<numWords;i++)
  {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i=0;i<5;i++)
  {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}
