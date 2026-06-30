// FUNC_NAME: DynamicArray::insertWithRandomPriority
// Function address: 0x006bf340
// This function inserts a value into a dynamic array with a random probability of insertion at each existing index.
// It uses a random number generator to decide where to insert, falling back to appending at the end.

void __thiscall DynamicArray::insertWithRandomPriority(void* thisPtr, undefined4 value, int* arrayData)
{
    // arrayData[0] = pointer to data array
    // arrayData[1] = current size
    // arrayData[2] = capacity

    // Possibly lock or initialize
    lockOrInit(thisPtr);

    uint index = 0;
    if (arrayData[1] != 0) {
        do {
            int rand1 = getRandomInt();  // FUN_00791750
            int rand2 = getRandomInt();  // FUN_00791750
            if (rand1 < rand2) {
                // Insert at this index – shift elements and write value
                undefined4* slot = (undefined4*)getInsertionSlot(index);  // FUN_006bee40
                *slot = value;
                return;
            }
            index++;
        } while (index < (uint)arrayData[1]);
    }

    // If we didn't insert during the loop, append at the end
    if (arrayData[1] == arrayData[2]) {
        // Need to reallocate
        int newCapacity;
        if (arrayData[2] == 0) {
            newCapacity = 1;
        } else {
            newCapacity = arrayData[2] * 2;
        }
        reallocateArray(newCapacity);  // FUN_006b1e10
    }

    // Write value at the end
    undefined4* endSlot = (undefined4*)(arrayData[0] + arrayData[1] * 4);
    arrayData[1] = arrayData[1] + 1;
    if (endSlot != (undefined4*)0x0) {
        *endSlot = value;
    }
    return;
}