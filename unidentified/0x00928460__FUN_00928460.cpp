// FUNC_NAME: SomeClass::setMode
void __thiscall setMode(int this, int newMode) {
    if (*(int *)(this + 0x78) != newMode) {
        *(int *)(this + 0x78) = newMode; // +0x78: mode
        FUN_005a04a0("ModeChanged", 0, &DAT_00d87b2c, 0); // Fire event
        if (*(int *)(this + 0x78) == 1) {
            *(uint *)(this + 0x50) = *(uint *)(this + 0x50) | 2; // +0x50: flags, set bit 1
            return;
        }
        *(uint *)(this + 0x50) = *(uint *)(this + 0x50) & 0xfffffffd; // Clear bit 1
    }
}