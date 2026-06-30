// FUNC_NAME: PlayerSM::canAttackTarget
int __thiscall PlayerSM::canAttackTarget(int thisPtr, int targetEntity)
{
    uint flags;
    int componentPtr;
    int componentResult;
    char* componentResultPtr;
    float distance;
    float angle;

    flags = *(uint *)(thisPtr + 0xe4); // +0xe4: bitfield flags (e.g., state flags)
    // First condition: bit1 of flags is NOT set
    if (((flags >> 1) & 1) == 0)
    {
        componentPtr = *(int *)(thisPtr + 0xf4); // +0xf4: pointer to a component (e.g., CombatComponent)
        if ((componentPtr != 0) &&
            (componentResult = (*(int (**)(void))(**(int **)componentPtr + 0x34))(), // virtual call at vtable+0x34 (index 13) -> returns a pointer
             componentResult != 0))
        {
            componentResultPtr = (char *)componentResult;
            // Check float at +0x2c (e.g., max range) against global threshold
            if (*(float *)(componentResultPtr + 0x2c) != g_floatMaxRange) // _DAT_00d577a0
            {
                // Check some delta value (counter or ID difference) against global range
                if ((uint)(g_intSomeLimit - *(int *)(componentResultPtr + 0x40)) < g_uintDeltaThreshold) // DAT_01205224, DAT_00e5192c
                {
                    distance = FUN_0045c470(targetEntity, componentResultPtr + 0x20); // +0x20: position vector
                    // Compare distance to global threshold (e.g., min dist, or angle)
                    if (distance < g_floatDistanceThreshold) // _DAT_00d64700
                    {
                        return 1;
                    }
                }
            }
        }
        // Additional check: some other condition on targetEntity
        if (FUN_0074c250(targetEntity) != '\0')
        {
            return 1;
        }
    }

    // Second condition block: check action state at +0xa4
    if ((*(int *)(thisPtr + 0xa4) != 0) && (*(int *)(thisPtr + 0xa4) != 0x48)) // +0xa4: current state ID (0 = idle, 0x48 = some state)
    {
        // Check if target is within some angle/field of view (1.0f = threshold)
        if (FUN_006ae680(targetEntity, 0x3f800000, 0) != '\0') // 0x3f800000 = 1.0f
        {
            return 1;
        }
    }
    return 0;
}