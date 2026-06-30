// FUNC_NAME: ObjectArray::clearAndFree
void __fastcall ObjectArray::clearAndFree(int* thisPtr)
{
    // thisPtr[0] = pointer to array base (each element is 12 bytes)
    // thisPtr[1] = number of elements in the array
    int count = thisPtr[1];
    int index = count - 1;
    if (index >= 0) {
        int byteOffset = index * 0xC; // 12 bytes per element
        do {
            // Each element has a pointer at offset +4 which may need freeing
            void** elementPtr = (void**)(byteOffset + 4 + thisPtr[0]);
            if (*elementPtr != nullptr) {
                FUN_004daf90(*elementPtr); // free the pointed-to memory
            }
            index--;
            byteOffset -= 0xC;
        } while (index >= 0);
    }
    if (thisPtr[0] != 0) {
        FUN_009c8f10((void*)thisPtr[0]); // free the array itself
    }
}