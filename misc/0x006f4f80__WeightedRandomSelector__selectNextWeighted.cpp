// FUNC_NAME: WeightedRandomSelector::selectNextWeighted
// Function address: 0x006f4f80
// Purpose: Perform weighted random selection from an array of items, excluding the last selected item.
// Uses temporary cumulative weight array allocated via allocateWeightArray.
// The random selection uses rand() with a scaling factor DAT_00e44590 (likely 1.0f/32767.0f).
// Item structure: [uint32_t id (0xFF = invalid), float weight, uint8_t pad[8]]

#include <cstdlib>
#include <cstdint>

// External helpers
extern float* allocateWeightArray(uint32_t count);
extern const float DAT_00e44590; // Reciprocal of RAND_MAX

struct WeightedItem {
    uint32_t id;      // +0x00, 0xFF marks invalid
    float    weight;  // +0x04
    // +0x08 – +0x0C unused (8 bytes padding)
};

// Member function __fastcall (this in ECX)
int __fastcall WeightedRandomSelector::selectNextWeighted(void* thisPtr)
{
    // +0x18: pointer to a structure containing item count at offset +4
    uint32_t count = *(uint32_t*)(*(int32_t*)((uint8_t*)thisPtr + 0x18) + 4);
    // +0x1c: pointer to array of WeightedItem (16 bytes each)
    WeightedItem* items = *(WeightedItem**)((uint8_t*)thisPtr + 0x1c);
    // +0x14: last selected index (to be excluded)
    uint32_t lastIndex = *(uint32_t*)((uint8_t*)thisPtr + 0x14);

    float sumWeights = 0.0f;
    uint32_t resultIndex = 0;

    if (count == 0) {
        return 0;
    }
    if (count == 1) {
        // Only one item, return it directly
        return (int)&items[0];
    }

    float* cumulativeWeights = allocateWeightArray(count);
    if (cumulativeWeights == nullptr) {
        return 0;
    }

    // Build cumulative weight array, excluding the item that was last selected
    sumWeights = 0.0f;
    for (uint32_t i = 0; i < count; ++i) {
        if (i == lastIndex || items[i].id >= 0xFF) {
            // Exclude last selected item or invalid entries
            cumulativeWeights[i] = 0.0f;
        } else {
            // (Compiler-inserted delay loops omitted for clarity)
            // The original code contained empty timing loops here.
            sumWeights += items[i].weight;
            cumulativeWeights[i] = items[i].weight;
        }
    }

    // Generate a random float in [0, sumWeights)
    float randomValue = (float)rand() * DAT_00e44590 * sumWeights;

    // Unrolled loop: process 4 items at a time for performance
    uint32_t remaining = count - 1;
    uint32_t i = 0;
    if (remaining > 3) {
        float* cumPtr = cumulativeWeights + 2; // start at index 2
        WeightedItem* itemPtr = items + 2;      // start at index 2
        do {
            // Check items i, i+1, i+2, i+3
            if (itemPtr[-2].id < 0xFF) {
                randomValue -= cumPtr[-2];
                if (randomValue < 0.0f) goto found;
            }
            if (itemPtr[-1].id < 0xFF) {
                randomValue -= cumPtr[-1];
                if (randomValue < 0.0f) { i += 1; goto found; }
            }
            if (itemPtr->id < 0xFF) {
                randomValue -= cumPtr[0];
                if (randomValue < 0.0f) { i += 2; goto found; }
            }
            if (itemPtr[1].id < 0xFF) {
                randomValue -= cumPtr[1];
                if (randomValue < 0.0f) { i += 3; goto found; }
            }
            i += 4;
            itemPtr += 4;
            cumPtr += 4;
        } while (i < count - 4);
    }

    // Process remaining items (up to 3)
    WeightedItem* remainingItem = items + i;
    while (i < remaining) {
        if (remainingItem->id < 0xFF) {
            randomValue -= cumulativeWeights[i];
            if (randomValue < 0.0f) break;
        }
        ++i;
        ++remainingItem;
    }

found:
    // Store the selected index and return pointer to the selected item
    *(uint32_t*)((uint8_t*)thisPtr + 0x14) = i;
    return (int)(items + i);
}