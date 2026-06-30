// FUNC_NAME: ChaseCamera::updateTargetPosition
// Function address: 0x006dfe90
// This function computes the desired camera target position based on the entity's state and camera member variables.

void __thiscall ChaseCamera::updateTargetPosition(float* outPos, void* targetEntity)
{
    byte bVar1;
    float *pfVar2;
    int iVar3;
    float fVar4, fVar5, fVar6, fVar7;

    // Extract bit 26 from entity flags (offset 0x8e0)
    bVar1 = (byte)(*(uint*)((int)targetEntity + 0x8e0) >> 0x1a) & 1;

    // Case: bit26 = 0 and bit25 = 1 (entity in a specific state, e.g., driving)
    if ((bVar1 == 0) && ((*(uint*)((int)targetEntity + 0x8e0) >> 0x19 & 1) != 0)) {
        // Call external function to adjust outPos based on targetEntity (e.g., vehicle offset)
        FUN_007c6f70(outPos, targetEntity);
        outPos[1] = *(float*)((int)this + 0x18c) + outPos[1]; // Add vertical offset from camera

        // Choose pointer to vector depending on entity ID
        if ((int)targetEntity == -0x2770) {
            iVar3 = FUN_00471610(); // Get singleton (perhaps game manager)
            pfVar2 = (float*)(iVar3 + 0x20);
        } else {
            pfVar2 = (float*)((int)targetEntity + 0x277c); // Entity's own vector (e.g., vehicle velocity)
        }

        fVar7 = g_timeDelta1; // Global time delta (from _DAT_00d5780c)

        // Select horizontal distance based on bit30 (0x40000000) of entity flags
        if ((*(uint*)((int)targetEntity + 0x8e0) >> 0x1e & 1) == 0) {
            fVar6 = *(float*)((int)this + 0x1a0); // Standard horizontal offset
        } else {
            fVar6 = *(float*)((int)this + 0x19c); // Alternative horizontal offset
        }

        // Compute new position using pfVar2 as a transform (velocity-like adjustment)
        fVar4 = pfVar2[2] * fVar6 + outPos[0];
        fVar5 = fVar6 * g_timeDelta2 + outPos[1]; // g_timeDelta2 from _DAT_00d577a0
        fVar6 = (g_constant - *pfVar2) * fVar6 + outPos[2]; // g_constant from DAT_00e44564

        outPos[0] = fVar4;
        outPos[1] = fVar5;
        outPos[2] = fVar6;

        // Interpolate towards stored target position if camera lerp factor < time delta
        if (*(float*)((int)this + 0xf4) < fVar7) {
            fVar7 = fVar7 - *(float*)((int)this + 0xf4);
            outPos[0] = (*(float*)((int)this + 0x118) - fVar4) * fVar7 + fVar4;
            outPos[1] = (*(float*)((int)this + 0x11c) - fVar5) * fVar7 + fVar5;
            outPos[2] = (*(float*)((int)this + 0x120) - fVar6) * fVar7 + fVar6;
            return;
        }
    }
    // Case: bit0 = 0 and bit26 = 0 (normal state, e.g., on foot)
    else if (((*(byte*)((int)targetEntity + 0x8e0) & 1) == 0) && (bVar1 == 0)) {
        iVar3 = FUN_00471610(); // Get singleton position (e.g., player position)
        *(undefined8*)outPos = *(undefined8*)(iVar3 + 0x30); // Copy x,y
        outPos[2] = *(float*)(iVar3 + 0x38); // Copy z
        outPos[1] = *(float*)((int)this + 0x158) + outPos[1]; // Add vertical offset from camera

        fVar7 = *(float*)((int)this + 0xf4); // Lerp factor
        if (g_timeDelta2 < fVar7) {
            outPos[0] = (*(float*)((int)this + 0x118) - outPos[0]) * fVar7 + outPos[0];
            outPos[1] = (*(float*)((int)this + 0x11c) - outPos[1]) * fVar7 + outPos[1];
            outPos[2] = (*(float*)((int)this + 0x120) - outPos[2]) * fVar7 + outPos[2];
            return;
        }
    }
    // Default: use camera's stored target position directly (bit26 or bit0 set)
    else {
        *(undefined8*)outPos = *(undefined8*)((int)this + 0x118); // Copy x,y
        outPos[2] = *(float*)((int)this + 0x120); // Copy z
    }
    return;
}

// Global variables used (addresses provided for reference):
// 0x00d5780c: g_timeDelta1 (float)
// 0x00d577a0: g_timeDelta2 (float)
// 0x00e44564: g_constant (float)