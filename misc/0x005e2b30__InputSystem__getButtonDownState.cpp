// FUNC_NAME: InputSystem::getButtonDownState
uint __thiscall InputSystem::getButtonDownState(void *this, uint param_1) {
    // Function at 0x005e2b30
    // param_1 unknown, but may be a button mask
    uint result;

    if (*(byte *)(DAT_0122350c + 0x1744) != 0) {  // Check global input enabled flag
        uint managerPtr = FUN_005e2150();          // Get input device manager
        if (managerPtr != 0) {
            // vtable at *DAT_01223510, method at offset 0x98
            // Object is at managerPtr + 0x1cc (probably InputDevice *)
            result = (**(code (__thiscall **)(int, uint))(*(int *)DAT_01223510 + 0x98))
                     (*(int *)(managerPtr + 0x1cc), param_1);
            return result;
        }
    }
    // If disabled or manager null, return only high 24 bits (low byte cleared)
    return in_EAX & 0xFFFFFF00;
}