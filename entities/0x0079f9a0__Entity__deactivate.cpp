// FUNC_NAME: Entity::deactivate
void __thiscall Entity::deactivate(void)
{
    // Check if component pointer at +0x2B80 is non-null
    if (*(int *)(this + 0x2B80) != 0) {
        // Release or cleanup the component
        FUN_004df600();
    }
    // Clear bit 14 (0x4000) of flags at +0x24A4 (likely "active" flag)
    *(uint *)(this + 0x24A4) &= 0xFFFFBFFF;
}