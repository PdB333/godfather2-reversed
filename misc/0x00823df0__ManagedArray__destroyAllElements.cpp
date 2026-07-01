// FUNC_NAME: ManagedArray::destroyAllElements
void __fastcall ManagedArray::destroyAllElements(int *this) {
    int count = this[1]; // +0x04
    void **array = (void **)this[0]; // +0x00, pointer to array of 8-byte elements

    for (int i = count - 1; i >= 0; --i) {
        void *element = array[i]; // first 4 bytes of each 8-byte element is pointer
        if (element != nullptr) {
            destroyElement(array + i * 2); // 8-byte element base address
        }
    }

    if (array != nullptr) {
        deallocateArray(array);
    }
}