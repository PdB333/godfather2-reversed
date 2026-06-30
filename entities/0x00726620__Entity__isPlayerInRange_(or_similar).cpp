// FUNC_NAME: Entity::isPlayerInRange (or similar)
// Address: 0x00726620
// This function checks if the player (global entity) is within a certain range of this entity.
// Returns a packed value: high 24 bits contain some identifier from the player, low 8 bits are 1 if in range.
int __fastcall Entity::isPlayerInRange(Entity* thisPtr)  // ECX = thisPtr
{
    // Get player object (probably from global state)
    Entity* player = getPlayer(); // FUN_00471610 -> assumed to return Entity*

    // Extract some ID from player's offset 0x30 (likely a packed identifier)
    unsigned int idHighBytes = (unsigned int)(player->field_0x30) >> 8; // high 24 bits of the ID

    // Global constants (likely configured in data)
    extern float gMaxVerticalTolerance; // _DAT_00d577a0
    extern unsigned int gVerticalMask;  // DAT_00e44680 (probably 0x7FFFFFFF to ignore sign)

    // Check vertical condition first: if this entity's vertical tolerance is less than global max,
    // OR if the masked difference in Y is within the tolerance.
    float dy = player->posY - thisPtr->posY; // offset: iVar1+0x34 - this+0x134
    float tolerance = thisPtr->verticalTolerance; // +0x78
    if ((tolerance < gMaxVerticalTolerance) ||
        ((float)(((unsigned int)dy) & gVerticalMask) <= tolerance))
    {
        // Compute squared distance in XZ plane
        float dx = player->posX - thisPtr->posX; // +0x30, +0x130
        float dz = player->posZ - thisPtr->posZ; // +0x38, +0x138
        float distSq = dz*dz + dy*dy + dx*dx; // dy already computed

        // Check if within the squared range threshold
        float rangeSq = thisPtr->rangeSquared; // +0x74
        if (distSq <= rangeSq)
        {
            // In range: return ID with low byte set to 1
            return (idHighBytes << 8) | 1;
        }
    }
    // Not in range: return ID with low byte 0
    return (idHighBytes << 8);
}