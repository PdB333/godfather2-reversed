// FUNC_NAME: Player::lazyInitSubsystem
void __thiscall Player::lazyInitSubsystem() {
    // +0x1bc8: pointer to allocated subsystem object
    if (*(int*)(this + 0x1bc8) != 0) {
        return;
    }

    // Parameters for creation: {2, 0x10, 0} – likely {flags, alignment, unknown}
    struct CreationParams {
        int field0;  // 2
        int field4;  // 0x10
        int field8;  // 0
    } params = {2, 0x10, 0};

    // Allocate a block of 0x5f0 bytes (size of the subsystem object)
    int iVar1 = FUN_009c8ed0(0x5f0, &params);
    if (iVar1 == 0) {
        iVar1 = 0;  // allocation failed
    } else {
        // Construct the actual object if allocation succeeded
        iVar1 = FUN_007f1c30();
    }

    // Store the created object (or null) at the field
    *(int*)(this + 0x1bc8) = iVar1;

    if (iVar1 != 0) {
        // Success: enable subsystem flags
        // +0x1b94: global state flags (set bit 0x400000)
        *(unsigned int*)(this + 0x1b94) |= 0x400000;
        // +0x974: another flag field (set bit 0x10)
        *(unsigned int*)(this + 0x974) |= 0x10;

        // Notify system of successful initialization
        FUN_009c4ea0(0);  // likely "onSubsystemChange"(false) or similar
        FUN_007f60e0();   // update dependent systems
    } else {
        // Failure: clear the subsystem bit
        *(unsigned int*)(this + 0x974) &= ~0x10;
        // Notify system of failure
        FUN_009c4ea0(1);
        FUN_007f60e0();
    }
}