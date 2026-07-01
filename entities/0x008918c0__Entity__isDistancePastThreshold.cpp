// FUNC_NAME: Entity::isDistancePastThreshold
// Function at 0x008918c0: Checks if a distance computed from a sub-object at +0x90 exceeds a global threshold.
// If global threshold (DAT_00d5ccf8) < computed distance, returns true (1), else false (0).
// The callee FUN_008934e0 likely retrieves the distance/volume/intensity from a component (e.g., audio or physics).

bool __thiscall Entity::isDistancePastThreshold()
{
    float computedValue = 0.0f;
    // Get pointer to sub-object at offset +0x90 and compute value
    FUN_008934e0(*(int*)((int)this + 0x90), &computedValue);
    if (DAT_00d5ccf8 < computedValue)
    {
        return true;
    }
    return false;
}