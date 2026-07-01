// FUNC_NAME: UnknownClass_destructor
void __thiscall UnknownClass_destructor(void* thisPtr)
{
    int* pointer1; // pointer to an int (actually a pointer to something)
    int index;
    int** iterPtr; // pointer to pointer for iteration

    // Set vtable pointer to base class or first virtual function table
    *(int*)thisPtr = (int)&PTR_FUN_00d73178;

    // iterator starts at offset 0x1C? Actually thisPtr+7 is offset 28 bytes, then subtract 3 each iteration: first gives offset 16, second gives offset 4.
    iterPtr = (int**)((char*)thisPtr + 0x1C); // thisPtr + 7 (4-byte units) = offset 28 bytes
    index = 1;
    do {
        pointer1 = (int*)((char*)iterPtr - 0xC); // subtract 12 bytes (3 units) -> offset 16 on first, 4 on second
        iterPtr = (int**)((char*)iterPtr - 0xC); // move iterator down by 12 bytes
        if (*pointer1 != 0) {
            FUN_009c8f10(*pointer1); // free the pointed resource
        }
        index = index - 1;
    } while (-1 < index);

    // Set vtable pointer to another address, likely a null or sentinel vtable
    *(int*)thisPtr = (int)&PTR_LAB_00d73174;

    // Clear a global flag
    DAT_011298d8 = 0;
}