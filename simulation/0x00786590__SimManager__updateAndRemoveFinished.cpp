// FUNC_NAME: SimManager::updateAndRemoveFinished
void __thiscall SimManager::updateAndRemoveFinished(void *thisPtr)
{
    int *currentPtr;
    int count;
    int *basePtr;
    int index;
    unsigned int uCount;
    unsigned int foundIndex;
    int *objPtr;
    void *updateContext = (void *)0x01205228; // global update context

    count = *(int *)((int)thisPtr + 0x1a3c);
    basePtr = (int *)((int)thisPtr + 0x193c);
    currentPtr = basePtr;

    do {
        do {
            if (currentPtr == basePtr + count) {
                return;
            }
            objPtr = (int *)*currentPtr; // dereference: pointer to managed object
            currentPtr++;
            // Update the object (e.g., tick)
            FUN_00788f30(updateContext);
        } while (*objPtr != 0); // continue while object's first word is non-zero (still active)

        // Object is finished, find its index in the array
        foundIndex = -1;
        uCount = *(int *)((int)thisPtr + 0x1a3c);
        if (uCount != 0) {
            index = 0;
            do {
                if ((int *)basePtr[index] == objPtr) {
                    foundIndex = index;
                    break;
                }
                index++;
            } while (index < uCount);
        }

        // If this object is the "current" one, clear the reference
        if (objPtr == *(int **)((int)thisPtr + 0x2c74)) {
            *(int *)((int)thisPtr + 0x2c74) = 0;
        }

        // Remove from array by swapping with last element
        uCount = *(int *)((int)thisPtr + 0x1a3c);
        if ((unsigned int)foundIndex < uCount) {
            if ((unsigned int)foundIndex < uCount - 1) {
                basePtr[foundIndex] = *(int *)((int)thisPtr + 0x1938 + uCount * 4); // last element
            }
            *(int *)((int)thisPtr + 0x1a3c) = *(int *)((int)thisPtr + 0x1a3c) - 1;
        }

        // Notify removal (e.g., call vfunc at index 1 of some object's vtable)
        FUN_00788c50();
        ((void (__thiscall *)(void *, int))(* (int *)(*(int *)((int)thisPtr + 0x1914) + 4) ))(objPtr, 0);
    } while (true);
}