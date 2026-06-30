// FUNC_NAME: NetSession::resetPacketWindow
void __thiscall NetSession::resetPacketWindow(void) {
    int slotIndex = 0x1f;                                   // 31 slots (0-indexed)
    uint* slotPtr = reinterpret_cast<uint*>(this + 8);     // +0x08: start of packet window array (32 slots, each 16 bytes)
    do {
        slotPtr[0] = 0;                                     // clear first 4 bytes of slot (e.g., sequence number)
        slotPtr[1] = 0;                                     // clear next 4 bytes (e.g., ack field)
        slotPtr += 4;                                       // move to next slot (4 * sizeof(uint) = 16 bytes)
        slotIndex--;
    } while (slotIndex >= 0);
}