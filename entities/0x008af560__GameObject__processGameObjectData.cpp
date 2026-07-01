// FUNC_NAME: GameObject::processGameObjectData

void __thiscall GameObject::processGameObjectData(int handle, int unused1, int unused2, void (*callback)(int)) {
    bool conditionMet;
    char conditionFlag;

    // Check bit 8 of flags at offset 0x7C (this[0x1f])
    if (((uint)this->m_flags >> 8 & 1) == 0) {
        // Bit 8 is clear
        if (((uint)this->m_flags >> 7 & 1) != 0) {
            // Bit 7 is set: push a stack frame for local processing
            int local_c = 0;
            int local_8 = 0;
            int local_4 = 0;  // unused

            pushContext(1);
            // Simulate a single iteration of a loop (local_8 incremented once)
            int iVar3 = local_8 * 0x10;  // first iteration: 0
            local_8 = local_8 + 1;       // becomes 1
            if (iVar3 + local_c != 0) {
                // This condition is false on first iteration
                resolveHandle(&handle);
            }
            popContext(&local_c);  // pop the frame
            restoreContext();
        }
    } else {
        // Bit 8 is set
        // Check two counters at offsets 0xF0 and 0xE4
        conditionMet = (this->m_someCounter1 != 0) || (this->m_someCounter2 != 0);
        
        // Call virtual function at vtable+0xD8 (index 54) with address of handle
        (this->*vfProcessHandle)(&handle);
        
        if (conditionMet) {
            conditionFlag = checkSomeCondition();
            if (conditionFlag != '\0') {
                // Call virtual function at vtable+0xB0 (index 44)
                (this->*vfOnConditionCleared)();
            }
        }
    }

    // If the handle is non-zero, invoke the callback with it
    if (handle != 0) {
        callback(handle);
    }
}