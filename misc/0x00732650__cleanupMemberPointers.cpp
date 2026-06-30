// FUNC_NAME: cleanupMemberPointers
// Function address: 0x00732650
// Releases multiple owned pointers by calling appropriate release functions.
// Offsets suggest a class with several dynamically allocated member objects.
void __thiscall cleanupMemberPointers(void) {
    // Release member at +0x54 (likely an object with its own destructor)
    if (*(int*)(this + 0x54) != 0) {
        FUN_004daf90(this + 0x54);  // releases pointer and nulls it
    }
    // Release member at +0x4c
    if (*(int*)(this + 0x4c) != 0) {
        FUN_004daf90(this + 0x4c);
    }
    // Release member at +0x3c (direct call to deallocator)
    if (*(int*)(this + 0x3c) != 0) {
        FUN_009c8f10(*(int*)(this + 0x3c));
    }
    // Release member at +0x34
    if (*(int*)(this + 0x34) != 0) {
        FUN_004daf90(this + 0x34);
    }
    // Release member at +0x1c
    if (*(int*)(this + 0x1c) != 0) {
        FUN_009c8f10(*(int*)(this + 0x1c));
    }
    // Release member at +0x14
    if (*(int*)(this + 0x14) != 0) {
        FUN_004daf90(this + 0x14);
    }
}