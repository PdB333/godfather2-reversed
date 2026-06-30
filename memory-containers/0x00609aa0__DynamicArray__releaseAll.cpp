// FUNC_NAME: DynamicArray::releaseAll
// Address: 0x00609aa0
// Purpose: Destroys all elements in a dynamic array of structs (each 0x14 bytes) and frees the array buffer.
// Each element has a pointer at offset 0x8 that is deallocated individually before the buffer is freed.
// FUN_009c8f10 likely is a memory deallocation function (e.g., operator delete or custom free).

void __thiscall DynamicArray::releaseAll(void)
{
    int countMinusOne = this->count - 1;
    if (countMinusOne >= 0) {
        int offset = countMinusOne * 0x14; // 20 bytes per element
        do {
            // Pointer at offset +8 within each element
            int* elementPtr = *(int**)(this->buffer + offset + 8);
            if (elementPtr != (int*)0x0) {
                FUN_009c8f10(elementPtr); // deallocate element
            }
            countMinusOne = countMinusOne - 1;
            offset = offset - 0x14;
        } while (countMinusOne >= 0);
    }
    // Free the buffer itself
    if (this->buffer != (int*)0x0) {
        FUN_009c8f10(this->buffer);
    }
    return;
}