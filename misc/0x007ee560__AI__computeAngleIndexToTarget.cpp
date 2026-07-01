// FUNC_NAME: AI::computeAngleIndexToTarget
// Address: 0x007ee560
// Returns an integer index representing a discretized angle difference between the player's heading and the direction to a target entity.
// Uses global constants for threshold and scaling.

int AI::computeAngleIndexToTarget()
{
    // Retrieve two entity pointers (likely player and current target)
    Entity* pPlayer = (Entity*)FUN_00471610();  // getPlayer() (or sim entity 1)
    Entity* pTarget = (Entity*)FUN_00471610();  // getTarget() (or sim entity 2)

    // Compute difference vector between target and player positions
    // Entity position offsets: +0x30 = x, +0x34 = y, +0x38 = z
    Vector3 diff;
    diff.x = pTarget->position.x - pPlayer->position.x; // +0x30
    diff.y = pTarget->position.y - pPlayer->position.y; // +0x34
    diff.z = pTarget->position.z - pPlayer->position.z; // +0x38

    // Normalize the vector (or compute magnitude/ angle) – FUN_0056afa0 likely a vector normalize function
    FUN_0056afa0(&diff, &diff);

    // Global constant: probably player's current heading (forward direction's x-component or angle)
    float heading = g_HeadingX;      // DAT_00d70028

    // Unknown call – possibly synchronization or debug print
    FUN_00b9a9fa();

    // After normalization, diff.x is the x-component of the unit direction vector (cosine of angle from forward)
    float directionCos = diff.x;

    // Another unknown call
    FUN_00b9a9fa();

    // Compute angle difference (in cosine space? or raw angle?)
    float angleDiff = heading - directionCos;

    // Global threshold and scale for discretization
    float threshold = g_AngleThreshold; // DAT_00d5d70c
    float scale = g_AngleScale;         // _DAT_00d70024

    // Clamp and scale to integer index
    if (threshold <= angleDiff)
    {
        return (int)((angleDiff - threshold) * scale);
    }
    if (angleDiff < 0.0f)
    {
        angleDiff += threshold;
    }
    return (int)(angleDiff * scale);
}