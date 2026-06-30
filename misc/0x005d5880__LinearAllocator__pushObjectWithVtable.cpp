// FUNC_NAME: LinearAllocator::pushObjectWithVtable
// Address: 0x005d5880
// This function allocates a 16-byte block from a global linear allocator (g_allocatorPtr +0x14).
// It writes a fixed vtable pointer, then stores three integer parameters consecutively after alignment.
// Used in the EARS engine for constructing small objects with known vtable and three fields.

void __fastcall LinearAllocator::pushObjectWithVtable(
    int unused1,        // ecx (unused)
    int field0,         // edx (first data field)
    int field1,         // stack (second data field)
    int field2          // stack (third data field)
)
{
    // Global allocator structure pointer (DAT_01206880)
    // +0x14 holds the current free memory pointer.
    uint* pFreeSlotPtr = (uint*)(g_allocatorPtr + 0x14);   // pointer to the slot pointer

    uint currentSlot = *pFreeSlotPtr;                       // current allocation address

    // Write vtable pointer at current slot
    **(void***)pFreeSlotPtr = (void*)&vtable_01126c58;      // set vtable

    // Advance past vtable (4 bytes)
    *pFreeSlotPtr = currentSlot + 4;

    // Align to 4-byte boundary (round up to next multiple of 4)
    uint alignedAddr = (*pFreeSlotPtr + 3) & 0xFFFFFFFC;
    *pFreeSlotPtr = alignedAddr;

    // Store field0
    *(int*)alignedAddr = field0;
    *pFreeSlotPtr = alignedAddr + 4;

    // Store field1
    *(int*)(*pFreeSlotPtr) = field1;
    *pFreeSlotPtr = *pFreeSlotPtr + 4;

    // Store field2
    *(int*)(*pFreeSlotPtr) = field2;
    *pFreeSlotPtr = *pFreeSlotPtr + 4;

    // Final: free pointer points past the allocated block (vtable + 3 ints)
}