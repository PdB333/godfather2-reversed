// FUNC_NAME: ObjectPool::findFreeObject
// Function at 0x006f92a0: Iterates over an array of pointers stored at this+0x28 (size at this+0x2c).
// For each pointer, checks a field at offset +0x10 via FUN_004d4b20. Returns the first pointer for which the check returns 0.
void* __thiscall ObjectPool::findFreeObject(void* thisPtr)
{
    // +0x28: pointer to start of array of object pointers (each 4 bytes)
    int* begin = *(int**)((char*)thisPtr + 0x28);
    // +0x2c: number of elements (count)
    int count = *(int*)((char*)thisPtr + 0x2c);
    int* end = begin + count; // pointer arithmetic (each int is 4 bytes)

    if (begin == end) // empty container
        return 0;

    int* current = begin;
    do {
        // Dereference current to get the object pointer
        void* object = (void*)*current;
        // FUN_004d4b20 likely checks an availability flag at object+0x10; returns 0 if available
        int available = FUN_004d4b20((void*)((char*)object + 0x10));
        if (available == 0) {
            return object;
        }
        current++;
    } while (current != end);
    return 0;
}