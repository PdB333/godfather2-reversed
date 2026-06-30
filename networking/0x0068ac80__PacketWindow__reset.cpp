// FUNC_NAME: PacketWindow::reset
void __fastcall PacketWindow::reset(uint32_t* thisPtr)
{
    // Zero out the 32-slot sequence array (offsets 0x00-0x7C, 128 bytes)
    uint32_t* ptr = thisPtr;
    int32_t count = 15; // 16 iterations, each clearing 2 dwords
    do {
        *ptr = 0;
        ptr[1] = 0;
        ptr += 2;
        count--;
    } while (count >= 0);
    // Clear the last received sequence field at offset 0x80
    thisPtr[0x20] = 0;
}