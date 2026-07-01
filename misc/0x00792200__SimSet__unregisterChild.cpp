// FUNC_NAME: SimSet::unregisterChild
// Address: 0x00792200
// Searches a container's object list (array at +0x14, count at +0x18) for a given element pointer,
// removes it from the list by calling an internal eraser at FUN_006be9f0,
// and clears a flag (bit 22, 0x400000) on the element's flags at +0x5c to mark it no longer registered.

void __thiscall SimSet::unregisterChild(void *thisPtr, void *element) {
    uint count = *(uint *)((char *)thisPtr + 0x18);
    if (count == 0) {
        return;
    }

    int *list = *(int **)((char *)thisPtr + 0x14);
    uint index = 0;
    while (list[index] != (int)element) {
        index++;
        if (index >= count) {
            return; // element not found
        }
    }

    // Found element at 'index'
    // Internal erase by index; likely shifts remaining elements
    FUN_006be9f0(index); // Container::eraseByIndex

    // Clear the "registered in container" flag (bit 22) on the element
    *(uint *)((char *)element + 0x5c) &= 0xffbfffff; // bit 22 = 0x400000
}