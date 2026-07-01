// FUNC_NAME: ObjectManager::addObject
void __thiscall ObjectManager::addObject(int thisPtr, int objPtr)
{
    int *arrayPtr;
    int newCapacity;
    int currentCount;
    uint newMax;

    // Check object state at offset +0xC4
    if (*(int *)(objPtr + 0xC4) == 1) {
        // Object is active/ready to be added to the main array
        currentCount = *(int *)(thisPtr + 0x10C);
        int capacity = *(int *)(thisPtr + 0x110);
        if (currentCount == capacity) {
            // Need to grow the array
            if (capacity == 0) {
                newCapacity = 1;
            } else {
                newCapacity = capacity * 2;
            }
            // Reallocate array (likely memory allocation function)
            FUN_00849170(newCapacity);
        }
        // Get pointer to the next slot in the array
        arrayPtr = (int *)(*(int *)(thisPtr + 0x108) + currentCount * 4);
        // Increment count
        *(int *)(thisPtr + 0x10C) = currentCount + 1;
        if (arrayPtr != (int *)0x0) {
            *arrayPtr = objPtr;
        }
    } else {
        if (*(int *)(objPtr + 0xC4) != 0) {
            // Unknown state, ignore
            return;
        }
        // Object state is 0: handle differently (maybe remove or process)
        FUN_00849660(&objPtr);
    }

    // Set a scaling factor on the object (e.g., speed multiplier)
    *(float *)(objPtr + 0x80) = *(float *)(thisPtr + 0x184) * *(float *)(thisPtr + 0x144);

    // Check if game is paused or similar global state
    int isPaused = FUN_006b4860();
    if (isPaused == 0) {
        // Not paused, perform additional initialization on the object
        FUN_008c3ec0(objPtr);
    }

    // If this manager is for a specific class (e.g., Player), track maximum count
    if (*(int *)(thisPtr + 0x54) == 0x637b907) {
        newMax = *(int *)(thisPtr + 0x118) + *(int *)(thisPtr + 0x10C);
        if (*(uint *)(thisPtr + 0x120) < newMax) {
            *(uint *)(thisPtr + 0x120) = newMax;
        }
    }
}