// FUNC_NAME: Player::evaluateCoverDistanceAndFlags
// Function address: 0x007f16b0
// Role: Computes distance to a target entity and sets cover-related flags based on bit fields in the target.
// Offsets: +0xec (int), +0xf0 (int), +0xf8 (float), +0x5e4 (byte)

void __thiscall Player::evaluateCoverDistanceAndFlags(Player* this, Entity* coverPoint)
{
    // If distance hasn't been computed yet (default 0), compute it now
    if (this->coverDistance == 0.0f)
    {
        // Assuming these functions return pointers to entities with position data
        Entity* someEntity = GetSomeEntity(0); // returns entity at iVar1
        Player* localPlayer = GetLocalPlayer(); // returns player at iVar2

        // Extract positions from the entities
        float dx = someEntity->position.x - localPlayer->position.x;
        float dy = someEntity->position.y - localPlayer->position.y;
        float dz = someEntity->position.z - localPlayer->position.z;

        // Compute distance and cache it
        this->coverDistance = sqrt(dx * dx + dy * dy + dz * dz);
    }

    // Reset some timers or counters
    this->coverTimer1 = 0;
    this->coverTimer2 = 0;

    // Check if the cover point has both required flags set (bit 0xB)
    // Offsets +0x970 and +0x974 likely contain bitfields for cover properties
    if ((coverPoint->coverFlags1 & (1 << 0xB)) && (coverPoint->coverFlags2 & (1 << 0xB)))
    {
        this->canUseCover = true;
    }
    else
    {
        this->canUseCover = false;
    }
}