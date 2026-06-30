// FUNC_NAME: MemBlock::deallocateVariantArray
// Address: 0x00638460
// Role: Frees a dynamic array whose element size depends on a flag.
// Offsets: this+0x06 = flag (0 => compact, 4-byte elements; else => wide, 8-byte elements)
//          this+0x07 = element count
// Calculates total block size = (count * elementSize) + header (0x18 for compact, 0x10 for wide)
// Calls a global deallocation function (no explicit pointer – assumed from context/register)
// Updates a size counter pointed to by a saved global allocator pointer (stored in EDI at call site)

void __thiscall MemBlock::deallocateVariantArray(void)
{
    uint8 flag = *(uint8*)((uint32)this + 6);
    uint8 count = *(uint8*)((uint32)this + 7);
    int blockSize;

    if (flag == 0) {
        // Compact: 4 bytes per element + 0x18 header
        blockSize = (int)count * 4 + 0x18;
    } else {
        // Wide: 8 bytes per element + 0x10 header
        blockSize = (int)count * 8 + 0x10;
    }

    // Call global deallocation function (likely a custom free that uses a stored pointer)
    // The actual buffer pointer is probably stored in this object (e.g., at offset +0x00 or +0x0C)
    // but not shown in the decompiled snippet. The call uses a function pointer at DAT_012059e0.
    ((void (*)(void))DAT_012059e0)();

    // Adjust allocator stats: subtract block size from a counter
    // The allocator context pointer is stored in the EDI register during the call.
    // Assuming EDI points to a global allocator object with the structure:
    //   +0x10: pointer to stats array
    //   +0x24: current total allocated size
    // In reconstructed C++, this would be something like:
    //   *(int*)(*(int*)(allocatorPtr + 0x10) + 0x24) -= blockSize;
    // But allocatorPtr is not visible in the function signature.
}

// Note: This reconstruction assumes that `DAT_012059e0` is a global function pointer
// and that the allocator context is passed via a register (error-prone in portable C++).
// The actual game code likely uses a thread-local or global singleton for memory management.