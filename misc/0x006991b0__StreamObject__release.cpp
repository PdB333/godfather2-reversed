// FUNC_NAME: StreamObject::release
void __thiscall StreamObject::release() {
    // +0x18: Win32 handle (HANDLE)
    if (this->handle != INVALID_HANDLE_VALUE) {
        CloseHandle(this->handle);
        this->handle = INVALID_HANDLE_VALUE;
    }

    // +0x14: dynamically allocated buffer (e.g., read/write buffer)
    if (this->buffer1 != nullptr) {
        // FUN_009c8eb0 - likely custom deallocation
        MemoryManager::deallocate(this->buffer1);
        this->buffer1 = nullptr;
    }

    // +0x2c: another allocated resource (e.g., secondary buffer, structure)
    if (this->buffer2 != nullptr) {
        // FUN_009c8f10 - likely another deallocation
        MemoryManager::deallocate(this->buffer2);
        this->buffer2 = nullptr;
    }

    // +0x04, +0x08: pointer pair (possibly a shared reference or tracked pointer)
    // The code stores the pointer at +0x04 into +0x08 before freeing the original.
    void* extraPtr = this->somePointer;  // offset +0x04
    this->somePointerCopy = extraPtr;    // offset +0x08
    if (extraPtr != nullptr) {
        MemoryManager::deallocate(extraPtr);
    }
}