// FUNC_NAME: DebugManager::updateDebugDisplay
void __fastcall DebugManager::updateDebugDisplay(int this) {
    // Call some initialization/update function (no parameters)
    updateSomething();

    // Call a member function on a sub-object at offset 0x50
    subObjectUpdate(this + 0x50);

    // Check a flag at offset 0x8c
    if (*(char *)(this + 0x8c) != 0) {
        // Clear bit 2 in a global game manager's field at offset 0x10
        // gpGameManager points to a singleton with flags
        *(uint *)(gpGameManager + 0x10) &= 0xfffffffb;
        // Reset the flag
        *(char *)(this + 0x8c) = 0;
    }

    // Prepare a local variable to deallocate something
    int local_string = DAT_01130368; // Global string or resource pointer
    int local_unknown1 = 0;
    int local_unknown2 = 0;
    releaseResource(&local_string, 0); // FUN_00408a00 - might be a deallocation call

    // Check another flag at offset 0x8d
    if (*(char *)(this + 0x8d) != 0) {
        // Call a virtual function at offset 0x2c from the vtable pointed by DAT_01129a74
        // The vtable pointer is stored in a global, so this might be a singleton pattern
        (*(code **)(*(int *)DAT_01129a74 + 0x2c))();
    }
}