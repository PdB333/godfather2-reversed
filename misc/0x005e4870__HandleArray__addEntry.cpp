// FUNC_NAME: HandleArray::addEntry

// Function at 0x005E4870: Adds an entry to a dynamic array of 8-byte elements and returns a handle.
// The array is part of a larger class: data pointer at +0x602c, count at +0x6030, capacity at +0x6034.
// Each entry: first word is a vtable/type pointer (points to 0x004c9720), second word is user data.
// Handle is formed by taking the address of the new entry, clearing the low byte, and setting it to 0x01.
// Calling convention: __fastcall (this in edx, first stack param in ecx? Actually param_2 is this, param_3 is data, param_1 is unused).

int __fastcall HandleArray::addEntry(void* param_1, void* this, int userData)
{
    int capacity = *(int*)((char*)this + 0x6034);
    int count    = *(int*)((char*)this + 0x6030);

    // If array is full, resize (double or start at 1)
    if (count == capacity)
    {
        int newCapacity;
        if (capacity == 0)
            newCapacity = 1;
        else
            newCapacity = capacity * 2;
        // Reallocate array (function at 0x005E70B0 likely sets new capacity and updates pointers)
        FUN_005e70b0(newCapacity);
    }

    // Pointer to the element array (base at +0x602c)
    int* dataArray = *(int**)((char*)this + 0x602c);
    // New element slot (8 bytes each)
    int* newEntry = (int*)((char*)dataArray + count * 8);
    // Increment count
    *(int*)((char*)this + 0x6030) = count + 1;

    if (newEntry != nullptr)
    {
        // Set first word to the type/vtable pointer (global label at 0x004c9720)
        newEntry[0] = (int)&LAB_004c9720;
        // Set second word to user-supplied data
        newEntry[1] = userData;
    }

    // Return handle: replace low byte of address with 0x01
    return ((int)newEntry & 0xFFFFFF00) | 0x01;
}