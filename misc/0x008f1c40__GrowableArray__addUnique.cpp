// FUNC_NAME: GrowableArray::addUnique

/**
 * Function: 0x008f1c40
 * Role: Appends an integer value to a dynamic array only if it is not already present.
 *       If the array is full, it doubles its capacity (or sets to 1 if currently 0).
 * Structure fields:
 *   +0x04: int* data         // pointer to dynamic array of integers
 *   +0x08: int   size        // current number of elements
 *   +0x0C: int   capacity    // allocated capacity
 */
void __thiscall GrowableArray::addUnique(int thisPtr, int value)
{
    uint uVar1;
    int newCapacity;
    int *piVar3;

    // Linear search for existing value
    uVar1 = 0;
    if (*(int *)(thisPtr + 8) != 0) {
        piVar3 = *(int **)(thisPtr + 4);
        do {
            if (*piVar3 == value) {
                return; // value already exists, do nothing
            }
            uVar1 = uVar1 + 1;
            piVar3 = piVar3 + 1;
        } while (uVar1 < *(uint *)(thisPtr + 8));
    }

    // Check if we need to grow the array
    newCapacity = *(int *)(thisPtr + 0xc);
    if (*(int *)(thisPtr + 8) == newCapacity) {
        if (newCapacity == 0) {
            newCapacity = 1;
        }
        else {
            newCapacity = newCapacity * 2;
        }
        // Reallocate the internal buffer (presumably copies old data)
        GrowableArray::reallocate(newCapacity); // 0x008f1820
    }

    // Append value to end of array
    piVar3 = (int *)(*(int *)(thisPtr + 4) + *(int *)(thisPtr + 8) * 4);
    *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) + 1;
    if (piVar3 != (int *)0x0) {
        *piVar3 = value;
    }
    return;
}