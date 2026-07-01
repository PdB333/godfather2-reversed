// FUNC_NAME: SomeBehavior::checkActive
bool __thiscall SomeBehavior::checkActive() {
    // offset +0x74: pointer to derived object or subcomponent
    uintptr_t objPtr = *(uintptr_t*)(this + 0x74);
    // 0x48 is used as a sentinel (possibly indicating invalid or untracked state)
    if (objPtr == 0 || objPtr == 0x48) {
        return true;
    }
    // The object at objPtr is actually at a fixed offset from its base due to inheritance
    void* basePtr = (void*)(objPtr - 0x48);
    // vtable is at *basePtr, call virtual function at vtable offset 0xc0 (48th function?)
    typedef float (__thiscall *VirtualFunc)(void*);
    VirtualFunc func = *(VirtualFunc*)(*(uintptr_t*)basePtr + 0xc0);
    float result = func(basePtr);

    // Global threshold used for condition (e.g., visibility, distance, etc.)
    extern float g_someGlobal; // DAT_00e44598
    if (g_someGlobal < result) {
        uintptr_t baseAddr = objPtr - 0x48;
        // Check bit 11 (0x800) at offset +0x18c from the base object
        if ((*(unsigned int*)(baseAddr + 0x18c) & (1 << 11)) == 0) {
            return false;
        }
    }
    return true;
}