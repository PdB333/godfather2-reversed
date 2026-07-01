// FUNC_NAME: ArrayContainer::destroyArray

void ArrayContainer::destroyArray()
{
    int count = *(int*)(*(int*)(this + 0x2C) + 0x2C); // this->someStruct->count
    int* arrayPtr = *(int**)(this + 0x40);            // this->array (pointer to 8-byte elements)

    // Destroy elements in reverse order
    for (int i = count - 1; i >= 0; i--)
    {
        int* element = arrayPtr + i * 2; // each element is 8 bytes (2 ints)
        FUN_004086d0(element);           // element destructor/cleanup
        FUN_00408310(element);           // additional cleanup
    }

    // Call vtable function to free the array memory
    // vtable at this+0x28, function at vtable+4
    void (*freeArray)(void*, int) = (void (*)(void*, int))(*(int**)(*(int**)(this + 0x28) + 4));
    freeArray(arrayPtr, 0);

    *(int**)(this + 0x40) = 0; // nullify array pointer
}