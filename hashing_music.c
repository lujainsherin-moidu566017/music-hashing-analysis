/**
 * ============================================================================
 * Project Title : Music Application - Hashing and Search Performance Analysis
 * File Name     : hashing_music.c
 * Description   : Academic implementation of a Hash Table using the Division
 *                 Method with Linear Probing for collision resolution, and a
 *                 comparative performance analysis against Linear Search.
 * Author        : Student / Beginner Implementation
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10    /* Size of the Hash Table */
#define NUM_SONGS 8      /* Number of song IDs to insert */
#define NUM_SEARCHES 4   /* Number of search queries */
#define EMPTY -1         /* Sentinel value representing an empty slot */

/* Global Hash Table */
int hashTable[TABLE_SIZE];

/* Original Array of Song IDs (for Linear Search) */
int songIDs[NUM_SONGS] = {105, 210, 315, 420, 525, 630, 735, 840};

/* Search Keys to test */
int searchKeys[NUM_SEARCHES] = {105, 420, 840, 500};

/**
 * Hash Function using the Division Method:
 * h(key) = key % table_size
 */
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

/**
 * Initializes all slots of the Hash Table to EMPTY (-1).
 */
void initHashTable(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = EMPTY;
    }
}

/**
 * Displays the current state of the Hash Table.
 */
void displayHashTable(void) {
    printf("+-------+-------------+\n");
    printf("| Index |   Song ID   |\n");
    printf("+-------+-------------+\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] == EMPTY) {
            printf("|   %d   |    EMPTY    |\n", i);
        } else {
            printf("|   %d   |     %3d     |\n", i, hashTable[i]);
        }
    }
    printf("+-------+-------------+\n\n");
}

/**
 * Inserts a song ID into the Hash Table using Division Method
 * and Linear Probing for collision resolution.
 */
void insert(int key) {
    int initialIndex = hashFunction(key);
    int currentIndex = initialIndex;
    int probeCount = 0;
    int collisionDetected = 0;

    printf("------------------------------------------------------------\n");
    printf("Inserting Song ID : %d\n", key);
    printf("Initial Hash Index: h(%d) = %d %% %d = %d\n", key, key, TABLE_SIZE, initialIndex);

    /* Check if the initial position already has a collision */
    if (hashTable[initialIndex] != EMPTY) {
        collisionDetected = 1;
        printf("COLLISION DETECTED at index %d (Occupied by Song ID %d)!\n", 
               initialIndex, hashTable[initialIndex]);
        printf("Resolving collision using Linear Probing...\n");
    }

    /* Linear Probing sequence */
    while (hashTable[currentIndex] != EMPTY) {
        printf(" -> Checked index %d: OCCUPIED by Song ID %d\n", 
               currentIndex, hashTable[currentIndex]);
        probeCount++;
        currentIndex = (currentIndex + 1) % TABLE_SIZE;

        /* If we have checked all slots and returned to the start, table is full */
        if (probeCount == TABLE_SIZE) {
            printf("Error: Hash Table is full! Cannot insert Song ID %d.\n", key);
            return;
        }
    }

    if (collisionDetected) {
        printf(" -> Checked index %d: EMPTY slot found.\n", currentIndex);
        printf("Collision resolved after %d probe step(s).\n", probeCount);
    } else {
        printf("No collision. Slot %d is directly available.\n", currentIndex);
    }

    /* Insert the key into the empty slot */
    hashTable[currentIndex] = key;
    printf("Final Position: Song ID %d successfully inserted at Index [%d].\n\n", key, currentIndex);
}

/**
 * Searches for a song ID in the Hash Table using Linear Probing.
 * Returns the index if found, or -1 if not found.
 * Tracks the number of comparisons/probe operations in *comparisons.
 */
int hashSearch(int key, int *comparisons) {
    int initialIndex = hashFunction(key);
    int currentIndex = initialIndex;
    int probes = 0;

    printf("------------------------------------------------------------\n");
    printf("Hashing Search for Song ID: %d\n", key);
    printf("Initial Hash Index        : h(%d) = %d %% %d = %d\n", key, key, TABLE_SIZE, initialIndex);
    printf("Probe Path                : ");

    while (probes < TABLE_SIZE) {
        probes++;
        printf("[%d]", currentIndex);

        /* Case 1: Slot is empty -> Element does not exist in the table */
        if (hashTable[currentIndex] == EMPTY) {
            printf("\nSlot [%d] is EMPTY -> Search terminates.\n", currentIndex);
            *comparisons = probes;
            return -1;
        }

        /* Case 2: Slot contains the target key -> Found */
        if (hashTable[currentIndex] == key) {
            printf(" -> MATCH FOUND!\n");
            *comparisons = probes;
            return currentIndex;
        }

        /* Case 3: Slot contains a different key -> Continue probing */
        printf(" (Song %d) -> ", hashTable[currentIndex]);
        currentIndex = (currentIndex + 1) % TABLE_SIZE;
    }

    /* Checked all slots and wrapped around */
    printf("\nEntire table checked -> Element not found.\n");
    *comparisons = probes;
    return -1;
}

/**
 * Searches for a song ID using Linear Search on the original array.
 * Returns the index if found, or -1 if not found.
 * Tracks the number of element comparisons in *comparisons.
 */
int linearSearch(int arr[], int size, int key, int *comparisons) {
    *comparisons = 0;
    printf("------------------------------------------------------------\n");
    printf("Linear Search for Song ID : %d\n", key);
    printf("Comparison Sequence       : ");

    for (int i = 0; i < size; i++) {
        (*comparisons)++;
        printf("[Index %d: %d]", i, arr[i]);

        if (arr[i] == key) {
            printf(" -> MATCH FOUND!\n");
            return i;
        }

        if (i < size - 1) {
            printf(" -> ");
        }
    }

    printf(" -> END OF ARRAY\n");
    return -1;
}

int main(void) {
    printf("============================================================\n");
    printf("   MUSIC APPLICATION - HASHING & SEARCH PERFORMANCE ANALYSIS\n");
    printf("============================================================\n\n");

    /* Step 1: Configuration Details */
    printf("PROGRAM CONFIGURATION:\n");
    printf(" - Number of Song IDs to store : %d\n", NUM_SONGS);
    printf(" - Hash Table Size             : %d\n", TABLE_SIZE);
    printf(" - Hash Function               : h(key) = key %% %d\n", TABLE_SIZE);
    printf(" - Collision Resolution Policy : Linear Probing [ (h(key) + i) %% %d ]\n\n", TABLE_SIZE);

    /* Step 2: Initialize Table */
    initHashTable();
    printf("INITIAL HASH TABLE STATE (All %d slots empty):\n", TABLE_SIZE);
    displayHashTable();

    /* Step 3: Insert all 8 Song IDs */
    printf("============================================================\n");
    printf("PART A: INSERTION PROCESS (WITH COLLISION RESOLUTION)\n");
    printf("============================================================\n");

    for (int i = 0; i < NUM_SONGS; i++) {
        insert(songIDs[i]);
        printf("Hash Table State after inserting Song ID %d:\n", songIDs[i]);
        displayHashTable();
    }

    /* Step 4: Calculate and Display Load Factor */
    double loadFactor = (double)NUM_SONGS / TABLE_SIZE;
    printf("============================================================\n");
    printf("LOAD FACTOR CALCULATION:\n");
    printf("============================================================\n");
    printf("Load Factor (alpha) = Number of Stored Elements / Table Size\n");
    printf("                    = %d / %d\n", NUM_SONGS, TABLE_SIZE);
    printf("                    = %.2f (%.0f%% full)\n\n", loadFactor, loadFactor * 100.0);

    /* Step 5: Search Operations & Performance Comparison */
    printf("============================================================\n");
    printf("PART B: SEARCH PERFORMANCE ANALYSIS (HASHING vs LINEAR)\n");
    printf("============================================================\n\n");

    int hashComparisons[NUM_SEARCHES];
    int linearComparisons[NUM_SEARCHES];
    int hashResults[NUM_SEARCHES];
    int linearResults[NUM_SEARCHES];

    for (int i = 0; i < NUM_SEARCHES; i++) {
        int key = searchKeys[i];
        printf("\n>>> SEARCH TEST CASE %d: Target Song ID = %d <<<\n", i + 1, key);

        /* Perform Hash Search */
        hashResults[i] = hashSearch(key, &hashComparisons[i]);
        if (hashResults[i] != -1) {
            printf("Result: SUCCESS (Found at Hash Table Index %d in %d comparison(s))\n", 
                   hashResults[i], hashComparisons[i]);
        } else {
            printf("Result: FAILURE (Song ID %d NOT FOUND after %d comparison(s))\n", 
                   key, hashComparisons[i]);
        }

        /* Perform Linear Search */
        linearResults[i] = linearSearch(songIDs, NUM_SONGS, key, &linearComparisons[i]);
        if (linearResults[i] != -1) {
            printf("Result: SUCCESS (Found at Array Index %d in %d comparison(s))\n", 
                   linearResults[i], linearComparisons[i]);
        } else {
            printf("Result: FAILURE (Song ID %d NOT FOUND after %d comparison(s))\n", 
                   key, linearComparisons[i]);
        }
    }

    /* Step 6: Summary Comparison Table */
    printf("\n========================================================================================\n");
    printf("SEARCH PERFORMANCE COMPARISON TABLE\n");
    printf("========================================================================================\n");
    printf("| Search ID | Target Type   | Hashing Probes | Linear Comparisons | Faster Method       |\n");
    printf("+-----------+---------------+----------------+--------------------+---------------------+\n");

    int totalHashComps = 0;
    int totalLinearComps = 0;

    for (int i = 0; i < NUM_SEARCHES; i++) {
        int key = searchKeys[i];
        char *type = (hashResults[i] != -1) ? "Successful " : "Unsuccessful";
        char *winner;

        if (hashComparisons[i] < linearComparisons[i]) {
            winner = "Hashing is Faster  ";
        } else if (hashComparisons[i] > linearComparisons[i]) {
            winner = "Linear is Faster   ";
        } else {
            winner = "Tie (Equal)        ";
        }

        printf("|    %3d    | %s   |       %2d       |         %2d         | %s |\n",
               key, type, hashComparisons[i], linearComparisons[i], winner);

        totalHashComps += hashComparisons[i];
        totalLinearComps += linearComparisons[i];
    }
    printf("+-----------+---------------+----------------+--------------------+---------------------+\n");
    printf("| TOTAL     | -             |       %2d       |         %2d         | Hashing Won Overall |\n",
           totalHashComps, totalLinearComps);
    printf("| AVERAGE   | -             |      %4.2f      |        %4.2f        | Hashing Won Overall |\n",
           (double)totalHashComps / NUM_SEARCHES, (double)totalLinearComps / NUM_SEARCHES);
    printf("========================================================================================\n\n");

    /* Step 7: Final Conclusion Summary */
    printf("FINAL SUMMARY & OBSERVATIONS:\n");
    printf("1. Collisions occurred for 6 out of 8 insertions because all song IDs\n");
    printf("   end in 5 or 0, clustering at hash indices 5 and 0.\n");
    printf("2. Despite clustering, Hashing required only %d total comparisons versus\n", totalHashComps);
    printf("   %d comparisons for Linear Search across the 4 search test cases.\n", totalLinearComps);
    printf("3. Hashing achieved an average search cost of %.2f comparisons vs %.2f for Linear Search,\n",
           (double)totalHashComps / NUM_SEARCHES, (double)totalLinearComps / NUM_SEARCHES);
    printf("   proving Hashing is significantly more efficient for the music application.\n");
    printf("============================================================\n");

    return 0;
}
