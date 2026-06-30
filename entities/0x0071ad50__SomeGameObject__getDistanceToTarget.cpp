// FUNC_NAME: SomeGameObject::getDistanceToTarget
float __fastcall SomeGameObject::getDistanceToTarget(int this)
{
    // +0x20: pointer to entity/position component 
    int* pEntity = *(int**)(this + 0x20);
    float distance = *g_defaultDistance; // global fallback value (e.g., FLT_MAX)

    if (pEntity != nullptr)
    {
        // FUN_00471610 returns a pointer to a target (e.g., player or camera)
        int* pTarget = FUN_00471610(); // likely returns a position holder
        if (pTarget != nullptr)
        {
            // Offsets: entity position at +0x44 (x), +0x48 (y), +0x4c (z)
            // Target position at +0x30 (x), +0x34 (y), +0x38 (z)
            float dx = *(float*)(pEntity + 0x44) - *(float*)(pTarget + 0x30);
            float dy = *(float*)(pEntity + 0x48) - *(float*)(pTarget + 0x34);
            float dz = *(float*)(pEntity + 0x4c) - *(float*)(pTarget + 0x38);
            distance = sqrt(dx * dx + dy * dy + dz * dz);
        }
    }
    return distance;
}