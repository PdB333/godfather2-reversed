// Xbox PDB: EARS::Modules::F2FCamera::GetEntityLowerPos
// FUNC_NAME: NPC::updateHeadAimDirection
// Address: 0x006cc800
// Purpose: Adjusts the character's head/aim direction towards a target, applying smoothing and clamping.
// Parameters:
//   - this: NPC object (assumed to have vtable with bone retrieval functions)
//   - outAimVector: output 3D vector (modified in place, initially target relative offset)
// Returns: true if successful, false if system is paused or bone missing

bool __thiscall NPC::updateHeadAimDirection(NPC* this, float outAimVector[3])
{
    // Global time data (likely from a time manager)
    // Offsets: +0x20 = delta time, +0x28 = something, +0x30 = position, +0x38 = other
    TimeData* timeData = (TimeData*)FUN_00471610(); // getTimeManager()

    // Copy some time data into outAimVector initially? Actually set x and y from timeData+0x30, +0x38
    *(uint64_t*)outAimVector = *(uint64_t*)((char*)timeData + 0x30); // copy first 8 bytes (x,y?)
    outAimVector[2] = *(float*)((char*)timeData + 0x38); // z

    // Attempt to use "eye_R" bone (right eye)
    // First check if this bone exists via vfunc +0x94 (probably hasBone)
    bool hasEyeR = (this->vtable->func_0x94)(); // no args? maybe checks eye_R availability
    if (hasEyeR)
    {
        // Get bone transform for "eye_R" (function +0xA4 returns transform values into stack)
        float eyePos[3]; // derived from stack layout
        (this->vtable->func_0xA4)(&eyePos, eyePos); // actually the call uses some stack offsets

        // Compute vertical difference from current aim vector y (outAimVector[1])
        float diffY = eyePos[1] - outAimVector[1]; // stack variable fStack_10 - param_2[1]
        if (diffY < g_minHeadAngle) { // _DAT_00d5ca64
            diffY = g_minHeadAngle;
        }
        // Smoothly adjust aim vector y toward eye position
        outAimVector[1] += diffY;
    }

    // Check if the game is paused
    if (!FUN_007f7c50()) // isPaused? returns bool (cast from pointer)
    {
        return false;
    }

    // If this pointer is null? Actually checking (char)this == 0 -> weird
    if ((char)this == 0)
    {
        // Default behavior: apply damping using time data
        // outAimVector[0] -= timeData->someFactor * _DAT_00d5cf70 (likely a damping constant)
        timeData = (TimeData*)FUN_00471610(); // refresh?
        outAimVector[0] -= *(float*)((char*)timeData + 0x20) * g_aimDampingX; // _DAT_00d5cf70
        timeData = (TimeData*)FUN_00471610();
        float dampingZ = *(float*)((char*)timeData + 0x28) * g_aimDampingZ; // _DAT_00d5cf70
        // Then later subtract from outAimVector[2]
    }
    else
    {
        // Use neck bone "m_neck1" for more accurate aiming
        // Check if neck bone exists
        if (!this->vtable->func_0x94()) // hasBone("m_neck1")?
        {
            return false;
        }

        // Get neck bone position
        float neckPos[3];
        (this->vtable->func_0xA4)(&neckPos, neckPos); // bone name implicit? Actually the call uses two args

        // Compute difference between neck position and current aim vector
        float diffX = neckPos[0] - outAimVector[0];
        float diffY = neckPos[1] - outAimVector[1];
        float diffZ = neckPos[2] - outAimVector[2];

        // Get time data again for smoothing factors
        timeData = (TimeData*)FUN_00471610();
        float timeX = *(float*)((char*)timeData + 0x20);
        float timeY = *(float*)((char*)timeData + 0x28);
        float timeZ = *(float*)((char*)timeData + 0x30); // some other component

        // Compute dot product or weighted combination? The decompile shows:
        // fVar5 = (float)((ulonglong)*puVar3 >> 0x20) * diffY + fVar8 * diffX + local_28[0] * diffZ;
        // This is messy. Probably a dot product with some rotation matrix.
        float dot = timeX * diffX + timeY * diffY + timeZ * diffZ;

        if (dot > g_aimSmoothRef) // _DAT_00e510a4
        {
            // Apply smoothing: scale down the difference and add to aim vector
            outAimVector[0] += g_aimSmoothFactor * timeX; // _DAT_00e510a0
            outAimVector[2] += g_aimSmoothFactor * timeZ;
            return true;
        }

        if (dot > g_aimClampMin) // _DAT_00e44564 - _DAT_00e510a4
        {
            // Clamp condition
            timeData = (TimeData*)FUN_00471610();
            float timeX2 = *(float*)((char*)timeData + 0x20);
            float timeY2 = *(float*)((char*)timeData + 0x28);
            float dot2 = timeX2 * diffX + timeY2 * diffY + timeZ * diffZ; // similar dot
            if (dot2 <= g_aimClampThreshold) // _DAT_00e5109c
            {
                return (bool*)((char*)timeData + 0x20);
            }
            // Apply clamp movement
            outAimVector[0] += g_aimClampFactor * timeX2; // _DAT_00e51098
            outAimVector[2] += g_aimClampFactor * timeY2;
            return (bool*)((char*)timeData + 0x20);
        }

        // Default: subtract damping
        outAimVector[0] -= g_aimDampingX * timeX; // _DAT_00e510a0
        // later outAimVector[2] -= fVar6 (which is local_28[0] * something)
    }

    // Apply final damping to Z component
    outAimVector[2] -= dampingZ;
    return true; // or return some pointer
}

// Global constants (from data refs)
extern float g_minHeadAngle; // _DAT_00d5ca64
extern float g_aimDampingX;  // _DAT_00d5cf70
extern float g_aimSmoothFactor; // _DAT_00e510a0
extern float g_aimSmoothRef; // _DAT_00e510a4
extern float g_aimClampMin; // _DAT_00e44564 - _DAT_00e510a4 (computed)
extern float g_aimClampThreshold; // _DAT_00e5109c
extern float g_aimClampFactor; // _DAT_00e51098

// Extern functions
extern TimeData* FUN_00471610(); // getTimeManager
extern bool FUN_007f7c50(); // isPaused