// FUNC_NAME: DataContainer::copyData
// Address: 0x0056f080
// Reconstructed from Ghidra decompilation. This function copies the internal data block
// into an output buffer only if the requested maxCount is >= the internal count.

struct DataBlock {
    // +0x00: uint unknown1 (set to 0 in output)
    // +0x04: uint unknown2 (set to 0 in output)
    // +0x08: byte flag1 (set to 1 in output)
    // +0x09: byte flag2 (set to 0 in output)
    // +0x0A: ushort count
    // +0x0C: uint dataSize
    // +0x10: byte someFlag
    // +0x14: data array (size dataSize)
};

int __thiscall DataContainer::copyData(void* this, uint maxCount, DataBlock* outBuffer) {
    ushort count = *(ushort*)((uint)this + 0x0A); // internal count

    if (count <= maxCount) {
        // Clear output header fields
        outBuffer->unknown1 = 0;
        outBuffer->unknown2 = 0;
        outBuffer->flag1 = 1;
        outBuffer->flag2 = 0;

        // Copy internal header fields
        outBuffer->count = count;
        outBuffer->dataSize = *(uint*)((uint)this + 0x0C);
        outBuffer->someFlag = *(byte*)((uint)this + 0x10);

        // Copy the data array
        uint dataSize = outBuffer->dataSize;
        memcpy(&outBuffer->data, (void*)((uint)this + 0x14), dataSize);

        return 1; // success
    }

    return 0; // failure (maxCount too small)
}