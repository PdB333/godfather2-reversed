// FUNC_NAME: TargetingManager::checkTargetInRange
// Address: 0x00746920
// This function checks if the current target is within a vertical range and horizontal distance.
// Returns a uint encoding success (low byte = 1) and an object ID derived from the target's address.

uint __thiscall TargetingManager::checkTargetInRange(float minVerticalDiff, float maxVerticalDiff, float maxHorizontalDistSq)
{
    // +0x5c: state/flags field (0 = inactive, 0x48 = invalid target)
    uint targetState = *(uint*)(this + 0x5c);

    // If no target or invalid, return state with low byte cleared
    if (targetState == 0 || targetState == 0x48)
    {
        return targetState & 0xffffff00;
    }

    // Get current target and self (likely the player or NPC)
    int* targetEntity = (int*)FUN_00471610(); // getTargetEntity()
    int* selfEntity   = (int*)FUN_00471610(); // getSelfEntity()

    // Compute vertical difference (Y-axis at +0x34)
    float verticalDiff = *(float*)(targetEntity + 0x34) - *(float*)(selfEntity + 0x34);

    // Extract a partial ID from target's position pointer (shifted right 8 bits)
    uint3 encodedId = (uint3)((uint)(targetEntity + 0x30) >> 8);

    // Check vertical range
    if ((minVerticalDiff < verticalDiff) && (verticalDiff <= maxVerticalDiff))
    {
        // Compute horizontal distance squared (X at +0x30, Z at +0x38)
        float xDiff = *(float*)(targetEntity + 0x38) - *(float*)(selfEntity + 0x38);
        float zDiff = *(float*)(targetEntity + 0x30) - *(float*)(selfEntity + 0x30);
        float distSq = xDiff * xDiff + zDiff * zDiff;

        if (distSq <= maxHorizontalDistSq)
        {
            // Success: combine encoded ID with low byte 1
            return CONCAT31(encodedId, 1); // (encodedId << 8) | 1
        }
    }

    // Failure: return encoded ID shifted left (low byte 0)
    return (uint)encodedId << 8;
}