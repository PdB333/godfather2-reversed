// FUNC_NAME: Entity::isFlagSet
byte __fastcall Entity::isFlagSet(int thisPtr)
{
    // +0x38: flags byte, bit 0 indicates some state (e.g., active, enabled, dirty)
    return *(byte *)(thisPtr + 0x38) & 1;
}