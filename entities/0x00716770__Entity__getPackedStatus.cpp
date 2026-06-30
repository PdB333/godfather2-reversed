// FUNC_NAME: Entity::getPackedStatus
uint __fastcall Entity::getPackedStatus(void) const
{
    // Read packed flags from offset 0x154
    // Mask keeps bit 0 and bits 8-31 after shifting right by 3
    // This isolates original bit 3 and bits 11-31 (likely a flag + 21-bit value)
    return *(uint *)((int)this + 0x154) >> 3 & 0xffffff01;
}