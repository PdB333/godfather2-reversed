// FUNC_NAME: clearFlag8AndNotify
void __fastcall clearFlag8AndNotify(SomeObject* this) {
    // Check if bit 8 (0x100) is set in flags at offset 0x60
    if ((*(uint*)((uintptr_t)this + 0x60) >> 8 & 1) != 0) {
        // Clear bit 2 (0x4) in global state at +0x10
        *(uint*)(*(uintptr_t*)DAT_011298d4 + 0x10) &= ~0x4;
        // Call notification/trigger function
        notifyEvent();
        // Clear bit 8 in the object's flags
        *(uint*)((uintptr_t)this + 0x60) &= ~0x100;
    }
}