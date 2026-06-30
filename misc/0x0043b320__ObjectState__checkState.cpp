// FUNC_NAME: ObjectState::checkState
uint __thiscall ObjectState::checkState(char *this) {
    // +0x00: state flag (non-zero means active)
    if (this[0] != '\0') {
        // +0x04: valueA, +0x08: valueB
        int valueA = *(int *)(this + 4);
        int valueB = *(int *)(this + 8);
        // Take upper 24 bits of valueA and concatenate with equality flag
        uint upperBits = (uint)((int3)((uint)valueA >> 8));
        uint equalityMask = (uint)(valueA == valueB);
        return (upperBits << 8) | equalityMask;
    } else {
        // +0x0C: valueC, return whether it is zero
        int valueC = *(int *)(this + 0xC);
        return (uint)(valueC == 0);
    }
}