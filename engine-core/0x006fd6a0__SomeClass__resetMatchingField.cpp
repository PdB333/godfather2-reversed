// FUNC_NAME: SomeClass::resetMatchingField
void __thiscall SomeClass::resetMatchingField(int valueToMatch)
{
    // Check if field at +0x208 equals the given value
    if (*(int*)(this + 0x208) == valueToMatch) {
        // Reset to -1 (invalid/uninitialized)
        *(int*)(this + 0x208) = 0xFFFFFFFF;
        // Log or handle debug string (likely a format or label)
        FUN_005e6640(&LAB_006fd640);
    }
}