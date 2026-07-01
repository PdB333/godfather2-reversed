// FUNC_NAME: TNL::PacketWindow::copyEntry
void __thiscall TNL::PacketWindow::copyEntry(int this, int index, int source)
{
    // Destination pointer: base + index * elementSize (0x1C = 28 bytes per entry)
    byte* dest = (byte*)(this + index * 0x1C);

    // Copy fields from source (assumed to be a PacketWindowEntry of size 0x1C)
    // Structure Layout (size 0x1C):
    // +0x00: byte flags (set to 0 after copy — marks entry as unused/clear)
    // +0x04: uint32 sequenceNumber (or ID)
    // +0x08: uint64 timeSent (or timestamp)
    // +0x10: uint64 timeReceived (or ack timestamp)
    // +0x18: uint32 additionalData (e.g., acknowledgment bitmask)
    // Padding after +0x00 to align dword at +0x04: 3 bytes

    *(uint32*)(dest + 4) = *(uint32*)(source + 4);
    *(uint64*)(dest + 8) = *(uint64*)(source + 8);
    *(uint64*)(dest + 0x10) = *(uint64*)(source + 0x10);
    *(uint32*)(dest + 0x18) = *(uint32*)(source + 0x18);
    *dest = 0; // Clear first byte (flags)
}