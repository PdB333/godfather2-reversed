// FUNC_NAME: NetConnection::writeUpdatePacket
// Address: 0x0053ea50
// This function appears to write a packet containing updates for network objects.
// It uses a TLS-based temporary allocator to buffer data, then iterates over a list of
// object descriptors to process them (likely marking them as dirty or adding to a list).
// The function takes an implicit array pointer and count from ESI and EBP (fastcall-like registers).

void NetConnection::writeUpdatePacket(int param_2, int updateListArray, int updateCount)
{
    int* tlsData;                    // piVar1
    int bufferPtr;                   // local_14
    int savedAllocTop;               // local_10
    uint allocFlags = 0x80000020;    // local_c
    int allocOffset;                 // local_8

    bufferPtr = 0;
    savedAllocTop = 0;

    // Get thread-local storage pointer
    tlsData = (int*)TlsGetValue(DAT_01139810);
    allocOffset = tlsData[8];        // current allocation top

    // Allocate 0x110 bytes from the TLS scratch buffer
    if ((uint)tlsData[0xb] < (uint)(allocOffset + 0x110)) {
        // Need more memory: call custom allocator (vtable at *tlsData + 0x14)
        bufferPtr = (int)((*(code**)(*tlsData + 0x14))(0x110));
    } else {
        // Bump the pointer within the current block
        tlsData[8] = allocOffset + 0x110;
        bufferPtr = allocOffset;
    }

    allocFlags = 0x80000020;         // Flag indicating this is a network write buffer
    savedAllocTop = allocOffset;     // Save original top for later restoration

    // Call a virtual function on an object obtained from this->field4
    // The object is at *(this+4), then field at +0x54 points to a serializer,
    // and its vtable offset 0x40 is a function that writes into the buffer.
    // param_2 is likely the object or stream to serialize.
    (**(code**)(**(int**)(*(int*)(this + 4) + 0x54) + 0x40))(param_2, &bufferPtr);

    // Iterate over the list of update descriptors (each 8 bytes: pointer to object data + padding)
    for (int i = 0; i < updateCount; i++) {
        int objPtr = *(int*)(updateListArray + 4 + i * 8);   // Get pointer from array
        // The object structure: char at offset 5 indicates some flag, char at offset 0x10 and 0x18
        int objBase = *(char*)(objPtr + 5) + objPtr;         // Derive base pointer (possibly a structure with vtable)
        // Check conditions: (offset 0x18 == 1) and (offset 0x10 pointer is non-null)
        if ((*(char*)(objBase + 0x18) == 1) && (*(char*)(objBase + 0x10) + objBase != 0)) {
            FUN_009f2000();   // Likely adds the object to a dirty list or triggers an update
        }
    }

    // Restore TLS allocation state
    tlsData = (int*)TlsGetValue(DAT_01139810);
    tlsData[8] = savedAllocTop;                       // Reset allocation top
    if (savedAllocTop == tlsData[10]) {
        (**(code**)(*tlsData + 0x18))(savedAllocTop); // Free if we hit the watermark
    }

    // If buffer was allocated (non-negative pointer), free it via thread-local deallocation
    if (bufferPtr >= 0) {
        TlsGetValue(DAT_01139810);                     // Get TLS again (unused result)
        FUN_00aa26e0(updateListArray, bufferPtr * 8, 0x17); // Likely memory deallocation
    }
}