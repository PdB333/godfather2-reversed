// FUNC_NAME: PacketStream::unpackAndDispatch
// Address: 0x004f13a0
// Reads a packed buffer (pointer at this+0x18), extracts 6 fields with 4-byte alignment,
// and calls a dispatch function (function pointer from table at param_2) with extracted values.

void PacketStream::unpackAndDispatch(void *thisPtr, void *dispatchTable) {
    uint32_t packetId;           // first field (unaligned read)
    uint32_t field1;             // field at aligned offset 0
    uint64_t field2;             // field at aligned offset 4
    uint32_t field3;             // field at aligned offset 12
    uint64_t field4;             // field at aligned offset 16
    uint32_t field4_lo, field4_hi; // split of field4

    uint8_t *alignedStart;       // current buffer pointer after rounding

    // Retrieve current buffer pointer from object at offset +0x18
    uint8_t *rawPtr = *(uint8_t**)((char*)thisPtr + 0x18);

    // Read the first 4-byte field (e.g., packet type) from the raw unaligned pointer
    packetId = *(uint32_t*)rawPtr;

    // Align the pointer to the next 4-byte boundary (round up if needed)
    alignedStart = (uint8_t*)(((uint32_t)rawPtr + 7) & ~3);
    *(uint8_t**)((char*)thisPtr + 0x18) = alignedStart; // update buffer pointer

    // Read fields from aligned buffer in order (as per original unhinted sequence)
    // Each read advances the pointer in the object at the same points as the original asm.
    field1 = *(uint32_t*)alignedStart;
    *(uint8_t**)((char*)thisPtr + 0x18) = alignedStart + 4; // pointer now at offset 4

    field2 = *(uint64_t*)(alignedStart + 4);
    // no pointer update here in original code (re-used puVar6+1)
    field3 = *(uint32_t*)(alignedStart + 12); // puVar6[3]
    *(uint8_t**)((char*)thisPtr + 0x18) = alignedStart + 16; // pointer now at offset 16

    field4 = *(uint64_t*)(alignedStart + 16);
    *(uint8_t**)((char*)thisPtr + 0x18) = alignedStart + 24; // pointer now at offset 24

    // Split the 64-bit field4 into low and high 32-bit parts
    field4_lo = (uint32_t)(field4 & 0xFFFFFFFF);
    field4_hi = (uint32_t)(field4 >> 32);

    // Call the dispatch function through the first entry in the table (param_2)
    // The dispatchTable is a pointer to a function pointer (e.g., vtable entry)
    typedef void (__fastcall *DispatchFunc)(uint32_t, uint32_t, uint64_t, uint32_t, uint32_t, uint32_t);
    DispatchFunc func = *(DispatchFunc*)dispatchTable;
    func(packetId, field1, field2, field3, field4_lo, field4_hi);
}