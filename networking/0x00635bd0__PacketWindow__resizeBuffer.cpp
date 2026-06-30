// FUNC_NAME: PacketWindow::resizeBuffer
// Function address: 0x00635bd0
// Role: Resizes the internal sliding-window buffer for packet tracking.
//   The buffer holds 8-byte packet entries. A fixed header of 0xA8 bytes
//   precedes the array. Old element count is stored at this+0x20.
//   New element count is passed as the first parameter (in EDI).
void PacketWindow::resizeBuffer(int newElementCount)
{
    // Allocate new buffer: both old and new sizes are multiplied by 8 (element size)
    // FUN_006279a0 is assumed to be a memory allocator (returns pointer to memory)
    int newBuffer = FUN_006279a0(*(int *)(this + 0x20) * 8, // old count * 8
                                  newElementCount * 8);        // new count * 8

    // Store the raw buffer pointer at this+0x1C
    *(int *)(this + 0x1C) = newBuffer;

    // Calculate the offset into the buffer where the first usable entry starts.
    // The header occupies 0xA8 bytes, so the usable area begins at newBuffer + 0xA8.
    // Then we skip the first `newElementCount * 8` bytes? Actually we set it to
    // newBuffer - 0xA8 + newElementCount * 8. This looks like a pointer to the
    // end of the usable area (or to a specific slot).
    *(int *)(this + 0x18) = newBuffer - 0xA8 + newElementCount * 8;

    // Update the element count at this+0x20
    *(int *)(this + 0x20) = newElementCount;

    // Call internal setup routine (e.g., reset indices, clear flags)
    FUN_00635b50();
}