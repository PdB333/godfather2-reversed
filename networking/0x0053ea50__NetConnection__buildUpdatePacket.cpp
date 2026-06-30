// FUNC_NAME: NetConnection::buildUpdatePacket
void __thiscall NetConnection::buildUpdatePacket(void* this, void* unknownParam, int updateCount, void** updateArray)
{
    // Parameters in registers: updateCount (EBP), updateArray (ESI)
    // unknownParam (param_2) is passed as stack argument.

    int savedAllocatorPos = 0;
    int allocatorCurrentPos = 0;
    int allocFlags = 0x80000000;
    int* tlsAllocator = (int*)TlsGetValue(DAT_01139810);
    int allocBuffer = 0;

    // Allocate temporary memory (0x110 bytes) from TLS allocator
    int oldTop = tlsAllocator[8]; // current stack pointer
    if ((uint)tlsAllocator[0xb] < (uint)(oldTop + 0x110)) {
        allocBuffer = (**(code**)(*tlsAllocator + 0x14))(0x110); // allocate new block
    } else {
        allocBuffer = oldTop;
        tlsAllocator[8] = oldTop + 0x110; // advance pointer
    }
    allocFlags = 0x80000020;
    savedAllocatorPos = allocBuffer; // store the base of allocated memory

    // Call a virtual function to serialize into the allocated buffer
    // this+4 -> some subobject -> vtable+0x54 -> function at +0x40
    (**(code**)(**(int**)(*(int*)((char*)this + 4) + 0x54) + 0x40))(unknownParam, &allocBuffer);

    // Iterate over the updateArray (each entry is 8 bytes: pointer + extra info)
    for (int i = 0; i < updateCount; ++i) {
        int objPtr = *(int*)((char*)updateArray + 4 + i * 8); // second dword of entry
        int adjustedPtr = *(char*)(objPtr + 5) + objPtr; // add signed byte at offset 5
        if (*(char*)(adjustedPtr + 0x18) == '\x01' && *(char*)(adjustedPtr + 0x10) + adjustedPtr != 0) {
            FUN_009f2000(); // debug/log function
        }
    }

    // Restore allocator state
    tlsAllocator = (int*)TlsGetValue(DAT_01139810);
    tlsAllocator[8] = savedAllocatorPos; // restore to saved position
    if (savedAllocatorPos == tlsAllocator[10]) {
        (**(code**)(*tlsAllocator + 0x18))(savedAllocatorPos); // deallocate if at limit
    }

    // Store the allocated buffer info back into the update array?
    if (allocBuffer >= 0) {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(updateArray, allocBuffer * 8, 0x17); // likely a memset or assignment
    }
}