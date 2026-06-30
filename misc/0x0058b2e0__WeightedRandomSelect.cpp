// FUNC_NAME: WeightedRandomSelect
// Address: 0x0058b2e0
// Role: Weighted random selection from a list of items, with optional exclusion of one index.
// Uses a random state (global or per-instance) and an array of weights.

struct RandomState {
    uint8_t flags[0x14]; // +0x13 bit 0 controls per-instance vs global randomness
    uint32_t counter;    // +0x2d4 internal counter if per-instance
};

struct WeightedItem {
    // unknown fields
    float weight; // +0x8
};

struct WeightedList {
    int field_0;                // +0x0 (unused)
    short* countAndFlag;       // +0x4 pointer to array: [count, ?, flag] (short at +0, flag at +2)
    int field_8;               // +0x8 (unused)
    WeightedItem* items[];     // +0xC actually starts at param_2[3] (offset 12 bytes)
};

struct DynamicWeightArray {
    float* data;   // +0x0
    int capacity;  // +0x4
};

// Global random counter
static uint32_t g_globalCounter = 0;
// Global random table (likely precomputed floats in [0,1))
extern float g_randomTable[/* size */]; // &DAT_010c2680
extern uint32_t g_randomTableSize;      // DAT_010c2678

int __cdecl WeightedRandomSelect(RandomState* randomState, WeightedList* list, DynamicWeightArray* weightArray) {
    // Extract count and flag from the list's countAndFlag pointer
    short* countPtr = (short*)list->countAndFlag;
    short count = *countPtr;
    short skipFlag = countPtr[2]; // if ==1, skip index from weight array

    // Ensure weight array capacity is large enough; if not, resize
    if ((uint32_t)weightArray->capacity <= (uint32_t)count) {
        // Resize (FUN_00591c00)
        weightArray->capacity = 0; // placeholder
        // Actually calls a reallocation function; we omit the implementation
    }

    float totalWeight = 0.0f;
    // Read the index to exclude from the weight array (stored as float at offset count)
    int excludeIndex = (int)*(float*)(weightArray->data + count); // sVar1 = count

    WeightedItem** itemsPtr = &list->items[0];
    int i = 0;

    if (skipFlag == 1) {
        // Accumulate total weight, skipping the excluded index
        if (count > 3) {
            int numQuads = (count - 4) / 4;
            for (int q = 0; q < numQuads; q++) {
                if (i != excludeIndex) totalWeight += itemsPtr[0]->weight;
                if (i+1 != excludeIndex) totalWeight += itemsPtr[1]->weight;
                if (i+2 != excludeIndex) totalWeight += itemsPtr[2]->weight;
                if (i+3 != excludeIndex) totalWeight += itemsPtr[3]->weight;
                i += 4;
                itemsPtr += 4;
            }
        }
        for (; i < count; i++) {
            if (i != excludeIndex) {
                totalWeight += itemsPtr[0]->weight;
            }
            itemsPtr++;
        }
    } else {
        // Accumulate all weights
        if (count > 3) {
            int numQuads = (count - 4) / 4;
            for (int q = 0; q < numQuads; q++) {
                totalWeight += itemsPtr[0]->weight + itemsPtr[1]->weight + itemsPtr[2]->weight + itemsPtr[3]->weight;
                i += 4;
                itemsPtr += 4;
            }
        }
        for (; i < count; i++) {
            totalWeight += itemsPtr[0]->weight;
            itemsPtr++;
        }
    }

    // Compute a random number
    uint32_t randIndex;
    if (randomState != nullptr && (randomState->flags[0x13] & 1)) {
        randIndex = (randomState->counter + 1) & (g_randomTableSize - 1);
        randomState->counter = randIndex;
    } else {
        randIndex = g_globalCounter & (g_randomTableSize - 1);
        g_globalCounter++;
    }

    float threshold = g_randomTable[randIndex] * totalWeight;

    // Second pass: accumulate cumulative weight until threshold exceeded
    i = 0;
    float cumulativeWeight = 0.0f;
    itemsPtr = &list->items[0];

    if (skipFlag == 1) {
        for (; i < count; i++) {
            if (i != excludeIndex) {
                cumulativeWeight += itemsPtr[0]->weight;
            }
            if (threshold < cumulativeWeight) {
                return i;
            }
            itemsPtr++;
        }
    } else {
        for (; i < count; i++) {
            cumulativeWeight += itemsPtr[0]->weight;
            if (threshold < cumulativeWeight) {
                return i;
            }
            itemsPtr++;
        }
    }

    return 0;
}