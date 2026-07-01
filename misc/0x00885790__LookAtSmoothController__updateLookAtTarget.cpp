// FUNC_NAME: LookAtSmoothController::updateLookAtTarget
void __fastcall LookAtSmoothController::updateLookAtTarget(void* thisPtr)
{
    // +0x50: m_pTargetObject (pointer to derived look-at target object)
    // +0x58: m_pTargetEntity (some entity pointer, validated by FUN_00543070)
    // +0x5c: m_CurrentLookAt (float[2]? or a 3D? The code swaps 4 bytes, but could be 2 floats? Actually it swaps both 0x5c/0x64 and 0x60/0x68, so likely two variables of 8 bytes each, e.g., quaternion or two 2D angles? We'll treat as 3D vector: x,y,z? But offset 0x68 is swapped with 0x60, and 0x64 with 0x5c. So it's two 3-float vectors spread across 4 slots? Actually 0x5c,0x60,0x64,0x68 are four consecutive 4-byte chunks. They swap the first and third, and second and fourth. So it's swapping two 8-byte structures (e.g., two 2D vectors or two floats? But 8 bytes could be two floats (x,y) or a single double? Likely two 2D yaw/pitch angles or two 3D positions truncated? We'll model as float[2] for each: m_CurrentLookAt[0] at +0x5c, m_CurrentLookAt[1] at +0x60; m_TargetLookAt[0] at +0x64, m_TargetLookAt[1] at +0x68. Or could be two 3D vectors but only 4 floats stored? The code only references four floats. So likely two 2D look directions (horizontal and vertical angles?). We'll use float arrays. But the virtual functions likely deal with full 3D? We'll assume the struct stores two 2D angles (yaw, pitch). At the end it swaps all four floats.
    float* pCurrentAngle0 = (float*)((int)thisPtr + 0x5c); // +0x5c: horizontal angle
    float* pCurrentAngle1 = (float*)((int)thisPtr + 0x60); // +0x60: vertical angle
    float* pTargetAngle0   = (float*)((int)thisPtr + 0x64); // +0x64: target horizontal
    float* pTargetAngle1   = (float*)((int)thisPtr + 0x68); // +0x68: target vertical

    // Validate pointers
    if (*(int*)((int)thisPtr + 0x58) == 0 || *(int*)((int)thisPtr + 0x50) == 0)
        return;

    // Check if the target object type is valid (skip if == 0x48)
    if (*(int*)((int)thisPtr + 0x50) == 0x48)
        return;

    // Additional validation via FUN_00543070 (likely isAlive/isValid)
    if (!FUN_00543070(*(int*)((int)thisPtr + 0x58)))
        return;

    // Retrieve the base class pointer from the derived object at +0x50
    int* pBase; // base class pointer for vtable dispatch
    if (*(int*)((int)thisPtr + 0x50) == 0)
        pBase = 0;
    else
        pBase = *(int**)(*(int*)((int)thisPtr + 0x50) - 0x48); // derived->base via offset

    // Virtual function at vtable+0x1f8: get current look-at direction (output to local)
    struct { float x, y, z; } localLookDir;
    ((void(*)(int, void*))(*pBase + 0x1f8))(*(int*)((int)thisPtr + 0x58), &localLookDir);

    // Virtual function at vtable+0x1f0: compute new target from current look direction (stored in pCurrentAngle0)
    // This probably transforms the current direction into angle representation
    if (*(int*)((int)thisPtr + 0x50) == 0)
        pBase = 0;
    else
        pBase = *(int**)(*(int*)((int)thisPtr + 0x50) - 0x48);
    ((void(*)(void*, float*))(*pBase + 0x1f0))(&localLookDir, pCurrentAngle0);

    // Virtual function at vtable+0x1c8: copy current angles to target angles? Or compute target from current?
    if (*(int*)((int)thisPtr + 0x50) == 0)
        pBase = 0;
    else
        pBase = *(int**)(*(int*)((int)thisPtr + 0x50) - 0x48);
    ((void(*)(float*, float*))(*pBase + 0x1c8))(pCurrentAngle0, pTargetAngle0);

    // Now check a condition: compute dot product between two entities' forward vectors?
    // The code calls FUN_00471610 three times to get pointers to transform data.
    // It computes (v1 - v2) dot something then compares to global threshold.
    // Based on result, maybe we need to flip target/current.

    // Check a flag at offset 0xc8a in the base class (bit 0)
    int* pBase2;
    if (*(int*)((int)thisPtr + 0x50) == 0)
        pBase2 = 0;
    else
        pBase2 = (int*)(*(int*)((int)thisPtr + 0x50) - 0x48);
    if ((*(byte*)((int)pBase2 + 0xc8a) & 1) == 0)
        return; // feature disabled? Probably skip smoothing update

    // Retrieve pointers to transforms of two entities (maybe camera and target entity index 0xe54 holds entity ID or pointer to something)
    int* pEntity1;
    int* pEntity2;
    if (*(int*)((int)pBase2 + 0xe54) != 0 && *(int*)((int)pBase2 + 0xe54) != 0x48)
    {
        pEntity1 = (int*)FUN_00471610(); // likely returns a pointer to a transform or position
        pEntity2 = (int*)FUN_00471610(); // second transform
        float dx = *(float*)(pEntity1 + 0x30) - *(float*)(pEntity2 + 0x30); // position difference X
        float dy = *(float*)(pEntity1 + 0x34) - *(float*)(pEntity2 + 0x34); // Y
        // The function then fetches a third transform for Z difference
        float dz1 = *(float*)(pEntity1 + 0x38); // probably Z of first entity?
        float dz2 = *(float*)(pEntity2 + 0x38); // Z of second
        float* pNormal = (float*)FUN_00471610(); // some direction vector
        int* pNormal2 = (int*)FUN_00471610(); // another component?
        int* pNormal3 = (int*)FUN_00471610(); // third

        // Compute dot product: pNormal->x * dx + pNormal2->y * dy + pNormal3->z * (dz1 - dz2)
        float dotProduct = *pNormal * dx + *(float*)(pNormal2 + 1) * dy + *(float*)(pNormal3 + 2) * (dz1 - dz2);
        // Compare to global threshold (likely cos of angle or distance)
        if (dotProduct <= g_lookAtThreshold) // _DAT_00d577a0
        {
            if (!FUN_008754b0(pCurrentAngle0)) // predicate: is current direction okay?
                return;
        }
        else
        {
            if (FUN_008754b0(pCurrentAngle0)) // opposite predicate
                return;
        }
        // If we get here, swap current and target angles (smooth transition?)
        float temp0 = *pCurrentAngle0;
        float temp1 = *pCurrentAngle1;
        *pCurrentAngle0 = *pTargetAngle0;
        *pCurrentAngle1 = *pTargetAngle1;
        *pTargetAngle0 = temp0;
        *pTargetAngle1 = temp1;
    }
}