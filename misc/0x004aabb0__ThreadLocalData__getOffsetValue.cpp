// FUNC_NAME: ThreadLocalData::getOffsetValue
// Function address: 0x004aabb0
// Role: Returns a computed offset into a thread-local storage structure.
// Accesses FS:[0x2c] (pointer to TLS array) to get the first TLS slot (a pointer),
// reads offset 8 from that pointed structure, adds 0x50 and the value at this+0x18.
// Used likely for per-thread game context data access.

int __fastcall ThreadLocalData::getOffsetValue()
{
    // FS:[0x2c] in Win32 points to the Thread Local Storage (TLS) array pointer.
    // The TLS array contains pointers to per-thread data blocks.
    // We dereference to get the first TLS slot (a pointer to some per-thread structure).
    int* tlsArray = *(int**)(__readfsdword(0x2c));   // read the TLS array pointer from FS
    // Read an integer from offset 8 of the per-thread data block (the structure pointed by TLS[0]).
    // This likely holds a base address or some global offset.
    int baseOffset = *(int*)(tlsArray + 8);           // +8 corresponds to field offset 8
    // Compute final value as baseOffset + constant 0x50 + this->+0x18 offset.
    // this->0x18 is presumably an instance-specific offset used for dynamic access.
    return baseOffset + 0x50 + *(int*)((int)this + 0x18);
}