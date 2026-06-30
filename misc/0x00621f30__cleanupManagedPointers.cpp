// FUNC_NAME: cleanupManagedPointers
void __thiscall cleanupManagedPointers(void) {
    // Check if first managed pointer at +0x10 exists
    if (*(int*)(this + 0x10) != 0) {
        // Call Release (vtable+4) on the object pointed by vtable at +0xc
        (*(void(__thiscall**)(int, int))(*(int*)(this + 0xc) + 4))(*(int*)(this + 0x10), 0);
        *(int*)(this + 0x10) = 0; // Clear pointer
    }
    // Call finalize (vtable+0xc) on the first vtable object
    (*(void(__thiscall**)(void))(*(int*)(this + 0xc) + 0xc))();

    // Check if second managed pointer at +0x8 exists
    if (*(int*)(this + 0x8) != 0) {
        // Call Release (vtable+4) on the object pointed by vtable at +0x4
        (*(void(__thiscall**)(int, int))(*(int*)(this + 0x4) + 4))(*(int*)(this + 0x8), 0);
        *(int*)(this + 0x8) = 0; // Clear pointer
    }
    // Call finalize (vtable+0xc) on the second vtable object
    (*(void(__thiscall**)(void))(*(int*)(this + 0x4) + 0xc))();
    return;
}