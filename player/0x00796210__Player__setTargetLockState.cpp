// FUNC_NAME: Player::setTargetLockState
void __thiscall Player::setTargetLockState(bool enable)
{
    // Flags field at offset 0x2BC (700 bytes)
    uint flags = *(uint *)(this + 700);
    if (enable)
    {
        // Set bit 29 to enable target lock
        *(uint *)(this + 700) = flags | 0x20000000;
        // Notify subsystem to enter locked state
        FUN_00794600(1); // setAimLockState(true)
    }
    else
    {
        // Clear bit 29
        *(uint *)(this + 700) = flags & 0xDFFFFFFF;
        // Query current aim state (0,1) and apply it
        int state = FUN_00795a90(0, 1); // getCurrentAimLockState()
        FUN_00794600(state); // setAimLockState(state)
    }
}