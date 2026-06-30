// FUNC_NAME: EARSObject::initializeWithFlag

// Global helper functions (addresses from Ghidra for reference)
// 0x00745dd0 - baseInitialize
// 0x00624da0 - setupAllocator

EARSObject* __thiscall EARSObject::initializeWithFlag(byte flag) {
    // Call base class initializer (global/static function)
    baseInitialize();

    // If the low bit is set, perform additional allocation setup
    if ((flag & 1) != 0) {
        setupAllocator(this);  // Global function taking this pointer
    }

    return this;
}