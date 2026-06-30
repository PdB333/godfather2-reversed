// FUNC_NAME: PriorityQueue::updateItems
// Function address: 0x00554270
// This function appears to be part of a priority queue or task scheduler.
// It merges incoming items from param_2 and param_3 into an internal sorted container,
// then processes items based on distance criteria and extracts items of type 1 and 2 into separate lists.

#include <cstdint>

// Forward declaration for TLS heap manager
struct TLSHeapManager {
    // unknown
};

extern TLSHeapManager* g_tlsManager; // at 0x01139810

// External functions (renamed based on behavior)
float getDistance(); // FUN_005540a0 - returns a float, likely distance or some metric
int findItemIndex(void* container, const int* item); // FUN_00554200 - searches for an item, returns index or -1
void* heapAlloc(int size); // FUN_009f2410? or similar
void heapFree(void* ptr); // FUN_00aa26e0
void growArray(int* arrayPtr, int elementSize); // FUN_00aa4190
void addToList1(void* list1, int item); // FUN_009f2330
void addToList2(void* list2, int item); // FUN_00a0df80

// Item structure (0x30 = 48 bytes)
struct Item {
    int field0;
    int field4;
    int field8;
    int fieldC;
    int field10;
    int field14;
    int field18;
    int field1C;
    int field20;
    int field24;
    int* objectPtr; // +0x28 - pointer to an object
    int field2C;
};

// Object structure (pointed by objectPtr)
struct BaseObject {
    uint8_t unknown[0x10];
    uint8_t derivedOffset; // +0x10
    uint8_t typeFlag;      // +0x18: 1 or 2
    // ... rest of object
};

class PriorityQueue {
public:
    // Internal fields
    // +0x00: vtable? Not used here
    // +0x04-0x07: unknown
    // +0x08: list1 management? (FUN_009f2410 called on this+8)
    // +0x10: list2 management? (FUN_00a0dec0 called on this+0xc)
    // +0x58: reference float (e.g., distance threshold)
    // +0x68: itemCount (number of items in container)
    // +0x6c: itemCapacity (masked with 0x3fffffff)
    // +0x70: callbackArray (array of function pointers)
    // +0x74: callbackCount
    // +0x7c: list1 pointer (type1 objects)
    // +0x80: list1 count
    // +0x84: list1 capacity (mask)
    // +0x88: list2 pointer (type2 objects)
    // +0x8c: list2 count
    // +0x90: list2 capacity (mask)
    // +0x94: unknown

    void updateItems(const void* source1, const void* source2) {
        // Source1 and source2 are containers with:
        // +0x10: pointer to array of Items
        // +0x14: number of items

        int* tlsHeap = (int*)TlsGetValue(g_tlsManager);
        int tempHeapBase = tlsHeap[8]; // current heap offset
        int numItemsSource1 = *(int*)((uint8_t*)source1 + 0x14);
        int totalCopySize = numItemsSource1 * 0x30 + 0x10; // extra 0x10 for alignment?

        // Allocate temporary space on TLS heap
        int newHeapPos;
        if ((uint32_t)tlsHeap[0xb] < (uint32_t)(tempHeapBase + totalCopySize)) {
            newHeapPos = (int)((code*)tlsHeap[0] + 0x14)(totalCopySize); // custom alloc
        } else {
            tlsHeap[8] = tempHeapBase + totalCopySize;
            newHeapPos = tempHeapBase;
        }

        // Copy items from source1 to temporary buffer (with some weird offset +0x48, -0x18, etc.)
        // This appears to be a vectorized copy with stride 0x30, but the addresses are offset.
        // We'll simplify: copy items normally.
        int* srcArray = *(int**)((uint8_t*)source1 + 0x10);
        int* dst = (int*)(newHeapPos + 0x18); // destination starts at +0x18?
        for (int i = 0; i < numItemsSource1; i++) {
            for (int j = 0; j < 12; j++) { // 12 ints per item
                dst[j] = *(srcArray + j);
            }
            srcArray += 12;
            dst += 12;
        }

        // Now process existing items in this container (at +0x68 count)
        int itemCount = *(int*)((uint8_t*)this + 0x68);
        int* itemArray = *(int**)((uint8_t*)this + 0x64); // +0x64? Actually +0x60? Wait, we don't have pointer field; item array is at +0x100? Not in this function.
        // The code uses offset +0x100? No, it uses *(int*)(this+100) for itemArray. So +0x64 = 100? Actually 0x64 = 100. So the item array pointer is at this+0x64 (100).
        // But the decompilation shows *(int *)(param_1 + 100) = +0x64.
        int* itemArrayPtr = *(int**)((uint8_t*)this + 0x64);

        // Loop over existing items in reverse (from last to first)
        for (int i = itemCount - 1; i >= 0; i--) {
            int* currentItem = itemArrayPtr + i * 12; // 12 ints per item
            int bestMatchIndex = -1;
            float bestDistance = 99999.0f; // from DAT_00e445a4
            int numSrcItems = numItemsSource1;

            // Check if source1 is empty, then handle this item specially (remove it)
            if (numSrcItems < 1) {
                // Remove this item by calling callbacks with destructor (vtable+8)
                int callbackCount = *(int*)((uint8_t*)this + 0x74);
                int* callbackArray = *(int**)((uint8_t*)this + 0x70);
                for (int c = 0; c < callbackCount; c++) {
                    ((void (*)(int*))(*((int**)callbackArray[c]) + 8))(currentItem);
                }
                // Decrease count and move last item to this slot
                itemCount--;
                int* lastItem = itemArrayPtr + itemCount * 12;
                for (int j = 0; j < 12; j++) {
                    currentItem[j] = lastItem[j];
                }
                continue;
            }

            // Search for a matching item in source1 based on distance
            for (int s = 0; s < numSrcItems; s++) {
                int* srcItem = (int*)(newHeapPos + 0x18 + s * 12); // source items in temp buffer
                float dist = getDistance(); // FUN_005540a0
                if (dist < bestDistance) {
                    bestMatchIndex = s;
                    bestDistance = dist;
                }
            }

            if (bestMatchIndex < 0) {
                // No match, remove this item
                int callbackCount = *(int*)((uint8_t*)this + 0x74);
                int* callbackArray = *(int**)((uint8_t*)this + 0x70);
                for (int c = 0; c < callbackCount; c++) {
                    ((void (*)(int*))(*((int*)callbackArray[c] + 8)))(currentItem);
                }
                itemCount--;
                int* lastItem = itemArrayPtr + itemCount * 12;
                for (int j = 0; j < 12; j++) {
                    currentItem[j] = lastItem[j];
                }
            } else {
                int* bestSrcItem = (int*)(newHeapPos + 0x18 + bestMatchIndex * 12);
                // Compare object pointers (field at index 10)
                int* obj1 = (int*)currentItem[10];
                int* obj2 = (int*)bestSrcItem[10];
                int derivedPtr1 = 0;
                int derivedPtr2 = 0;
                if (*((uint8_t*)obj1 + 0x18) == 1) {
                    derivedPtr1 = (int)(uint8_t)(*((uint8_t*)obj1 + 0x10)) + (int)obj1;
                }
                if (*((uint8_t*)obj2 + 0x18) == 1) {
                    derivedPtr2 = (int)(uint8_t)(*((uint8_t*)obj2 + 0x10)) + (int)obj2;
                }
                if (derivedPtr1 != derivedPtr2) {
                    // Different types, need to swap callbacks
                    int callbackCount = *(int*)((uint8_t*)this + 0x74);
                    int* callbackArray = *(int**)((uint8_t*)this + 0x70);
                    // Remove old item (destructor +8)
                    for (int c = 0; c < callbackCount; c++) {
                        ((void (*)(int*))(*((int*)callbackArray[c] + 8)))(currentItem);
                    }
                    // Insert new item (constructor +4)
                    for (int c = 0; c < callbackCount; c++) {
                        ((void (*)(int*))(*((int*)callbackArray[c] + 4)))(bestSrcItem);
                    }
                }
                // Copy bestSrcItem to currentItem
                for (int j = 0; j < 12; j++) {
                    currentItem[j] = bestSrcItem[j];
                }
                // Remove bestSrcItem from source list by moving last item to its place
                numSrcItems--;
                int* lastSrcItem = (int*)(newHeapPos + 0x18 + numSrcItems * 12);
                for (int j = 0; j < 12; j++) {
                    bestSrcItem[j] = lastSrcItem[j];
                }
            }
        }

        // After processing existing items, update the itemCount
        *(int*)((uint8_t*)this + 0x68) = itemCount;

        // Now process remaining new items from source1 (those not matched)
        int remainingSrcItems = numSrcItems; // update after loop
        for (int i = 0; i < remainingSrcItems; i++) {
            int* newItem = (int*)(newHeapPos + 0x18 + i * 12);
            int* obj = (int*)newItem[10];
            bool skip = false;
            if (obj && *((uint8_t*)obj + 0x18) == 1) {
                int derivedPtr = (int)(uint8_t)(*((uint8_t*)obj + 0x10)) + (int)obj;
                if (derivedPtr) {
                    float distSq = *(float*)(derivedPtr + 0x1a0) * *(float*)(derivedPtr + 0x1a0) +
                                   *(float*)(derivedPtr + 0x1a4) * *(float*)(derivedPtr + 0x1a4) +
                                   *(float*)(derivedPtr + 0x1a8) * *(float*)(derivedPtr + 0x1a8);
                    if (distSq <= some_epsilon) { // DAT_00e2b05c
                        skip = true;
                    }
                    if (*((uint8_t*)(derivedPtr + 0xd8)) != 6) {
                        skip = true;
                    }
                } else {
                    skip = true;
                }
            } else {
                skip = true;
            }

            // Check distance from some reference point (this+0x58)
            float diff = (float)newItem[1] - *(float*)((uint8_t*)this + 0x58);
            float threshold = some_threshold; // DAT_00e44598

            if (diff < threshold && !skip) {
                int searchResult = findItemIndex(this, newItem - 6); // FUN_00554200
                if (searchResult < 0) {
                    // Add new item to container
                    int callbackCount = *(int*)((uint8_t*)this + 0x74);
                    int* callbackArray = *(int**)((uint8_t*)this + 0x70);
                    for (int c = 0; c < callbackCount; c++) {
                        ((void (*)(int*))(*((int*)callbackArray[c] + 4)))(newItem - 6);
                    }
                    // Grow if necessary
                    if ((uint32_t)itemCount == (*(uint32_t*)((uint8_t*)this + 0x6c) & 0x3fffffff)) {
                        growArray((int*)((uint8_t*)this + 0x64), 0x30);
                    }
                    int* dest = itemArrayPtr + itemCount * 12;
                    for (int j = 0; j < 12; j++) {
                        dest[j] = newItem[j - 6]; // Note the offset
                    }
                    itemCount++;
                }
            }
        }

        // Process source2 (similar logic)
        int numItemsSource2 = *(int*)((uint8_t*)source2 + 0x14);
        if (numItemsSource2 > 0) {
            int* src2Array = *(int**)((uint8_t*)source2 + 0x10);
            int searchIdx = findItemIndex(this, src2Array);
            if (searchIdx == -1) {
                // Add
                int callbackCount = *(int*)((uint8_t*)this + 0x74);
                int* callbackArray = *(int**)((uint8_t*)this + 0x70);
                for (int c = 0; c < callbackCount; c++) {
                    ((void (*)(int*))(*((int*)callbackArray[c] + 4)))(src2Array);
                }
                if ((uint32_t)itemCount == (*(uint32_t*)((uint8_t*)this + 0x6c) & 0x3fffffff)) {
                    growArray((int*)((uint8_t*)this + 0x64), 0x30);
                }
                int* dest = itemArrayPtr + itemCount * 12;
                for (int j = 0; j < 12; j++) {
                    dest[j] = src2Array[j];
                }
                itemCount++;
            } else {
                // Update existing item
                int* existingItem = itemArrayPtr + searchIdx * 12;
                int* obj2 = (int*)src2Array[10];
                int derived2 = 0;
                if (*((uint8_t*)obj2 + 0x18) == 1) {
                    derived2 = (int)(uint8_t)(*((uint8_t*)obj2 + 0x10)) + (int)obj2;
                }
                int* obj1 = (int*)existingItem[10];
                int derived1 = 0;
                if (*((uint8_t*)obj1 + 0x18) == 1) {
                    derived1 = (int)(uint8_t)(*((uint8_t*)obj1 + 0x10)) + (int)obj1;
                }
                if (derived2 != derived1) {
                    int callbackCount = *(int*)((uint8_t*)this + 0x74);
                    int* callbackArray = *(int**)((uint8_t*)this + 0x70);
                    // Remove old
                    for (int c = 0; c < callbackCount; c++) {
                        ((void (*)(int*))(*((int*)callbackArray[c] + 8)))(existingItem);
                    }
                    // Insert new
                    for (int c = 0; c < callbackCount; c++) {
                        ((void (*)(int*))(*((int*)callbackArray[c] + 4)))(src2Array);
                    }
                }
                for (int j = 0; j < 12; j++) {
                    existingItem[j] = src2Array[j];
                }
            }
        }

        // Bubble sort container items based on distance (ascending)
        for (int i = itemCount - 1; i > 0; i--) {
            for (int j = 0; j < i; j++) {
                int* itemA = itemArrayPtr + j * 12;
                int* itemB = itemArrayPtr + (j+1) * 12;
                float distA = getDistance();
                if (distA <= some_distance_threshold) { // DAT_00e2b334
                    // If itemA is within threshold, remove itemA
                    int callbackCount = *(int*)((uint8_t*)this + 0x74);
                    int* callbackArray = *(int**)((uint8_t*)this + 0x70);
                    for (int c = 0; c < callbackCount; c++) {
                        ((void (*)(int*))(*((int*)callbackArray[c] + 8)))(itemA);
                    }
                    itemCount--;
                    // Move last item to this slot
                    int* lastItem = itemArrayPtr + itemCount * 12;
                    for (int k = 0; k < 12; k++) {
                        itemA[k] = lastItem[k];
                    }
                    i = itemCount; // restart? Actually, the loop continues with new i
                }
            }
        }

        // Extract items with type 1 into list1 and type 2 into list2
        for (int i = 0; i < itemCount; i++) {
            int* item = itemArrayPtr + i * 12;
            int* obj = (int*)item[10];
            if (obj && *((uint8_t*)obj + 0x18) == 1) {
                int derivedPtr = (int)(uint8_t)(*((uint8_t*)obj + 0x10)) + (int)obj;
                if (derivedPtr) {
                    // Check if already in list1
                    int* list1 = *(int**)((uint8_t*)this + 0x7c);
                    int list1Count = *(int*)((uint8_t*)this + 0x80);
                    bool found = false;
                    for (int j = 0; j < list1Count; j++) {
                        if (list1[j] == derivedPtr) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        addToList1(this + 8, derivedPtr); // FUN_009f2330
                        if ((uint32_t)list1Count == (*(uint32_t*)((uint8_t*)this + 0x84) & 0x3fffffff)) {
                            growArray((int*)((uint8_t*)this + 0x7c), 4);
                        }
                        list1[list1Count] = derivedPtr;
                        *(int*)((uint8_t*)this + 0x80) = list1Count + 1;
                    }
                }
            }

            obj = (int*)item[10];
            if (obj && *((uint8_t*)obj + 0x18) == 2) {
                int derivedPtr = (int)(uint8_t)(*((uint8_t*)obj + 0x10)) + (int)obj;
                if (derivedPtr) {
                    int* list2 = *(int**)((uint8_t*)this + 0x88);
                    int list2Count = *(int*)((uint8_t*)this + 0x8c);
                    bool found = false;
                    for (int j = 0; j < list2Count; j++) {
                        if (list2[j] == derivedPtr) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        addToList2(this + 0xc, derivedPtr); // FUN_00a0df80
                        if ((uint32_t)list2Count == (*(uint32_t*)((uint8_t*)this + 0x90) & 0x3fffffff)) {
                            growArray((int*)((uint8_t*)this + 0x88), 4);
                        }
                        list2[list2Count] = derivedPtr;
                        *(int*)((uint8_t*)this + 0x8c) = list2Count + 1;
                    }
                }
            }
        }

        // Release TLS heap
        tlsHeap[8] = tempHeapBase;
        if (tempHeapBase == tlsHeap[10]) {
            ((void (*)(int))(*tlsHeap + 0x18))(tempHeapBase);
        }
        if ((int)(numItemsSource1 | 0x80000000) >= 0) {
            // Free temporary buffer
            heapFree(tempHeapBase, (numItemsSource1 & 0x3fffffff) * 0x30, 0x17); // FUN_00aa26e0
        }
    }
};