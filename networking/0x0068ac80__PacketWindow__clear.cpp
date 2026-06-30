// FUNC_NAME: PacketWindow::clear
void __fastcall PacketWindow::clear()
{
    // Clear the first 32 DWORD slots (0-31) using 16 iterations of two writes
    int* ptr = reinterpret_cast<int*>(this);
    int count = 16;
    do {
        ptr[0] = 0;          // +0x00
        ptr[1] = 0;          // +0x04
        ptr += 2;            // Advance 8 bytes (2 DWORDs)
        count--;
    } while (count >= 0);

    // Clear slot index 32 (offset 0x80)
    // This is redundant with the loop's last write, but present in the original
    ptr[0] = 0;              // +0x80
}