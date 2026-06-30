// FUNC_NAME: HandleTable::getPointer
// Address: 0x006b07e0
// Retrieves a pointer from an internal array (offset +0x28) using an index computed by an internal function (0x006afa90).
// Returns 0 if the index is invalid or the element is null.

int __fastcall HandleTable::getPointer(void* this) {
    // Call internal function to compute an index (likely from a hash or ID)
    // FUN_006afa90 takes 'this' as parameter (ECX) and returns index or -1
    int index = FUN_006afa90(this); // assume thiscall, param in ECX

    if (index < 0) {
        return 0;
    }

    // Array at this+0x28: pointer to array of 8-byte entries.
    // Each entry: 4 bytes data at offset +0, then 4 bytes next? (since we read +4 into the element)
    // Actually: *(int*)( this+0x28 ) gives base pointer.
    // Then base + 4 + index*8 reads the second 4-byte field of each 8-byte struct.
    // But the return is the first 4 bytes of the pointer? Wait: puVar1 = (undefined4*)(base + 4 + i*8),
    // and then return *puVar1. So we are reading the value at that address, which is a 4-byte value.
    // This suggests each array element is an 8-byte structure where the second 4 bytes (offset 4) store a pointer to the actual data?
    // Actually, the returned value is the first 4 bytes at that pointer, so we are double-dereferencing? No.
    // Let's read the decompiler: puVar1 = (undefined4 *)(*(int *)(param_1 + 0x28) + 4 + iVar2 * 8);
    // Then return *puVar1; So puVar1 is a pointer to an undefined4, and we return the value it points to.
    // So the array at +0x28 is an array of pointers (8 bytes each? or maybe structures with 8 bytes).
    // The code adds 4 to the base pointer, meaning we skip the first 4 bytes of each element.
    // So each element is 8 bytes: first 4 bytes maybe a type or next/prev, second 4 bytes is a pointer.
    // Then that pointer is dereferenced to get the value.
    // So it's a two-level indirection: get pointer from array slot, then get value from that pointer.
    // But the return type is undefined4, so it's just a 32-bit value (possibly another pointer).

    int* arrayBase = *(int**)((char*)this + 0x28);
    if (arrayBase == 0) {
        return 0;
    }
    int* slotPtr = (int*)((char*)arrayBase + 4 + index * 8);
    if (slotPtr == 0) {
        return 0;
    }
    return *slotPtr;
}