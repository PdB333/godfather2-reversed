// FUNC_NAME: Player::computeCameraTransform
uint __thiscall Player::computeCameraTransform(int this, uint param_2) {
    uint result = *(uint*)&this[0x1c78]; // initial value from EAX? Actually, Ghidra shows in_EAX & 0xffffff00, likely a previous return value
    // Check if camera state is valid (not 0 and not 0x48 = disabled)
    if (*(int*)(this + 0x1c78) != 0 && *(int*)(this + 0x1c78) != 0x48) {
        // Get two transform pointers (e.g., current and target)
        void* pTransformA = (void*)FUN_00471610(); // returns a pointer to a 4x4 matrix
        void* pTransformB = (void*)FUN_00471610(); // returns another pointer
        // Compute interpolated transform: use translation of B, translation of A, orientation of A (Z axis at +0x20), and param_2
        result = FUN_007f7f30((int)pTransformB + 0x30, // translation of B
                              (int)pTransformA + 0x30, // translation of A
                              (int)pTransformA + 0x20, // orientation (Z axis) of A
                              param_2);
    }
    return result & 0xffffff00; // mask lower 8 bits (flags)
}