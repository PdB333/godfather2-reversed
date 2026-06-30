// FUNC_NAME: DataArrayManager::setValueAtIndex
bool DataArrayManager::setValueAtIndex(unsigned short index, float value) {
    // Check if index is within range (0..127) and if the manager is active (pointer at +0x580)
    if (index > 0x7f || *(int*)(this + 0x580) == 0) {
        return false;
    }

    // Array of 248-byte structs starting at +0x5a4; each element has a float at offset 0 within the struct
    float* target = (float*)(this + 0x5a4 + index * 0xf8);

    // If the current value already matches, no update needed
    if (*target == value) {
        return true;
    }

    // Acquire some system, set value via helper calls, then store
    if (FUN_005e9d10() != 0) {  // Likely singleton getter or resource lock
        FUN_00c9eac0();          // Begin operation (maybe enter critical section)
        FUN_00ca4e90(0, value);  // Push value to internal buffer or queue
        FUN_00c9eae0();          // Commit or release lock
        *target = value;         // Store the new value
        return true;
    }
    return false;
}