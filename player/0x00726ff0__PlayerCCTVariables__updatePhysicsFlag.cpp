// FUNC_NAME: PlayerCCTVariables::updatePhysicsFlag
void __thiscall PlayerCCTVariables::updatePhysicsFlag(void)
{
    // Check if bit 5 (0x20) is set at offset +0x114 (flags byte)
    if ((*(byte *)((int)this + 0x114) & 0x20) != 0) {
        // Update physics-related values: +0xa0, +0xa4 (likely Vector2 or components), +0x50 (another position/velocity)
        FUN_009c6320((int)this + 0xa0, (int)this + 0xa4, (int)this + 0x50);
        // Clear the flag
        *(byte *)((int)this + 0x114) = *(byte *)((int)this + 0x114) & 0xdf;
    }
    return;
}