// FUNC_NAME: StreamManager::releaseResources
// Address: 0x00567c60
// This function appears to release stream resources and reset state.
// It checks a flag at +0x20 and if false and context pointer exists, it cleans up owned objects.

int StreamManager::releaseResources() {
    // Check if already released (byte at +0x20 is true) and if context allocator exists
    if ((*reinterpret_cast<char*>(this + 0x20) == '\0') && 
        (*reinterpret_cast<int*>(this + 0x24) != 0)) {
        
        // Release first stream object (offset +0xc)
        if (*reinterpret_cast<int**>(this + 0xc) != nullptr) {
            // Call vtable function at index 0x5c (likely destructor/release)
            (**(code**)(**(int**)(this + 0xc) + 0x5c))(); // vtable[0x5c/4] call
            // Call allocator's function at index 0x3c (likely deallocate)
            (**(code**)(**(int**)(this + 0x24) + 0x3c))(); // vtable[0x3c/4] call
            *reinterpret_cast<int**>(this + 0xc) = nullptr;
        }
        
        // Release second stream object (offset +0x8)
        if (*reinterpret_cast<int**>(this + 0x8) != nullptr) {
            // Call vtable function at index 0x2c (likely destructor/release)
            (**(code**)(**(int**)(this + 0x8) + 0x2c))(); // vtable[0x2c/4] call
            // Call allocator's function at index 0x10 (likely deallocate)
            (**(code**)(**(int**)(this + 0x24) + 0x10))(); // vtable[0x10/4] call
            *reinterpret_cast<int**>(this + 0x8) = nullptr;
        }
        
        // Mark as released
        *reinterpret_cast<char*>(this + 0x20) = 1;
        
        // Call allocator's function at index 0x1c with 12 zero arguments
        // Possibly a memory reset or pool clear
        (**(code**)(**(int**)(this + 0x24) + 0x1c))(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
    return 1;
}