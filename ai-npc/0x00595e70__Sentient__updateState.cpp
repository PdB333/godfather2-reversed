// FUNC_NAME: Sentient::updateState
void Sentient::updateState(int param_2) {
    uint* flagsPtr = reinterpret_cast<uint*>(reinterpret_cast<uint8_t*>(this) + 4); // +0x04: flags
    uint flags = *flagsPtr;

    // Check bit 1 (0x02) - if not set, perform some transformation
    if ((flags & 0x02) == 0) {
        float value = FUN_00595490(param_2); // likely random or math function
        if (flags & 0x01) {
            value = FUN_00595490(value);
            FUN_00595490(value);
        }
        // Call a function that fills local variables (likely a vector or quaternion)
        Vector3 vec; // local_20, local_1c, local_18
        FUN_0059bb50(&vec); // fills vec
        // Call a method on a global singleton (DAT_012055a8) with vtable offset 0x34
        // This might be something like "setTransform" or "applyOffset"
        (**(void (__thiscall**)(Vector3, Vector3, Vector3, void*))(*DAT_012055a8 + 0x34))(vec, vec, vec, reinterpret_cast<uint8_t*>(this) + 0x8C); // +0x8C = this+0x23*4
    }

    // Check bit 2 (0x04) - if not set, another transformation
    if ((flags & 0x04) == 0) {
        float value = FUN_00595490(param_2);
        if (flags & 0x01) {
            value = FUN_00595490(value);
            FUN_00595490(value);
        }
        FUN_0059bc30(flagsPtr); // likely updates flags or state
    }

    // Check bit 3 (0x08) - if set, call virtual function at vtable+0x10 and return
    if (flags & 0x08) {
        (this->*reinterpret_cast<void (__thiscall Sentient::*)()>(this->vtable[0x10 / 4]))();
        return;
    }

    // Otherwise, perform more processing
    FUN_00595490(param_2);
    char result = FUN_00595610(); // some condition check
    if (result == 0) {
        *flagsPtr &= ~0x08; // clear bit 3
    } else {
        *flagsPtr |= 0x08; // set bit 3
    }

    // Call virtual function at vtable+0x0c with arguments
    // Note: iStack_24 is uninitialized in decompiled output; likely a stack variable that should be set earlier
    int someValue; // iStack_24 - uninitialized, possibly a bug in decompilation
    this->vtable[0x0c / 4](someValue, this->field_0xAC); // +0xAC = this+0x2b*4
    this->field_0xA4 = someValue; // +0xA4 = this+0x29*4
    this->field_0xA8 = static_cast<int>(static_cast<float>(this->field_0xA4)); // +0xA8 = this+0x2a*4, conversion from float

    // Call virtual function at vtable+0x10 again
    (this->*reinterpret_cast<void (__thiscall Sentient::*)()>(this->vtable[0x10 / 4]))();
}