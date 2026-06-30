// FUNC_NAME: SomeClass::cleanupChildren
// Address: 0x006d6460
// Role: Releases two child objects if they exist.
void __thiscall cleanupChildren(void) {
    if (*(int*)((char*)this + 0x28) != 0) {
        FUN_004daf90((int)this + 0x28); // release first child at offset +0x28
    }
    if (*(int*)((char*)this + 0x30) != 0) {
        FUN_004daf90((int)this + 0x30); // release second child at offset +0x30
    }
}