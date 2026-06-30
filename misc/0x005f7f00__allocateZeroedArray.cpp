// FUNC_NAME: allocateZeroedArray
// Function at 0x005f7f00: Allocates and zero-initializes an array of 12-byte elements.
// Uses a function pointer at +0x10 of the passed allocator interface (param_1).
// The element count is read from the pointer in EAX at entry (passed by caller).
void* __fastcall allocateZeroedArray(void* allocator)
{
    // EAX contains a pointer to the element count (set by caller)
    int count = *(int*)in_EAX;

    // Local struct for allocator flags (zeroed)
    int allocFlags[3] = { 0, 0, 0 };

    // Call the allocator's allocate function (offset +0x10)
    // Allocator interface: function at +0x10 takes (size, flags) returns void*
    void* buffer = (*(void*(__fastcall**)(int, int*))((int)allocator + 0x10))(count * 12, allocFlags);

    if (buffer)
    {
        // Zero the allocated memory
        memset(buffer, 0, count * 12);
        return buffer;
    }
    return nullptr;
}