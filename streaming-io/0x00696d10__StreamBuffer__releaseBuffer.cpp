// FUNC_NAME: StreamBuffer::releaseBuffer
void __fastcall StreamBuffer::releaseBuffer() {
    // Temporary 8-byte buffer for the release operation
    char tempBuffer[8];

    // Call internal release function that uses the buffer
    void (*releaseFunc)(char*, void*, uint32_t, void*, void*) = (void (*)(char*, void*, uint32_t, void*, void*))0x00695e30;
    releaseFunc(tempBuffer, this, **reinterpret_cast<uint32_t**>(this + 4), this, *reinterpret_cast<uint32_t**>(this + 4));

    // Free the buffer pointer at offset +0x4
    void (*freeFunc)(void*) = (void (*)(void*))0x009c8eb0;
    freeFunc(*reinterpret_cast<void**>(this + 4));

    // Clear both pointers
    *reinterpret_cast<void**>(this + 4) = nullptr;
    *reinterpret_cast<void**>(this + 8) = nullptr;
}