// FUNC_NAME: PlayerReputationTracker::computeReputationValue
int __fastcall PlayerReputationTracker::computeReputationValue(int this)
{
    float fVar1;
    float fVar2;
    char cVar3;
    int iVar4;
    int iVar5;
    int uVar6;
    int local_8;

    *(int *)(this + 0xCC) = 0; // m_computedValue = 0

    // Check if settings pointer is valid
    if (*(int *)(this + 0x40) != 0) // m_pSettings
    {
        iVar4 = isSettingsValid(*(int *)(this + 0x40)); // FUN_008c74d0
        if (iVar4 != 0)
        {
            // State type 0 – generate random base then multiply
            if (*(int *)(this + 0xC4) == 0) // m_stateType
            {
                iVar4 = getRandomBaseValue(); // FUN_008bece0
                fVar1 = (float)iVar4;
                if (iVar4 < 0)
                {
                    fVar1 = fVar1 + DAT_00e44578; // adjust for negative conversion
                }
                local_8 = (int)(long long)ROUND(fVar1 * *(float *)(this + 0xD0)); // m_multiplier
                *(int *)(this + 0xCC) = local_8;
                return local_8;
            }

            // State type 1 – requires target pointer and certain conditions
            if ((*(int *)(this + 0xC4) == 1) && // m_stateType
                (*(int *)(this + 0xC0) != 0) &&  // m_pTarget
                (iVar4 = hasTarget(), iVar4 != 0) && // FUN_0084a410
                (cVar3 = isTargetValid(), cVar3 != '\0')) // FUN_0084a670
            {
                // Get two values from target structure
                iVar4 = *(int *)(**(int **)(this + 0xC0) + 4); // pTarget->field_4
                iVar5 = getTargetProperty(); // FUN_0084a5b0
                fVar1 = (float)iVar5;
                if (iVar5 < 0)
                {
                    fVar1 = fVar1 + DAT_00e44578;
                }
                fVar2 = (float)iVar4;
                if (iVar4 < 0)
                {
                    fVar2 = fVar2 + DAT_00e44578;
                }
                // If the ratio is <= 0, call getTargetProperty again (perhaps discard)
                if (fVar1 / fVar2 <= 0.0f)
                {
                    getTargetProperty(); // FUN_0084a5b0
                }
                else
                {
                    getTargetProperty(); // FUN_0084a5b0
                }
                uVar6 = finalizeValue(); // FUN_00b9a1c0
                *(int *)(this + 0xCC) = uVar6;
            }
        }
    }
    return *(int *)(this + 0xCC);
}