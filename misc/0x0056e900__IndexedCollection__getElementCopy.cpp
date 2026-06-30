// FUNC_NAME: IndexedCollection::getElementCopy
// Address: 0x0056e900
// Copies the internal element array (8-byte elements) into a user-provided buffer,
// given that the specified index is within the allocated capacity.
// The output buffer layout:
//   +0x00: uint (zeroed)
//   +0x04: uint (zeroed)
//   +0x08: byte (set to 1)
//   +0x09: byte (zeroed)
//   +0x0A: ushort (capacity from this+0x0A)
//   +0x0C: uint (element count from this+0x0C)
//   +0x10: array of 'elementCount' 8‑byte entries (copied from this+0x10)
// Returns 1 on success, 0 if index >= capacity.

int __thiscall IndexedCollection::getElementCopy(uint index, void* outBuffer) {
    ushort capacity = *(ushort*)(this + 0x0A);
    if (capacity <= index) {
        return 0; // Index out of bounds
    }

    uint* out = (uint*)outBuffer;         // decompiler's in_EAX
    out[0] = 0;                            // offset 0x00
    out[1] = 0;                            // offset 0x04
    *(byte*)((int)out + 9) = 0;            // offset 0x09
    *(byte*)((int)out + 8) = 1;            // offset 0x08
    *(ushort*)((int)out + 10) = capacity;  // offset 0x0A
    out[3] = *(int*)(this + 0x0C);         // offset 0x0C – element count
    // Copy entire array (this+0x10) into output after header (out+4, i.e. offset 0x10)
    memcpy(out + 4, (void*)(this + 0x10), *(int*)(this + 0x0C) * 8);
    return 1;
}