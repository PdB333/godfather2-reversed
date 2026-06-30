// FUNC_NAME: Buffer::init
int* __thiscall Buffer::init(int* thisPtr, uint blockCount)
{
    uint uVar1;
    int* allocator;
    int currentOffset;
    int newOffset;
    int allocatedPtr;

    // Initialize buffer header fields
    thisPtr[0] = 0;          // +0x00: data pointer (null initially)
    thisPtr[1] = 0;          // +0x04: unknown (maybe size or offset)
    thisPtr[2] = -0x80000000; // +0x08: flags/capacity (high bit set, lower bits = 0)

    // Get thread-local allocator context
    allocator = (int*)TlsGetValue(DAT_01139810);
    currentOffset = allocator[8];   // +0x20: current allocation offset in the arena
    newOffset = blockCount * 0x40 + 0x10; // Requested size: blockCount * 64 + 16 bytes
    uVar1 = currentOffset + newOffset;

    // Check if we need to grow the arena
    if (uVar1 > (uint)allocator[0xb]) { // +0x2C: arena capacity
        // Call allocator's grow function (vtable method at offset 0x14)
        allocatedPtr = (**(code**)(*allocator + 0x14))(newOffset);
    } else {
        // Use existing arena space
        allocator[8] = uVar1; // Update current offset
        allocatedPtr = (int*)((int)allocator + currentOffset); // Actually the code sets *thisPtr = iVar3, where iVar3 is the old currentOffset? Wait, let's re-check.
        // In the decompiled code: *param_1 = iVar3; where iVar3 is the old currentOffset (piVar2[8]) before update? Actually:
        // iVar3 = piVar2[8]; // old current
        // then if not growing, piVar2[8] = uVar1; // update
        // then *param_1 = iVar3; // set data pointer to old current
        // So allocatedPtr is the old current offset as an address? But iVar3 is an offset, not a pointer. Wait, piVar2 is the TLS allocator pointer, so piVar2[8] is an offset into the arena? Or is it a pointer? The code uses iVar3 as an integer, then assigns to *param_1. So it's treating iVar3 as a pointer value. That suggests the allocator's current pointer is actually a pointer, not an offset. The code: iVar3 = piVar2[8]; then later *param_1 = iVar3; So it's a pointer. Then the grow function returns a pointer. So both branches set *param_1 to a pointer.
        // So in the else branch, allocatedPtr = iVar3 (the old current pointer). Then piVar2[8] = uVar1 (new pointer = old + size). So it's a bump allocator.
        allocatedPtr = (int*)currentOffset; // currentOffset is actually a pointer value
    }

    thisPtr[0] = (int)allocatedPtr; // +0x00: data pointer
    thisPtr[3] = (int)allocatedPtr; // +0x0C: another pointer to same data (maybe write cursor)
    thisPtr[2] = blockCount | 0x80000000; // +0x08: flags with block count and ownership bit

    return thisPtr;
}