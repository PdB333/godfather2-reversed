// FUNC_NAME: EARSObject::scalarDeletingDestructor
// Address: 0x0050f1f0
// This is the scalar deleting destructor for an EARS engine object of size 0xA0 (160 bytes).
// It calls the actual destructor (at FUN_004bfcf0) and optionally deallocates memory
// using a custom allocator vtable obtained from FUN_009c8f80.
// The deallocate function is at vtable offset +4 (second entry).

static const uint kEARSObjectSize = 0xA0;

void* __thiscall EARSObject::scalarDeletingDestructor(byte flags)
{
    // Call the actual destructor (member function, no explicit arguments)
    this->destructor(); // FUN_004bfcf0

    // If bit 0 of flags is set, deallocate memory
    if (flags & 1)
    {
        // Get allocator vtable pointer (returns pointer to an int array)
        int* allocatorVtable = (int*)GetAllocator(); // FUN_009c8f80

        // Deallocate function is the second vtable entry (offset +4)
        typedef void (__thiscall* DeallocateFunc)(void*, uint);
        DeallocateFunc deallocate = (DeallocateFunc)allocatorVtable[1];
        deallocate(this, kEARSObjectSize);
    }

    return this;
}