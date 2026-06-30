// FUNC_NAME: StreamManager::~StreamManager

// Destructor for StreamManager class at address 0x00747c50
// Assumes __thiscall calling convention (this in ecx)
// Offsets relative to this:
// +0x54 (0x15 * 4): resource handle ID (e.g., stream index)
// +0x60 (0x18 * 4): flag byte (non-zero indicates resource is active)

// External references
extern "C" void** PTR_LAB_00d640ac; // vtable for base class or custom cleanup
extern "C" void releaseStream(int resourceID); // FUN_007f6420
extern "C" void releaseHandle(void* handlePtr); // FUN_004daf90 - destruct sub-object at +0x54
extern "C" void baseDestructor(); // FUN_004ac1e0 - base class destructor

void StreamManager::~StreamManager() {
    // Set vtable to base class vtable to prevent double deletion via derived vtable
    this->vtable = &PTR_LAB_00d640ac;

    // Check if stream at index 0x15 (21) is active and handle is valid
    // Handle is non-zero and not equal to 0x48 (72) – possibly a sentinel value
    if (*(char*)(this + 0x60) != '\0' &&
        *(int*)(this + 0x54) != 0 &&
        *(int*)(this + 0x54) != 0x48) {
        releaseStream(0x15);
    }

    // Always release stream at index 0x16 (22)
    releaseStream(0x16);

    // Release the resource handle at offset +0x54 if it exists
    if (*(int*)(this + 0x54) != 0) {
        releaseHandle(this + 0x54);
    }

    // Call base class destructor
    baseDestructor();
}