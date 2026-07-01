// FUNC_NAME: Player::isInteractionAllowed
uint8 __thiscall Player::isInteractionAllowed(int this, int flags)
{
    // Call method on component at offset +0x58
    FUN_004a8ec0(*(int *)(this + 0x58));
    // Update some global state (e.g., input or timing)
    FUN_007962e0();
    // Return the 4th byte (bits 24-31) of the input flags as a boolean
    return (uint8)((flags >> 24) & 0xFF);
}