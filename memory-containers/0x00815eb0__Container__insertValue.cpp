// FUNC_NAME: Container::insertValue

void __thiscall Container::insertValue(Container* this, int value)
{
    // +0x50 on value is the bucketing key (e.g., category index)
    int bucketIndex = *(int*)(value + 0x50);

    // Each bucket descriptor is 12 bytes: arrayPtr (4b), count (4b), capacity (4b)
    int* bucketDesc = (int*)((int)this + 4 + bucketIndex * 0xC); // points to the array pointer
    int* arrayPtr = bucketDesc[0];  // +0x00: pointer to array of int (value pointers)
    int count = bucketDesc[1];      // +0x04: current number of elements
    int capacity = bucketDesc[2];   // +0x08: allocated capacity

    // 1. Linear search for pointer identity
    if (count != 0) {
        int* current = arrayPtr;
        for (uint i = 0; i < (uint)count; i++, current++) {
            if (*current == value) {
                // Already present – no insertion needed
                return;
            }
        }
    }

    // 2. Second chance: check using a secondary key from value+0x54
    int secondaryKey = *(int*)(value + 0x54);
    if (count != 0) {
        for (uint i = 0; i < (uint)count; i++) {
            // Compute hash of existing element? FUN_00401010 likely takes something.
            int hash = FUN_00401010();  // TODO: parameter missing in decomp? Possibly hash of arrayPtr[i]'s key?
            if (FUN_00815970(secondaryKey, hash) >= 0) {
                // Replace the slot at index i with value
                int* slot = (int*)FUN_00815e00(i); // returns &arrayPtr[i]
                *slot = value;
                return;
            }
        }
    }

    // 3. Not found – insert at the end, possibly growing the bucket
    if (count == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        FUN_00815b80(newCapacity); // resize the bucket's array
        // After resize, bucketDesc[0] has been updated to new array
        arrayPtr = bucketDesc[0];
        capacity = bucketDesc[2];
    }

    int* insertPos = arrayPtr + count * 4;
    bucketDesc[1] = count + 1;  // increment count
    if (insertPos != (int*)0x0) {
        *insertPos = value;
    }
    return;
}