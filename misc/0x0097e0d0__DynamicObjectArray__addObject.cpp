// FUNC_NAME: DynamicObjectArray::addObject

void __thiscall DynamicObjectArray::addObject(int thisPtr, int param2)
{
    int capacity = *(int *)(thisPtr + 0xb0); // +0xb0: capacity
    int count = *(int *)(thisPtr + 0xac);    // +0xac: current count

    if (count == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate array to new capacity
        FUN_0097bd80(capacity);
    }

    count = *(int *)(thisPtr + 0xac);
    *(int *)(thisPtr + 0xac) = count + 1;

    // Pointer to new element (16 bytes each)
    int elementBase = *(int *)(thisPtr + 0xa8); // +0xa8: base pointer to array
    int* newElement = (int*)(elementBase + count * 0x10);

    // Zero out first 8 bytes
    newElement[0] = 0;
    newElement[1] = 0;

    int id = FUN_00950b20(); // Generate unique ID
    if (id != 0) {
        // Initialize element with ID, global data, and a constant hash
        FUN_0097c010(newElement, id, _DAT_00d8fd74, 0x32fc9cdc);
    }

    // Store param2 at offset +0xc (4th int)
    *(int *)((int)newElement + 0xc) = param2;
}