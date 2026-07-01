// FUNC_NAME: EntityManager::collectFarEntities
// Function at 0x00967950 - Builds a list of entity indices whose distance/priority exceeds a threshold.
// Loops over 20 entity slots, checks each via isEntityRelevant(), and stores qualifying indices in a global array.

// External globals (likely class statics or module globals)
extern int g_numFarEntities;                     // DAT_011308b6 - count of far entities found
extern float g_farDistanceThreshold;             // DAT_00e44598 - threshold for distance/priority
extern unsigned char g_farEntityIndices[20];      // DAT_011308a0 - array of 20 indices
extern int* g_entitySlotArray[20];               // DAT_00d8dca0 - array of 20 pointers to entity objects (size 0x14)
// caller: FUN_009710e0 (likely part of same class)

// Forward declaration of helper function (at 0x008934e0)
bool isEntityRelevant(int* entitySlot, float* outValue); // returns true if entity should be considered, and sets *outValue

void collectFarEntities(void)
{
    char isRelevant;
    unsigned int index;
    unsigned int currentCount;
    int** slotPtr;

    g_numFarEntities = 0;
    slotPtr = &g_entitySlotArray[0];
    index = 0;
    do
    {
        float value = 0.0f;
        isRelevant = isEntityRelevant(*slotPtr, &value); // +0x00: call to get distance/relevance
        if ((isRelevant != '\0') && (g_farDistanceThreshold < value))
        {
            currentCount = (unsigned int)g_numFarEntities;
            g_numFarEntities = g_numFarEntities + 1;
            g_farEntityIndices[currentCount] = (unsigned char)index;
        }
        index = index + 1;
        slotPtr = slotPtr + 1; // advance by 4 bytes (int32 pointer)
    } while (index < 0x14); // 20 iterations
    return;
}