// FUNC_NAME: EntityManager::removeEntityByID

// Function removes an entity with given ID from one of two storage lists.
// Each list holds 0x20-byte entries indexed by short counts.
// +0xA0 : pointer to primary list array
// +0xA4 : pointer to secondary list array
// +0xA8 : short count of primary list
// +0xAA : short count of secondary list
void __thiscall EntityManager::removeEntityByID(int thisPtr, int entityID)
{
    int primaryCount = *(short*)(thisPtr + 0xA8);
    int secondaryCount;
    int i;
    int* primaryList = *(int**)(thisPtr + 0xA0);
    int* secondaryList;
    undefined8* src;
    undefined8* dst;

    // Search primary list
    for (i = 0; i < primaryCount; i++)
    {
        if (primaryList[i * 8] == entityID)   // first int of entry is ID
        {
            if ((primaryCount > 1) && (i != primaryCount - 1))
            {
                // Move last entry to this position
                dst = (undefined8*)(primaryList + i * 8);
                src = (undefined8*)(primaryList + (primaryCount - 1) * 8);
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
                dst[3] = src[3];
            }
            *(short*)(thisPtr + 0xA8) = primaryCount - 1;
            compactList(*(int*)(thisPtr + 0xA0), primaryCount - 1);
            return;
        }
    }

    // Search secondary list
    secondaryCount = *(short*)(thisPtr + 0xAA);
    secondaryList = *(int**)(thisPtr + 0xA4);
    for (i = 0; i < secondaryCount; i++)
    {
        if (secondaryList[i * 8] == entityID)
        {
            if ((secondaryCount > 1) && (i != secondaryCount - 1))
            {
                // Move last entry to this position
                dst = (undefined8*)(secondaryList + i * 8);
                src = (undefined8*)(secondaryList + (secondaryCount - 1) * 8);
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
                dst[3] = src[3];
            }
            *(short*)(thisPtr + 0xAA) = secondaryCount - 1;
            compactList(*(int*)(thisPtr + 0xA4), secondaryCount - 1);
            return;
        }
    }
}

// Helper function called after removal to compact the list (e.g., realloc or null-terminate)
// Defined elsewhere; assumed to take (int* array, int newCount)
void __thiscall EntityManager::compactList(int* listArray, int newCount);