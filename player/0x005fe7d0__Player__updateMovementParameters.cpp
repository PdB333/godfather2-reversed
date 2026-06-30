// FUNC_NAME: Player::updateMovementParameters
void Player::updateMovementParameters()
// Address: 0x005fe7d0
// Likely called each frame to update movement-related parameters based on character state flags.
// Accessing this pointer (via ECX) with offsets: +0xb4 (flags), +0xf8, +0x104, +0x110.
// Calls base update then passes parameters based on bit flags to another function.
{
    // Call base class update (general per-frame logic)
    baseUpdate();

    // Local variables correspond to movement-related values (e.g., animation speeds, offsets)
    float param1 = 0.0f; // +0x0 (local_4)
    float param2 = 0.0f; // +0x4 (local_8)
    float param3 = 0.0f; // +0x8 (local_c)

    // Check bit 6 of flags at +0xb4 (0x40 mask)
    // If clear, use the value at +0xf8 (likely a movement parameter like walk speed)
    if ((*(uint32*)(this + 0xb4) >> 6 & 1) == 0) // Bit 6: maybe "isInCombat" or "isAiming"
    {
        param1 = *(float*)(this + 0xf8); // e.g., base movement speed
    }

    // Check bit 5 of flags at +0xb4 (0x20 mask)
    // If clear, use values at +0x104 and +0x110 (e.g., strafe speed and rotation rate)
    if ((*(uint32*)(this + 0xb4) >> 5 & 1) == 0) // Bit 5: maybe "isInVehicle" or "isCrouching"
    {
        param2 = *(float*)(this + 0x104); // e.g., lateral movement speed
        param3 = *(float*)(this + 0x110); // e.g., rotation angular speed
    }

    // Apply the selected parameters to the movement system
    applyMovementParameters(param1, param2, param3); // FUN_0056b8a0
}