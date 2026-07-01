// FUNC_NAME: PlayerDamageHandler::processImpactForce
// Reconstructed C++ function for calculateImpactForce (0x008c4bb0)
// Calculates the final force for an impact based on hit type, player stats, and random modifiers

float __thiscall PlayerDamageHandler::processImpactForce(void* thisPtr, float hitDataPtr, char param_3)
{
    float fVar1;
    float fVar2;
    float fVar3;
    int iVar4;
    float10 fVar5;
    float10 fVar6;
    float10 fVar7;
    float10 fVar8;

    // Store the hit data pointer for later processing (offset +0x19C)
    *(float*)((int)thisPtr + 0x19C) = hitDataPtr;

    // Check hit type (offset +0xC4 in hit data; 1 = special type?)
    if (*(int*)((int)hitDataPtr + 0xC4) == 1)
    {
        fVar5 = (float10)FUN_008bd630();                          // Get random float or time delta?
        iVar4 = *(int*)((int)thisPtr + 0x19C);                     // Re-fetch hit data pointer
        fVar6 = (float10)FUN_008be7f0(*(undefined4*)(iVar4 + 0x40)); // Get some per‑frame multiplier

        hitDataPtr = 0.0f;
        if (*(int*)(DAT_0112A66C + 8) == *(int*)(iVar4 + 0x48))   // Check if hit belongs to player
        {
            hitDataPtr = *(float*)(DAT_0112F938 + 0xB4);          // Player‑specific force modifier
        }

        fVar7 = (float10)*(int*)(iVar4 + 0x68);                   // Signed integer from hit data
        if (*(int*)(iVar4 + 0x68) < 0)
        {
            fVar7 = fVar7 + (float10)DAT_00E44578;                // Convert negative to positive? (constant)
        }

        hitDataPtr = (float)(fVar7 * (float10)*(float*)(DAT_0112F938 + 0x4C) +
                             (float10)hitDataPtr +
                             fVar6 * (float10)*(float*)(*(int*)((int)thisPtr + 0x1D0) + 0x34) *
                             (float10)*(float*)(DAT_0112F938 + 0x94) +
                             (float10)(float)fVar5);

        if (param_3 == '\0')                                       // Extra random? (flag)
        {
            fVar5 = (float10)FUN_008C1040(*(undefined4*)(DAT_0112F938 + 0xB8));
            hitDataPtr = (float)(fVar5 + (float10)hitDataPtr);
        }

        // Add base damage from hit data (double dereference at offset +0x50)
        fVar8 = (float10)(*(float*)(**(int**)(*(int*)((int)thisPtr + 0x19C) + 0xC0) + 0x50) + hitDataPtr);
    }
    else
    {
        fVar5 = (float10)FUN_008bd630();
        iVar4 = *(int*)((int)thisPtr + 0x19C);
        fVar6 = (float10)FUN_008be7f0(*(undefined4*)(iVar4 + 0x40));

        fVar3 = *(float*)(*(int*)((int)thisPtr + 0x1D0) + 0x34);  // Local multiplier from damage component
        fVar1 = *(float*)(DAT_0112F938 + 0x94);                   // Global multiplier
        _param_3 = 0.0f;
        if (*(int*)(DAT_0112A66C + 8) == *(int*)(iVar4 + 0x48))
        {
            _param_3 = *(float*)(DAT_0112F938 + 0xB4);            // Player bonus
        }

        fVar7 = (float10)*(int*)(iVar4 + 0x68);
        if (*(int*)(iVar4 + 0x68) < 0)
        {
            fVar7 = fVar7 + (float10)DAT_00E44578;
        }

        fVar2 = *(float*)(DAT_0112F938 + 0x4C);                  // Global linear factor

        fVar8 = (float10)FUN_008C1040(*(undefined4*)(DAT_0112F938 + 0xB8)); // Final additive random
        fVar8 = fVar8 + (float10)(float)(fVar7 * (float10)fVar2 +
                                         (float10)_param_3 +
                                         fVar6 * (float10)fVar3 * (float10)fVar1 +
                                         (float10)(float)fVar5);
    }

    // Apply final multiplier from damage component (offset +0x38)
    fVar3 = *(float*)(*(int*)((int)thisPtr + 0x1D0) + 0x38);

    // Clear stored hit data pointer
    *(undefined4*)((int)thisPtr + 0x19C) = 0;

    return (float)(fVar8 * (float10)fVar3);
}