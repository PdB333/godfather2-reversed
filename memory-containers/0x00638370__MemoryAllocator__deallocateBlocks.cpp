// FUNC_NAME: MemoryAllocator::deallocateBlocks
void __thiscall MemoryAllocator::deallocateBlocks(void) {
    // this structure layout (e.g. offsets from this):
    // +0x08: pointer to block0
    // +0x0c: pointer to block1
    // +0x10: pointer to block2
    // +0x14: pointer to block3
    // +0x18: pointer to block4
    // +0x1c: pointer to block5
    // +0x24: totalAllocatedSize (or size counter for main block)
    // +0x28: size of block2 (used with -8 multiplier)
    // +0x2c: size of block0 (used with -4)
    // +0x30: size of block3 (used with -4)
    // +0x34: size of block1 (used with -4)
    // +0x38: size of block4 (used with -0xc)
    // No size field for block5? The last call uses -0x48 with no size from this.

    int* piVar1;
    int size;
    int returnPtr; // in_EAX
    // 'this' is in ESI (unaff_ESI)

    // Free block0 (offset 0xc)
    size = *(int*)(this + 0x2c);
    if (*(int*)(this + 0xc) != 0) {
        returnPtr = (*g_freeFunc)(*(int*)(this + 0xc)); // likely a custom deallocator
        if (returnPtr != 0) {
            piVar1 = (int*)(*(int*)(returnPtr + 0x10) + 0x24);
            *piVar1 += size * -4; // decrease allocated size by block's size * element count?
        }
    }

    // Free block1 (offset 0x10)
    size = *(int*)(this + 0x34);
    if (*(int*)(this + 0x10) != 0) {
        returnPtr = (*g_freeFunc)(*(int*)(this + 0x10));
        if (returnPtr != 0) {
            piVar1 = (int*)(*(int*)(returnPtr + 0x10) + 0x24);
            *piVar1 += size * -4;
        }
    }

    // Free block2 (offset 0x8)
    size = *(int*)(this + 0x28);
    if (*(int*)(this + 0x8) != 0) {
        returnPtr = (*g_freeFunc)(*(int*)(this + 0x8));
        if (returnPtr != 0) {
            piVar1 = (int*)(*(int*)(returnPtr + 0x10) + 0x24);
            *piVar1 += size * -8;
        }
    }

    // Free block3 (offset 0x14)
    size = *(int*)(this + 0x30);
    if (*(int*)(this + 0x14) != 0) {
        returnPtr = (*g_freeFunc)(*(int*)(this + 0x14));
        if (returnPtr != 0) {
            piVar1 = (int*)(*(int*)(returnPtr + 0x10) + 0x24);
            *piVar1 += size * -4;
        }
    }

    // Free block4 (offset 0x18)
    size = *(int*)(this + 0x38);
    if (*(int*)(this + 0x18) != 0) {
        returnPtr = (*g_freeFunc)(*(int*)(this + 0x18));
        if (returnPtr != 0) {
            piVar1 = (int*)(*(int*)(returnPtr + 0x10) + 0x24);
            *piVar1 += size * -0xc;
        }
    }

    // Free block5 (offset 0x1c)
    size = *(int*)(this + 0x24); // note: reusing totalAllocatedSize? or is 0x24 a size field for block5?
    // Actually the original uses iVar2 from this+0x24 for the last block, but originally it was used for the size multiplier.
    // In the decompiled, the last block uses iVar2 = *(this+0x24) before the final call? Let's check: after block4, they set iVar2 = *(this+0x24); then if (*(this+0x1c) != 0){...} with multiplier iVar2 * -4. So yes, offset 0x24 is the size for block5.
    if (*(int*)(this + 0x1c) != 0) {
        returnPtr = (*g_freeFunc)(*(int*)(this + 0x1c));
        if (returnPtr != 0) {
            piVar1 = (int*)(*(int*)(returnPtr + 0x10) + 0x24);
            *piVar1 += size * -4;
        }
    }

    // Final call: free main block? (no argument passed)
    returnPtr = (*g_freeFunc)(); // zero arguments? Possibly a different function overload. In assembly, it's just call [DAT_012059e0] with eax=0? Or it might be a release of the entire container.
    if (returnPtr != 0) {
        piVar1 = (int*)(*(int*)(returnPtr + 0x10) + 0x24);
        *piVar1 += -0x48; // subtract 0x48 from the counter
    }
}