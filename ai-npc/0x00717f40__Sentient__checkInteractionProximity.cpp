// FUNC_NAME: Sentient::checkInteractionProximity

#include <windows.h>

// ---------------------------------------------------------------------------
// 0x00717f40 - Sentient::checkInteractionProximity
// Checks whether the entity (this) is close enough and facing the target
// Implicit inputs: EAX = flags (high 24 bits preserved), EBX = target owner pointer, EBP high byte = initial result byte
// Returns: EAX with low byte set to condition result
// ---------------------------------------------------------------------------

uint __fastcall Sentient::checkInteractionProximity(Sentient* this, uint inFlags)
{
    char initialResult;
    uint outFlags;
    int componentPtr;
    int baseObj;
    int iVar3, iVar4, iVar5;
    float diffX, diffY, diffZ;
    float squaredDist;
    float dotProd;

    // +0x338 likely pointer to some behavior component (e.g., InteractionComponent)
    componentPtr = *(int*)((char*)this + 0x338);
    outFlags = inFlags & 0xFFFFFF00;

    if (componentPtr == 0)
        return outFlags;

    // Base object pointer at offset -0x48 from the component
    baseObj = componentPtr - 0x48;
    if (baseObj == 0)
        return outFlags;

    // Bit 10 at +0x898 indicates whether interaction is allowed
    if ((*(uint*)(componentPtr + 0x898) >> 10 & 1) == 0)
        return outFlags;

    // Call virtual function to get a float property by hash (0x369ac561 -> "interactionRadius")
    // Returns true if the property exists and writes the value to local_10
    if ((**(code**)(*(int*)baseObj + 0x10))(0x369ac561, &diffX) != 0)
    {
        // EBX is the target object (e.g., a Family or Building) passed from caller
        if (bX != 0)
        {
            // +0x24c4 points to some entity ID? Subtract 0x48 to get base object
            if (*(int*)(bX + 0x24c4) == 0)
                iVar3 = 0;
            else
                iVar3 = *(int*)(bX + 0x24c4) - 0x48;

            // Compare with entity at this+0x18 (likely the owner of the interaction)
            if (iVar3 == *(int*)((char*)this + 0x18))
            {
                initialResult = 1;
            }
            else if (iVar3 != 0)
            {
                // FUN_006c9440 probably casts or converts object to a common base class
                iVar3 = FUN_006c9440(iVar3, 0x55859efa);  // hash for "Family" or "Crew"
                if (iVar3 != 0 &&
                    *(int*)(iVar3 + 0x1ed4) == *(int*)(*(int*)((char*)this + 0x18) + 0x1ed4))
                {
                    initialResult = 1;
                }
            }
        }
    }

    // FUN_00471610 likely returns pointer to player position or object
    iVar3 = FUN_00471610();
    iVar4 = FUN_00471610();

    diffZ = *(float*)(iVar4 + 0x38) - *(float*)(iVar3 + 0x38);
    diffY = *(float*)(iVar4 + 0x34) - *(float*)(iVar3 + 0x34);
    diffX = *(float*)(iVar4 + 0x30) - *(float*)(iVar3 + 0x30);

    // Check squared distance against threshold
    if (diffX*diffX + diffY*diffY + diffZ*diffZ < DAT_00e445fc)  // interaction radius squared
    {
        // Get three more objects (probably forward vectors, up, etc.)
        iVar3 = FUN_00471610();
        iVar4 = FUN_00471610();
        iVar5 = FUN_00471610();

        // Compute dot product with direction vectors (likely facing and up)
        dotProd = *(float*)(iVar5 + 0x28) * diffZ +   // +0x28 = z of right/up?
                  *(float*)(iVar3 + 0x20) * diffX +   // +0x20 = x of forward?
                  *(float*)(iVar4 + 0x24) * diffY;    // +0x24 = y of forward?

        if (dotProd > DAT_00d5f6e8)  // min angle threshold
        {
            iVar3 = FUN_00471610();
            iVar4 = FUN_00471610();
            iVar5 = FUN_00471610();
            dotProd = *(float*)(iVar5 + 0x28) * diffZ +
                      *(float*)(iVar3 + 0x20) * diffX +
                      *(float*)(iVar4 + 0x24) * diffY;

            if (dotProd < DAT_00d61ae4)  // max angle threshold
            {
                // Return with low byte = 1 (interaction allowed)
                outFlags = (outFlags & 0xFFFFFF00) | 1;
                return outFlags;
            }
        }
        // Fall through: return with low byte = initialResult (0 or 1 from family check)
    }

    // If distance check fails, return with unchanged initialResult
    outFlags = (outFlags & 0xFFFFFF00) | initialResult;
    return outFlags;
}