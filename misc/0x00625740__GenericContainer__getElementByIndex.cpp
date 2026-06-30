// FUNC_NAME: GenericContainer::getElementByIndex
// This function retrieves an element from a container by index.
// The container appears to be a dynamic array with elements of size 8 bytes.
// param_1 is unused (fastcall convention, but only in_EAX is used as this pointer)
// param_2 is the index to retrieve.
// If index < 1, it calls FUN_00625430 (likely a "getFirst" or "begin" function).
// Otherwise, it computes the address of the element at the given index.
// Returns the first 4 bytes of the element, or 0xFFFFFFFF on failure.

int __fastcall GenericContainer::getElementByIndex(int thisPtr, int index)
{
    int *elementPtr;

    if (index < 1) {
        elementPtr = (int *)FUN_00625430(); // likely getFirst() or begin()
    }
    else {
        // +0x0C: pointer to data array start (base)
        // +0x08: pointer to end of allocated data (one past last element)
        elementPtr = (int *)(*(int *)(thisPtr + 0x0C) - 8 + index * 8);
        if (*(int **)(thisPtr + 0x08) <= elementPtr) {
            return 0xFFFFFFFF; // out of bounds
        }
    }

    if (elementPtr == (int *)0x0) {
        return 0xFFFFFFFF; // null element
    }

    return *elementPtr; // return first 4 bytes of element
}