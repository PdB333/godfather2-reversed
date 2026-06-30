// FUNC_NAME: SlotAllocator::allocateSlot
// Address: 0x00669e40
// Role: Attempts to allocate a new slot with a random key, using a sliding-window insertion approach.
// Structure layout: [0]=currentCount, [4]=capacity, [8]=someFlag, [12]=array pointer
int __fastcall SlotAllocator::allocateSlot(SlotAllocator* this, int maxAttempts)
{
    int* array = (int*)this[3];       // +0x0C - pointer to dynamic array
    int capacity = this[1];           // +0x04 - capacity of array
    this[2] = 0;                      // +0x08 - some flag (cleared)
    this[0] = 0;                      // +0x00 - current count (reset)
    _memset(array, 0, capacity * 4);   // clear all slots

    if (maxAttempts < 1) {
        return 0;
    }

    // Generate a non‑zero random absolute value
    int random;
    do {
        random = _rand();
        // absolute value of signed random
        random = (random ^ (random >> 0x1f)) - (random >> 0x1f);
    } while (random == 0);

    int slotIndex = FUN_00665820(this, random, this); // check if random can be placed
    if (slotIndex == 0) {
        // Attempt to insert by shifting existing elements
        while (true) {
            maxAttempts--;
            int curCount = this[0];           // +0x00
            int nextCount = curCount + 1;

            // If there is room, continue; otherwise try to expand the array
            if (nextCount > capacity) {
                if (FUN_00667740() != 0) {
                    // expansion succeeded? – we break only if expansion fails
                    // but check the condition: loop continues if (room) OR (expand returns 0)
                    // So if expansion returned non‑zero, we exit.
                    break;
                }
                // expansion failed; continue trying
            }

            // Expand the array by one slot at the front
            this[0] = nextCount;
            int shiftCount = curCount;       // number of elements to shift
            int* dest = array + curCount - 1; // array[curCount-1]
            int* src  = array + curCount - 2; // array[curCount-2]
            while (shiftCount > 0) {
                *dest = *src;
                dest--;
                src--;
                shiftCount--;
            }
            array[0] = 0;                  // clear first slot

            // Generate another random value and try again
            do {
                random = _rand();
                random = (random ^ (random >> 0x1f)) - (random >> 0x1f);
            } while (random == 0);

            slotIndex = FUN_00665820(this, random, this);
            if (slotIndex != 0) {
                return slotIndex;
            }

            if (maxAttempts < 1) {
                return 0;
            }
        }
    }
    return slotIndex;
}