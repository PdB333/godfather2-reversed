// FUNC_NAME: Entity::shouldMaintainTarget

// Function at 0x006ba510: Determines if the entity should continue engaging a threat.
// Checks distance to threat position (param_2) and a secondary position (param_3, likely a safe spot or cover).
// Returns 0 if too close to threat, or if threat is hidden near secondary position (flag bit not set and no line of sight).
// Otherwise returns 1 (continue maintaining target).

bool __thiscall Entity::shouldMaintainTarget(float* threatPos, float* secondaryPos)
{
    float dx, dy, dz;
    float distSq;

    // Compute squared distance to threat position
    dx = *(float*)(this + 0xC0) - threatPos[0]; // +0xC0: position x
    dy = *(float*)(this + 0xC4) - threatPos[1]; // +0xC4: position y
    dz = *(float*)(this + 0xC8) - threatPos[2]; // +0xC8: position z (200 decimal = 0xC8)

    distSq = dx*dx + dy*dy + dz*dz;

    // If too close to threat, stop maintaining target
    if (distSq < g_squaredCloseRange) // _DAT_00d5e6f8
        return false;

    // Check if flag bit 1 is set (e.g., "isAiming" or "isInCombat"?)
    uint flags = *(uint*)(this + 0x54); // +0x54: behaviour flags
    bool flagBit1Set = ((flags >> 1) & 1) != 0;

    if (!flagBit1Set)
    {
        // Compute squared distance to secondary position
        dx = *(float*)(this + 0xC0) - secondaryPos[0];
        dy = *(float*)(this + 0xC4) - secondaryPos[1];
        dz = *(float*)(this + 0xC8) - secondaryPos[2];

        distSq = dx*dx + dy*dy + dz*dz;

        // If near secondary position and no line of sight, stop maintaining target
        if (distSq < g_squaredSecondaryRange) // _DAT_00d5e6fc
        {
            if (!FUN_006c0050(this + 0xC0, 0, 0)) // Likely line-of-sight check (position, flags, flags)
                return false;
        }
    }

    return true;
}