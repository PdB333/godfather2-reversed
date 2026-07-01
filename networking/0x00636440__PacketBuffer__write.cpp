//FUNC_NAME: PacketBuffer::write
int __thiscall PacketBuffer::write(int param_1)
{
    byte savedByte;
    int result;

    // Check if current pointer equals end pointer (buffer empty or full?)
    if (*(int *)(this + 0x14) == *(int *)(this + 0x28)) {
        // Buffer is empty? Check if available space (difference >> 3) is less than requested size
        if ((*(int *)(this + 8) - *(int *)(this + 0xc)) >> 3 <= param_1) {
            result = FUN_006363e0(); // Likely error or grow buffer
            return result;
        }
    } else {
        // Check if the current element's flag (at +8) has bit 0x10 set
        if ((*(byte *)(*(int *)(this + 0x14) + 8) & 0x10) == 0) {
            result = FUN_006363e0(); // Error condition
            return result;
        }
    }

    savedByte = *(byte *)(this + 0x31); // Save state byte
    result = FUN_00635ab0(); // Attempt to write data
    if (result != 0) {
        // On success, reset pointers
        *(int **)(this + 0x14) = *(int **)(this + 0x28); // current = end
        *(int *)(this + 0xc) = **(int **)(this + 0x28); // read size from end
        *(short *)(this + 0x2e) = 0; // Clear some short
        FUN_006382a0(); // Finalize write
        FUN_006359f0(); // Update state
        *(byte *)(this + 0x31) = savedByte; // Restore state
        FUN_00635b10(); // Notify or cleanup
    }
    return result;
}