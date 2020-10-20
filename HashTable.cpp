#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable(int s)
{
    size = s;
    hashTable = new list<WordEntry>[size];
}

/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(string s)
{
    int value = 0;
    for (auto c : s)
    {
        value += (int)c;
    }
    return value % size;
}

/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(string s, int score)
{
    int index = computeHash(s);
    auto iterator = hashTable[index].begin();
    bool exists = false;
    while (iterator != hashTable[index].end())
    {
        if (iterator->getWord() == s)
        {
            iterator->addNewAppearance(score);
            exists = true;
            break;
        }
        iterator++;
    }
    if (!exists)
    {
        hashTable[index].push_back(WordEntry(s, score));
    }
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(string s)
{
    double avg = 2.0;
    int index = computeHash(s);
    auto iterator = hashTable[index].begin();
    while (iterator != hashTable[index].end())
    {
        if (iterator->getWord() == s)
        {
            avg = iterator->getAverage();
            break;
        }
        iterator++;
    }
    return avg;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(string s)
{
    int index = computeHash(s);
    auto iterator = hashTable[index].begin();
    bool exists = false;
    while (iterator != hashTable[index].end())
    {
        if (iterator->getWord() == s)
        {
            exists = true;
            break;
        }
        iterator++;
    }
    return exists;
}
