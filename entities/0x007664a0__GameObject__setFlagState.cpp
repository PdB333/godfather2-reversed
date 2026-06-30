// FUNC_NAME: GameObject::setFlagState
void __thiscall GameObject::setFlagState(bool enable, uint flagMask) {
    uint currentFlags = *(uint *)(this + 0xc88); // +0xC88: bit flags field

    if (enable == false) {
        // Clear bits: only act if any of the flagMask bits are currently set
        if ((~flagMask & currentFlags) != currentFlags) {
            // Notify flag change (0x10 indicates a flag update)
            (**(code **)(*(int *)(this + 0x58) + 0x28))(0x10);
            *(uint *)(this + 0xc88) = currentFlags & ~flagMask;
        }
    } else {
        // Set bits: only act if at least one flagMask bit is not already set
        if ((currentFlags | flagMask) != currentFlags) {
            (**(code **)(*(int *)(this + 0x58) + 0x28))(0x10);
            *(uint *)(this + 0xc88) = currentFlags | flagMask;
        }
    }
}