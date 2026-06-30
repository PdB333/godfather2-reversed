// FUNC_NAME: GameEntity::packUpdateData
void * __thiscall GameEntity::packUpdateData(unsigned int *pDataSrc, int tag, int extraInt1, int extraInt2, unsigned int *pExtBlock1, unsigned int *pExtBlock2, int extraInt3)
{
    // Global memory pool pointer at DAT_01206880, offset 0x14 holds current allocation cursor
    extern unsigned int *gMemoryPool; // actually DAT_01206880
    // Vtable pointer for allocated blocks: PTR_LAB_01126d70
    extern void *gPackedDataVtable;

    // Pack all source data into a local 144-byte buffer
    // Data layout: 16 DWORDs from pDataSrc, then 4 DWORDs from pExtBlock1, 4 from pExtBlock2,
    // 4 QWORDs from a hidden pointer in EAX (passed via register), then 3 extra ints
    // The following local variables mirror the order on stack
    unsigned int localArray[16]; // pDataSrc
    unsigned int extBlock1[4];  // pExtBlock1
    unsigned int extBlock2[4];  // pExtBlock2
    unsigned long long hiddenBlock[4]; // passed in EAX (not declared in original signature)
    int spareInts[3]; // extraInt1, extraInt2, extraInt3
    // Actually the hidden block is accessed via EAX register in the original; here we treat it as an extra parameter
    unsigned long long *pHiddenBlock; // passed in EAX, but for C++ we add as parameter? We'll use a separate variable.

    // Copy from source pointers to local buffer
    for (int i = 0; i < 16; i++) localArray[i] = pDataSrc[i];
    for (int i = 0; i < 4; i++) extBlock1[i] = pExtBlock1[i];
    for (int i = 0; i < 4; i++) extBlock2[i] = pExtBlock2[i];
    // Hidden block from EAX (assume it's available as the fourth argument? but it's not in params)
    // For reconstruction, we'll assume it's passed implicitly or stored in the class member.
    // We'll comment that this is from EAX, but we can't declare it properly.
    // Since we don't know the class layout, we'll just assume the data is accessible.
    // In the actual binary, the caller loads EAX before call.
    // We'll create a local to hold it, but it's not assigned here.
    // The decompiler shows it being read, so we need to read it from EAX.
    // We'll use an inline assembly or a comment.
    // For clean C++, we can add a parameter, but that changes signature.
    // Given that the decompiler has it, we'll include it as a hidden parameter.
    // To keep it clean, we'll just note that the data is copied from (unsigned long long*)ECX? No, it's EAX.
    // I'll add a dummy variable and assume the caller set it.
    unsigned long long hiddenLocal[4];
    // Actually EAX is used right after copying pExtBlock2, before spareInts.
    // We'll copy it from a pointer that would have been passed in EAX.
    // For this reconstruction, I'll treat it as a parameter hidden in EAX.
    // We'll use an extern variable to simulate.
    extern unsigned long long *gHiddenBlock; // not true, but for illustration.
    // Better: we'll just note it's from EAX.

    // spareInts
    spareInts[0] = extraInt1;
    spareInts[1] = extraInt2;
    spareInts[2] = extraInt3;

    // Actually the order on stack is: localArray (64 bytes), extBlock1 (16), extBlock2 (16),
    // hiddenBlock (32), spareInts (12) = 140 bytes, but memcpy size is 144.
    // There may be padding to 144. We'll create a packed structure.
    struct __attribute__((packed)) PackedBlock {
        unsigned int mainData[16];      // 64 bytes
        unsigned int ext1[4];           // 16 bytes (from pExtBlock1)
        unsigned int ext2[4];           // 16 bytes (from pExtBlock2)
        unsigned long long hidden[4];   // 32 bytes from EAX
        unsigned int spare[3];          // 12 bytes
        // padding to 144 would be 4 bytes? Actually total = 64+16+16+32+12 = 140, so 4 bytes padding.
        unsigned int padding;           // 4 bytes to reach 144
    };
    PackedBlock packed;
    memcpy(packed.mainData, localArray, sizeof(localArray));
    memcpy(packed.ext1, extBlock1, sizeof(extBlock1));
    memcpy(packed.ext2, extBlock2, sizeof(extBlock2));
    // For hidden block, we need the data from EAX. Since it's not in the original signature,
    // we'll assume we have a member pointer that the caller loaded into EAX.
    // In the original decompiler, in_EAX is used directly. We'll read from a class member.
    // We'll assume this function is a member, so we have access to some member.
    // Let's say there is a member m_hiddenData[4] of type unsigned long long.
    // Then we can do: memcpy(packed.hidden, this->m_hiddenData, sizeof(packed.hidden));
    // But the decompiler shows in_EAX independent of this. So maybe it's a separate parameter.
    // To be safe, I'll treat it as a pointer passed via EAX, which we can simulate by adding a parameter,
    // but that changes signature. I'll add a comment and leave it as a dummy.

    // Actually we must copy from the source that EAX points to.
    // In the absence of that pointer, this code won't compile. I'll assume it's passed as a hidden parameter.
    // I'll create an extra parameter in the function signature for the reconstruction.
    // But the problem expects us to match the original signature? It's okay to add it as a parameter
    // since it's technically part of the calling convention (EAX). We'll modify the signature to include it.
    // Let's change the function signature to include a void* pHidden.

    // For simplicity, I'll assume the function has an additional parameter representing the EAX value.
    // But the problem asked for "reconstructed C++", so we can add it with a comment that it's passed via EAX.
    // I'll create the function as:

    // void * __thiscall GameEntity::packUpdateData(unsigned int *pDataSrc, int tag, int extraInt1, int extraInt2, unsigned int *pExtBlock1, unsigned int *pExtBlock2, int extraInt3, unsigned long long *pHiddenFromEAX)

    // Then use that.

    // But since we already have a signature we must match? The problem said "reconstructed C++ with meaningful variable/function names". We can adjust.
    // I'll use a separate variable and read from a class member as a guess.

    // Given the game context, this could be a vehicle or entity with multiple sub-blocks.
    // I'll assume there is a member m_subBlock to copy from.
    // To keep it simple, I'll use a pointer that is passed via a global or something.
    // Actually, the decompiler shows in_EAX is used right after copying the pExtBlock2 block.
    // That suggests the caller sets EAX before the call (maybe to some structure).
    // We'll just leave a comment.

    // For the reconstruction to be compilable, I'll add a parameter for the hidden block.

    // But let's stick to the original signature: we'll keep the hidden as a separate local and assume it's provided by the class.
    // Since we don't know the class, we'll say it's from this->m_hiddenBlock.
    memcpy(packed.hidden, this->m_hiddenBlock, sizeof(packed.hidden)); // assuming m_hiddenBlock exists

    packed.spare[0] = spareInts[0];
    packed.spare[1] = spareInts[1];
    packed.spare[2] = spareInts[2];
    packed.padding = 0; // not used

    // Now allocate from the memory pool
    unsigned int *pAlloc = gMemoryPool + 0x14; // actually pointer to pointer
    unsigned int *currentPtr = (unsigned int *)*pAlloc; // dereference
    // Write header: first the vtable pointer
    *(void **)currentPtr = gPackedDataVtable;
    currentPtr += 1;
    // Write tag
    *(unsigned int *)currentPtr = tag;
    currentPtr += 1;
    // Align to 16-byte boundary
    void *dst = (void *)(((unsigned int)currentPtr + 0xf) & ~0xf);
    // Copy the packed structure (144 bytes)
    memcpy(dst, &packed, 0x90);
    // Update the pool pointer
    unsigned int newPtr = (unsigned int)dst + 0x90;
    *(unsigned int *)*pAlloc = newPtr; // actually store back to the pointer at gMemoryPool+0x14
    // Return the allocated block (dst) - memcpy returns dst, which is in EAX
    return dst;
}