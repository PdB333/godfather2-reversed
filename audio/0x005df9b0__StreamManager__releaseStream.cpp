// FUNC_NAME: StreamManager::releaseStream
// Function at 0x005df9b0 - Cleanup/release of a managed stream object (size 0x18)
void StreamManager::releaseStream() {
    byte localBuffer[12]; // temporary storage for a copy operation

    // Copy stream data to local buffer (likely a detach or backup)
    // FUN_005dffe0 signature: (outBuffer, this, *(*this+0x1c), this, *this+0x1c)
    FUN_005dffe0(localBuffer, this, 
                 **reinterpret_cast<void***>(this + 0x1c), 
                 this, 
                 *reinterpret_cast<void**>(this + 0x1c));

    // Call virtual release method on the stream object (offset 0x4 in vtable)
    void* stream = *reinterpret_cast<void**>(this + 0x1c);
    void* vtable = *reinterpret_cast<void**>(this + 4);       // +0x04: vtable pointer
    typedef void (*ReleaseFunc)(void*, int);
    ReleaseFunc release = *reinterpret_cast<ReleaseFunc*>(vtable + 4); // second virtual function
    release(stream, 0x18);

    // Clear both member pointers
    *reinterpret_cast<void**>(this + 0x1c) = nullptr; // +0x1c: stream pointer
    *reinterpret_cast<void**>(this + 0x20) = nullptr; // +0x20: related buffer/ptr
}