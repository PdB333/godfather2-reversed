// FUNC_NAME: NetBufferManager::releasePacketData
// Address: 0x004c3920 - Releases a double-indirected packet buffer.
extern void ReleaseBuffer(void* buffer);

void __fastcall NetBufferManager::releasePacketData(int this) {
    // Dereference pointer at offset 0x18 twice to obtain the actual buffer
    void* data = **(void***)(this + 0x18);
    ReleaseBuffer(data);
}