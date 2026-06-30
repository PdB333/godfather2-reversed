// FUNC_NAME: RelocatableBlock::fixupPointers

void __thiscall RelocatableBlock::fixupPointers(byte* outSignBit)
{
    // +0x08: Value whose MSB is stored as flag in outSignBit
    *outSignBit = (byte)((uint)*(int*)(this + 8) >> 0x1f);

    // +0x0c: Relative pointer to relocate (add base address if non-zero)
    if (*(int*)(this + 0xc) != 0) {
        *(int*)(this + 0xc) = *(int*)(this + 0xc) + (int)this;
    }

    // +0x18: Base address of the data block (points to offset +0x20)
    *(int*)(this + 0x18) = (int)this + 0x20;

    // +0x14: Second dimension count; +0x10: First dimension count
    // +0x1c: Pointer to the array of ints to relocate
    if (*(int*)(this + 0x14) != 0) {
        *(int*)(this + 0x1c) = (int)this + 0x20 + *(int*)(this + 0x10) * 4;
    }

    // Relocate each element of the pointer array (count = dim1 * dim2)
    int* currentPtr = *(int**)(this + 0x1c);
    int count = *(int*)(this + 0x10) * *(int*)(this + 0x14);
    for (int i = count; i != 0; i--) {
        *currentPtr = *currentPtr + (int)this;
        currentPtr++;
    }
}