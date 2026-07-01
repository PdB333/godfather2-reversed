// FUNC_NAME: IndexedContainer::findByKey
int* __thiscall IndexedContainer::findByKey(int key) {
    // Assume the class has a pointer to an internal array structure at offset 0.
    // Array structure layout:
    //   +0x18: count (uint)
    //   +0x28: array of elements (each element is 0x14 bytes, first int is the key)
    ArrayStruct* arrayStruct = *(ArrayStruct**)this; // +0x00: pointer to array structure
    uint count = *(uint*)((char*)arrayStruct + 0x18);
    int* elements = *(int**)((char*)arrayStruct + 0x28);

    for (uint i = 0; i < count; i++) {
        if (elements[i * 3] == key) { // each element is 0xC (3 ints) bytes
            return &elements[i * 3];
        }
    }
    return 0; // null
}