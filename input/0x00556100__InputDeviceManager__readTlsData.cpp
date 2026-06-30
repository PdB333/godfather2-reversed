// FUNC_NAME: InputDeviceManager::readTlsData
void __fastcall InputDeviceManager::readTlsData(void* this) {
    int slotIndex = *reinterpret_cast<int*>(static_cast<char*>(this) + 0x08); // +0x08 slot index
    if (slotIndex >= 0) {
        void* tlsBuffer = TlsGetValue(DAT_01139810);
        // Copy 23 bytes from TLS buffer at offset (slotIndex << 6) to the object's buffer
        FUN_00aa26e0(*reinterpret_cast<void**>(this), slotIndex << 6, 0x17);
    }
}