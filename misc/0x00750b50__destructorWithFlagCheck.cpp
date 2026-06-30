// FUNC_NAME: destructorWithFlagCheck
void __fastcall destructorWithFlagCheck(SomeClass* this)
{
    // Set vtable pointer to static vtable (object is being destroyed)
    this->vtable = &PTR_LAB_00d6492c;

    // Check bit 7 of flags at offset +0x18 (dword index, actual byte offset 0x60)
    if ((this->flags & 0x80) != 0) {
        FUN_0072cb10(0);  // Clear some flag or perform action
        this->flags &= ~0x80;  // Clear bit 7
    }

    FUN_009a5a10();  // Unknown cleanup
    FUN_00750870();  // Unknown cleanup

    // Free owned pointers at offsets +0x26 (byte offset 0x98) and +0x29 (byte offset 0xA4)
    if (this->ptrAt98 != nullptr) {
        FUN_004daf90(this->ptrAt98);  // Free / delete
    }
    if (this->ptrAtA4 != nullptr) {
        FUN_004daf90(this->ptrAtA4);  // Free / delete
    }

    FUN_004ac1e0();  // Final cleanup (e.g., operator delete)
    return;
}