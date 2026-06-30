// FUNC_NAME: memcpyAligned
void __thiscall memcpyAligned(void* dest, uint size) {
    // This function copies memory from the object (this pointer) to dest,
    // with alignment handling for 64-byte cache lines.
    // It uses 16-byte (4 dword) and 64-byte (16 dword) chunks for efficiency.
    uint uVar1;
    uint uVar2, uVar3, uVar4;
    int iVar5;

    // Align destination pointer to 64-byte boundary
    uVar1 = (uint)dest & 0x3f;
    // Copy 16-byte chunks until dest is 64-byte aligned or size exhausted
    for (; (uVar1 != 0 && (size != 0)); size -= 0x10) {
        uVar2 = ((uint*)this)[1];
        uVar3 = ((uint*)this)[2];
        uVar4 = ((uint*)this)[3];
        ((uint*)dest)[0] = *(uint*)this;
        ((uint*)dest)[1] = uVar2;
        ((uint*)dest)[2] = uVar3;
        ((uint*)dest)[3] = uVar4;
        dest = (uint*)dest + 4;
        this = (uint*)this + 4;
        uVar1 = (uint)dest & 0x3f;
    }
    // If remaining size > 64 bytes, copy in 64-byte blocks
    if (0x40 < size) {
        iVar5 = (size - 0x41 >> 6) + 1;
        do {
            // Copy 64 bytes (16 dwords) per iteration
            uVar2 = ((uint*)this)[1];
            uVar3 = ((uint*)this)[2];
            uVar4 = ((uint*)this)[3];
            ((uint*)dest)[0] = *(uint*)this;
            ((uint*)dest)[1] = uVar2;
            ((uint*)dest)[2] = uVar3;
            ((uint*)dest)[3] = uVar4;
            uVar2 = ((uint*)this)[5];
            uVar3 = ((uint*)this)[6];
            uVar4 = ((uint*)this)[7];
            ((uint*)dest)[4] = ((uint*)this)[4];
            ((uint*)dest)[5] = uVar2;
            ((uint*)dest)[6] = uVar3;
            ((uint*)dest)[7] = uVar4;
            uVar2 = ((uint*)this)[9];
            uVar3 = ((uint*)this)[10];
            uVar4 = ((uint*)this)[0xb];
            ((uint*)dest)[8] = ((uint*)this)[8];
            ((uint*)dest)[9] = uVar2;
            ((uint*)dest)[10] = uVar3;
            ((uint*)dest)[0xb] = uVar4;
            uVar2 = ((uint*)this)[0xd];
            uVar3 = ((uint*)this)[0xe];
            uVar4 = ((uint*)this)[0xf];
            ((uint*)dest)[0xc] = ((uint*)this)[0xc];
            ((uint*)dest)[0xd] = uVar2;
            ((uint*)dest)[0xe] = uVar3;
            ((uint*)dest)[0xf] = uVar4;
            this = (uint*)this + 0x10;
            dest = (uint*)dest + 0x10;
            size -= 0x40;
            iVar5--;
        } while (iVar5 != 0);
    }
    // Copy remaining bytes in 16-byte chunks
    for (; size != 0; size -= 0x10) {
        uVar2 = ((uint*)this)[1];
        uVar3 = ((uint*)this)[2];
        uVar4 = ((uint*)this)[3];
        ((uint*)dest)[0] = *(uint*)this;
        ((uint*)dest)[1] = uVar2;
        ((uint*)dest)[2] = uVar3;
        ((uint*)dest)[3] = uVar4;
        this = (uint*)this + 4;
        dest = (uint*)dest + 4;
    }
    return;
}