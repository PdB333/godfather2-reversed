// FUNC_NAME: ChaseCamera::updateChasePosition

void ChaseCamera::updateChasePosition(Vector3& outPos, Vector3& outTarget, const Vector3& inTarget, bool bClampVertical)
{
    bool bOverride = false;
    float speedFactor;
    Vector3 delta;
    Vector3 *posPtr;
    float clampY;
    int *stateFlags = reinterpret_cast<int*>(this) + 0x238; // +0x8EC (0x238*4) flags field
    int *extraFlags = reinterpret_cast<int*>(this) + 0x239; // +0x8F0
    char *animState = reinterpret_cast<char*>(this) + 0x93c; // +0x93C

    // Check if bit 10 of stateFlags is set and the function call succeeds
    if (((*stateFlags >> 10) & 1) == 0 || (FUN_00800ad0() == 0))
    {
        // Call virtual method at vtable+0xA4 (likely update/transition)
        (this->*(code *)(*(int*)this + 0xA4))(&outPos, reinterpret_cast<int*>(this) + 0x1c4);
    }
    else
    {
        // Alternative path: reset parameters and call another function
        FUN_00800ad0(&outPos, 0, 0, 0, 0);
        FUN_00701bc0(&outPos, 0.0f, 0.0f, 0.0f, 0.0f);
        int iVar2 = FUN_00800ad0();
        bOverride = *(char*)(iVar2 + 0x1aa) == '\x02'; // Check specific animation state
    }

    // Check bit 1 of stateFlags
    if ((*stateFlags >> 1) & 1)
    {
        // Simplified path: just clamp Y and return
        float adjustY = *(float*)(FUN_00471610() + 0x34) + _DAT_00d7322c; // global gravity offset
        if (outPos.y <= adjustY && adjustY != outPos.y)
        {
            outPos.y = adjustY;
            return;
        }
        return;
    }

    // Bit 1 is clear – proceed with more complex adjustment
    if ((*stateFlags >> 0x19) & 1)
    {
        int handle1 = FUN_00471610();
        int handle2 = FUN_00471610();
        posPtr = reinterpret_cast<Vector3*>(FUN_00471610());

        // Determine if we should apply the extra offset
        bool bApplyOffset = true;
        if ((*extraFlags & 0x100U) != 0 && *animState != '\0')
        {
            bApplyOffset = false;
        }

        // If busy flag is not set, compute look-at dot product
        if ((*extraFlags & 0x100U) == 0)
        {
            Vector3 vecToTarget;
            vecToTarget.x = inTarget.x - *(float*)(handle1 + 0x30);
            vecToTarget.y = inTarget.y - *(float*)(handle1 + 0x34);
            vecToTarget.z = inTarget.z - *(float*)(handle1 + 0x38);

            // Dot product with handle2's forward vector (elements at +0x20,+0x24,+0x28)
            float dot = *(float*)(handle2 + 0x20) * vecToTarget.x +
                        *(float*)(handle2 + 0x24) * vecToTarget.y +
                        *(float*)(handle2 + 0x28) * vecToTarget.z;

            if (_DAT_00d577a0 < dot) // global threshold
            {
                bApplyOffset = false;
            }
        }

        FUN_007c6f70(&outTarget); // reset target position?

        // Compute delta from target to look-at
        delta.x = outTarget.z - inTarget.z; // note: z and x swapped? unusual
        delta.y = 0.0f;
        delta.z = inTarget.x - outTarget.x;

        FUN_0043a210(&delta, &delta); // normalize or compute magnitude?

        float fFactor = _DAT_00d5cf70;
        if (bOverride)
        {
            fFactor = DAT_00d73228;
        }

        outTarget.x += fFactor * delta.x;
        outTarget.y += fFactor * delta.y;
        outTarget.z += fFactor * delta.z;

        if (bApplyOffset)
        {
            float fScale = 0.0f;
            if (bClampVertical && ((*stateFlags >> 0x1e) & 1))
            {
                fScale = DAT_00d73224;
            }
            outPos.x = posPtr->x * fScale + outTarget.x;
            outPos.z = posPtr->z * fScale + outTarget.z;
        }

        // Clamp Y position
        float clampY = outTarget.y + _DAT_00d7322c; // global gravity offset
        if (outPos.y <= clampY && clampY != outPos.y)
        {
            outPos.y = clampY;
        }
    }
}