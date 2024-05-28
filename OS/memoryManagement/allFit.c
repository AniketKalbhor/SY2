#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PROCESSES 4
#define MAX_SLOTS 5

int processRequirements[MAX_PROCESSES];
int availableMemory[MAX_SLOTS];
int isFinished[MAX_PROCESSES];

void initialize()
{
    for(int i = 0; i < MAX_PROCESSES; i++)
    {
        printf("Enter the memory requirement of process %d\n", i);
        scanf("%d", &processRequirements[i]);
    }

    for(int i = 0; i < MAX_SLOTS; i++)
    {
        printf("Enter the available memory in slot %d\n", i);
        scanf("%d", &availableMemory[i]);
    }
    
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        isFinished[i] = 0;
    }
}

void firstFit()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
        if (isFinished[i] == 0)
            for (int j = 0; j < MAX_SLOTS; j++)
                if (processRequirements[i] < availableMemory[j])
                {
                    printf("Process %d assigned to slot %d\n", i, j);
                    isFinished[i] = 1;
                    availableMemory[j] = availableMemory[j] - processRequirements[i];
                    break;
                }
    for(int i = 0; i < MAX_PROCESSES; i++)
        if(isFinished[i] == 0)
            printf("Memory can't be allocated for process %d\n", i);
}

int processSizes[MAX_PROCESSES];
int slotSizes[MAX_SLOTS];
int isProcessFinished[MAX_PROCESSES];

void worstFit()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (isProcessFinished[i] == 0)
        {
            int bestSlot = -1;
            int maxSize = INT_MIN;

            for (int j = 0; j < MAX_SLOTS; j++)
            {
                if (slotSizes[j] >= processSizes[i] && slotSizes[j] > maxSize)
                {
                    maxSize = slotSizes[j];
                    bestSlot = j;
                }
            }

            if (bestSlot != -1)
            {
                printf("Process %d assigned to slot %d\n", i, bestSlot);
                isProcessFinished[i] = 1;
                slotSizes[bestSlot] -= processSizes[i];
            }
            else
            {
                printf("Memory can't be allocated for process %d\n", i);
            }
        }
    }
}

int processFinished[MAX_PROCESSES];
int findBestSlot(int processSize)
{
    int bestSlot = -1;
    int minSize = INT_MAX;

    for (int j = 0; j < MAX_SLOTS; j++)
    {
        if (slotSizes[j] >= processSize && slotSizes[j] < minSize)
        {
            minSize = slotSizes[j];
            bestSlot = j;
        }
    }

    return bestSlot;
}

void allocateMemory()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (processFinished[i] == 0)
        {
            int bestSlot = findBestSlot(processSizes[i]);

            if (bestSlot != -1)
            {
                printf("Process %d assigned to slot %d\n", i, bestSlot);
                processFinished[i] = 1;
                slotSizes[bestSlot] -= processSizes[i];
            }
            else
            {
                printf("Memory can't be allocated for process %d\n", i);
            }
        }
    }
}

int processRequirements[MAX_PROCESSES];
int availableMemory[MAX_SLOTS];
int processCompletion[MAX_PROCESSES];
void nextFit()
{
    int currentSlot = 0; // Start from the first slot
    int completed = 0;

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (processCompletion[i] == 0)
        {
            while (currentSlot < MAX_SLOTS && completed < MAX_SLOTS)
            {
                if (processRequirements[i] <= availableMemory[currentSlot])
                {
                    printf("Process %d assigned to slot %d\n", i, currentSlot);
                    processCompletion[i] = 1;
                    availableMemory[currentSlot] -= processRequirements[i];
                    break;
                }

                currentSlot = (currentSlot + 1) % MAX_SLOTS; // Move to the next slot
                completed++;
            }
        }
    }

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (processCompletion[i] == 0)
        {
            printf("Memory can't be allocated for process %d\n", i);
        }
    }
}

int main()
{
    initialize();
    firstFit();
    printf("\n");
}
