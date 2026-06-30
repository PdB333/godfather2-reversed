// FUNC_NAME: RefCountedArray::removeElement
void __thiscall RefCountedArray::removeElement(int *thisPtr, int *element)
{
    uint index = 0;
    // +0x24: count of elements in the array
    int count = *(int *)(thisPtr + 0x24);
    if (count > 0) {
        // +0x2c: pointer to array of element pointers (contiguous)
        int *array = *(int **)(thisPtr + 0x2c);
        // Search for the element pointer in the array
        while (array[index] != element) {
            index++;
            if (index >= (uint)count) {
                return; // Not found
            }
        }
        // Element found: decrement its reference count at offset +0x08 (element[2])
        int refCount = element[2];
        element[2] = refCount - 1;
        if (element[2] == 0) {
            // Call virtual function at vtable+8 (probably a release/destructor)
            (*(void (**)(void))(*element + 8))();
        }
        // Remove the element from the array by shifting subsequent entries
        if (index < count - 1) {
            do {
                array[index] = array[index + 1];
                index++;
            } while (index < count - 1);
        }
        // Update the count
        *(int *)(thisPtr + 0x24) = count - 1;
    }
}