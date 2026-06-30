// FUNC_NAME: StreamWriter::appendQwordWithType
// Address: 0x005192a0
// Writes a 4-byte vtable pointer (PTR_FUN_01125158) followed by an 8-byte value into a dynamic buffer.
// The stream object (this) points to a BufferMemory structure that manages the write cursor.
// BufferMemory layout:
//   +0x00: base address of allocated memory (or buffer manager)
//   +0x14: current write pointer (advances as data is appended)

void __thiscall StreamWriter::appendQwordWithType(int* thisPtr, uint32_t lowPart, uint32_t highPart) {
    // Dereference this to get the buffer manager pointer
    int* bufferMgr = (int*)*thisPtr;

    // Write vtable pointer for the object type (4 bytes)
    *(undefined4**)(bufferMgr[0x14 / 4]) = &PTR_FUN_01125158;
    bufferMgr[0x14 / 4] += 4; // +0x14

    // Align write pointer to next 4-byte boundary (already aligned after 4-byte write)
    int* alignedPtr = (int*)((bufferMgr[0x14 / 4] + 3) & ~3);
    bufferMgr[0x14 / 4] = (int)alignedPtr;

    // Write the 8-byte value (lowPart and highPart)
    *alignedPtr = lowPart;
    *(alignedPtr + 1) = highPart;

    // Advance write pointer by 8 bytes
    bufferMgr[0x14 / 4] += 8;
}