// FUNC_NAME: Entity::tryInteract
bool __thiscall Entity::tryInteract(uint targetIndex)
{
    char isValid;
    Player* player;
    float verticalDiff;
    float dx;
    float dz;
    float distSq;

    isValid = isValidTarget(targetIndex);
    if (!isValid) {
        return false;
    }

    player = getPlayer();
    // Check vertical tolerance: if this->interactionMaxRange (0x78) is less than global override (someMaxRange)
    // or if the absolute Y difference (using bitwise AND to mask sign) is within this->interactionMaxRange
    if (((this->interactionMaxRange < g_someMaxRange) ||
         (float)((uint)(player->position.y - this->targetPosition.y) & g_absMask) <= this->interactionMaxRange)) &&
        // Check horizontal distance squared against this->interactionRadius (0x74)
        (dx = player->position.x - this->targetPosition.x,
         dz = player->position.z - this->targetPosition.z,
         distSq = dx*dx + dz*dz,
         distSq <= this->interactionRadius))
    {
        // Check line of sight from target position
        if (isPointVisible(&this->targetPosition)) {
            // Attempt to start interaction (second param 0 means maybe no options?)
            return (startInteraction(targetIndex, 0) == 0);
        }
    }
    return false;
}