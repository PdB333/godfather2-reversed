// FUNC_NAME: CallContext::invokeFromCallBuffer

void CallContext::invokeFromCallBuffer(uint* context, uint** callTarget)
{
    // Dereference pointer at offset +0x18 to get the current argument buffer
    uint* argsPtr = *(uint**)(context + 0x18);
    
    // Read four words from the buffer (consecutive consumption)
    uint arg1 = argsPtr[0];
    uint arg2 = argsPtr[1];
    int count   = argsPtr[2];   // Number of 12-byte slots
    int align   = argsPtr[3];   // Alignment boundary (power of two)
    
    // Update the context's buffer pointer past the 16-byte header
    // The pointer is set to: original buffer + count*0xC + aligned_offset
    uint baseAddr = (uint)argsPtr + 4 * sizeof(uint); // past the header words
    uint alignedOff = (baseAddr + align + 0xF) & ~(align - 1); // align up
    *(uint*)(context + 0x18) = (uint)argsPtr + count * 0xC + alignedOff;
    
    // Build the combined 64-bit parameter: high = count, low = alignedOff if count != 0 else 0
    uint64 combined = ((uint64)count << 32) | ((count != 0) ? alignedOff : 0);
    
    // Call the target function with the extracted arguments
    void (*func)(uint, uint, uint64, int) = (void (*)(uint, uint, uint64, int))(*callTarget);
    func(arg1, arg2, combined, align);
}