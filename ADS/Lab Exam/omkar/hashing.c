#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10
struct HashElement
{
    int key;
    int data;
};
struct HashTable
{
    struct HashElement table[TABLE_SIZE];
};
void initializeHashTable(struct HashTable *hashTable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable->table[i].key = -1;
    }
}

int linearProbingHash(int key, int attempt)
{
    return (key + attempt) % TABLE_SIZE;
}

int quadraticProbingHash(int key, int attempt)
{
    return (key + attempt * attempt) % TABLE_SIZE;
}

int doubleHashingHash(int key, int attempt)
{
    int secondHash = 3;
    return (key + attempt * secondHash) % TABLE_SIZE;
}

int insertLinearProbing(struct HashTable *hashTable, int key, int data)
{
    int attempt = 0;
    int index;

    do
    {
        index = linearProbingHash(key, attempt);
        if (hashTable->table[index].key == -1)
        {
            hashTable->table[index].key = key;
            hashTable->table[index].data = data;
            return attempt;
        }

        attempt++;
    } while (attempt < TABLE_SIZE);

    return -1;
}

int insertQuadraticProbing(struct HashTable *hashTable, int key, int data)
{
    int attempt = 0;
    int index;

    do
    {
        index = quadraticProbingHash(key, attempt);

        if (hashTable->table[index].key == -1)
        {
            hashTable->table[index].key = key;
            hashTable->table[index].data = data;
            return attempt;
        }

        attempt++;
    } while (attempt < TABLE_SIZE);

    return -1;
}

int insertDoubleHashing(struct HashTable *hashTable, int key, int data)
{
    int attempt = 0;
    int index;

    do
    {
        index = doubleHashingHash(key, attempt);

        if (hashTable->table[index].key == -1)
        {
            hashTable->table[index].key = key;
            hashTable->table[index].data = data;
            return attempt;
        }

        attempt++;
    } while (attempt < TABLE_SIZE);

    return -1;
}

void displayHashTable(struct HashTable *hashTable)
{
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable->table[i].key != -1)
        {
            printf("Index %d: Key=%d, Data=%d\n", i, hashTable->table[i].key, hashTable->table[i].data);
        }
        else
        {
            printf("Index %d: Empty\n", i);
        }
    }
}

int main()
{
    struct HashTable linearProbingTable, quadraticProbingTable, doubleHashingTable;
    initializeHashTable(&linearProbingTable);
    initializeHashTable(&quadraticProbingTable);
    initializeHashTable(&doubleHashingTable);

    // int data[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int data[] = {11, 21, 12, 31};
    int dataSize = sizeof(data) / sizeof(data[0]);

    // Insert data into hash tables using different probing techniques
    int linearCollisions = 0, quadraticCollisions = 0, doubleHashingCollisions = 0;

    for (int i = 0; i < dataSize; i++)
    {
        linearCollisions += insertLinearProbing(&linearProbingTable, data[i], data[i]);
        quadraticCollisions += insertQuadraticProbing(&quadraticProbingTable, data[i], data[i]);
        doubleHashingCollisions += insertDoubleHashing(&doubleHashingTable, data[i], data[i]);
    }

    // Display the contents of hash tables
    printf("\nLinear Probing:\n");
    displayHashTable(&linearProbingTable);
    printf("Collisions: %d\n", linearCollisions);

    printf("\nQuadratic Probing:\n");
    displayHashTable(&quadraticProbingTable);
    printf("Collisions: %d\n", quadraticCollisions);

    printf("\nDouble Hashing:\n");
    displayHashTable(&doubleHashingTable);
    printf("Collisions: %d\n", doubleHashingCollisions);

    return 0;
}
