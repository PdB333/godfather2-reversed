// FUNC_NAME: StateMachine::resetToIdle
void __thiscall StateMachine::resetToIdle(void) {
    int* subObj = reinterpret_cast<int*>(this + 0xC4); // +0xC4: pointer to a sub-object/resource

    // Clear some flag at +0xB4
    *reinterpret_cast<uint32_t*>(this + 0xB4) = 0;

    // If sub-object exists, deinitialize it
    if (*subObj != 0) {
        FUN_004daf90(subObj); // sub-object cleanup
        *subObj = 0;
    }

    // Check current state at +0xB0
    if (*reinterpret_cast<int*>(this + 0xB0) == 4) {
        // If there's a pending transition object at +0xC0
        if (*reinterpret_cast<int*>(this + 0xC0) != 0) {
            // Call a global virtual function to release it
            (**(code**)(*DAT_01194538 + 4))(*reinterpret_cast<int*>(this + 0xC0), 0);
            *reinterpret_cast<uint32_t*>(this + 0xC0) = 0;
            *reinterpret_cast<int*>(this + 0xB0) = 0; // State -> idle
            *reinterpret_cast<void**>(this + 0x78) = PTR_LAB_00e38260; // vtable for idle
            return;
        }
        // No pending object: just reset state
        *reinterpret_cast<int*>(this + 0xB0) = 0;
        *reinterpret_cast<void**>(this + 0x78) = PTR_LAB_00e38260;
        return;
    }

    // Not state 4: force idle
    *reinterpret_cast<int*>(this + 0xB0) = 0;
    *reinterpret_cast<void**>(this + 0x78) = PTR_LAB_00e38260;
}