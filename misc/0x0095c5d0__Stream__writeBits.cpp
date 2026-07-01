// FUNC_NAME: Stream::writeBits
void __thiscall Stream::writeBits(int* thisPtr, int* bitCountPtr, int numBits, uint maxBits, uint value)
{
    // Check if there is enough space for numBits + 1 bits (extra bit for sign/flag?)
    if (*bitCountPtr + numBits + 1U < maxBits) {
        if (value <= numBits + 1U) {
            // Path for small values: write with a flag bit
            // vtable[0x70] likely returns a buffer pointer
            uint buffer = (**(code (__thiscall **)(int))(*(int*)thisPtr + 0x70))(0);
            // vtable[0x74] writes the value into the buffer
            uint written = (**(code (__thiscall **)(int, uint))(*(int*)thisPtr + 0x74))(0, buffer);
            // Copy or finalize the written data
            FUN_005a04a0(written);
            // Advance the bit position by 1 (flag bit)
            *bitCountPtr = *bitCountPtr + 1;
            // vtable[0x6c] seeks to the new position
            (**(code (__thiscall **)(int))(*(int*)thisPtr + 0x6c))(*bitCountPtr);
            // Write the actual value
            buffer = (**(code (__thiscall **)(int))(*(int*)thisPtr + 0x70))(0);
            written = (**(code (__thiscall **)(int, uint))(*(int*)thisPtr + 0x78))(0, buffer);
            FUN_005a04a0(written);
            return;
        }
        // Path for larger values: write without the extra flag bit
        uint buffer = (**(code (__thiscall **)(int))(*(int*)thisPtr + 0x70))(0);
        uint written = (**(code (__thiscall **)(int, uint))(*(int*)thisPtr + 0x7c))(0, buffer);
        FUN_005a04a0(written);
    }
    // If not enough space, do nothing (or error handling omitted)
}