// FUNC_NAME: SingletonManager::constructor
// Function at 0x00957410 - Constructor for a singleton manager class.
// Sets up vtable pointers, initializes a global flag, and calls sub-initializer.
// If param_2 has bit 0 set, calls destructor/deallocator (likely for heap cleanup).

undefined4 * __thiscall SingletonManager::constructor(SingletonManager *this, byte allocFlag)
{
    // Set vtable pointer at +0x00
    this->vtable = &PTR_FUN_00d8c1b8;
    // Set vtable pointer at +0x10 (offset 4 words)
    this->field_0x10 = &PTR_LAB_00d8c194;
    // Set vtable pointer at +0x4C (offset 0x13 words)
    // Note: Two successive assignments might indicate a bug or different vtable slot in real code.
    this->field_0x4C = &PTR_LAB_00d8c190;
    this->field_0x4C = &PTR_LAB_00d8c18c;

    // Reset global singleton flag to 0
    DAT_01130020 = 0;

    // Call base or sub-initializer
    FUN_005c16e0();

    // If allocated on heap (allocFlag & 1), call destructor (or deallocator) on this
    if ((allocFlag & 1) != 0) {
        FUN_005c4480(this);
    }

    return this;
}