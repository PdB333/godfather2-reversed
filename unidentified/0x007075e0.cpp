// FUN_007075e0: Entity::setFlag
// Role: Sets or clears bit 0x80 in the flags field at offset +0x1d0.
// Called from multiple Entity-related methods (FUN_00854050, FUN_00855780, etc.).
void __thiscall Entity::setFlag(char enabled)
{
    // Access the flags member at offset 0x1d0
    if (enabled == '\x01')
    {
        // Set bit 7 (0x80) - e.g., marks the entity as "active", "dead", or "hidden"
        *(unsigned int *)(this + 0x1d0) |= 0x80;
    }
    else
    {
        // Clear bit 7
        *(unsigned int *)(this + 0x1d0) &= ~0x80;
    }
}