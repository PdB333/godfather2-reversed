// FUNC_NAME: Player::testAimAtTarget
uint __fastcall Player::testAimAtTarget(int thisPtr)
{
    float fVar1, fVar2, fVar3, fVar4, fVar5, fVar6;
    float fVar8;
    int iVar9, iVar10;
    double uVar7;
    uint uVar12;
    float local_18, local_14;
    char local_c[12]; // stack buffer for projection

    uVar12 = g_pGameManager; // DAT_012233a0

    // Check if the game manager's internal state is valid
    if ((int*)**(int**)(g_pGameManager + 4) != nullptr)
    {
        // Call a virtual method at vtable+0xc (likely "getActiveCamera" or "updateCamera")
        (**(code**)(*(int*)**(int**)(g_pGameManager + 4) + 0xc))();

        iVar9 = GetPlayerTransform();      // 1st call -> player transform?
        iVar10 = GetPlayerTransform();     // 2nd call -> target transform?

        // Positions of two objects (player and target)
        fVar1 = *(float*)(iVar10 + 0x30); // x
        fVar2 = *(float*)(iVar9 + 0x30);  // x
        fVar3 = *(float*)(iVar10 + 0x34); // y
        fVar4 = *(float*)(iVar9 + 0x34);  // y
        fVar5 = *(float*)(iVar10 + 0x38); // z
        fVar6 = *(float*)(iVar9 + 0x38);  // z

        // Project something to screen? Returns a packed 2D point (x,y) as a double
        uVar7 = ProjectToScreen((Vector3*)local_c, 0); // FUN_00424fb0
        fVar8 = *(float*)((char*)&uVar7 + 8); // high part? Actually from decompiler: puVar11+1 is +4 bytes? Mist.

        // Re-get player transform again (3rd call)
        iVar9 = GetPlayerTransform();
        local_18 = (float)uVar7;        // low 32 bits as float (x)
        local_14 = (float)((ulonglong)uVar7 >> 0x20); // high 32 bits as float (y)

        uVar12 = iVar9 + 0x30; // address of player's position

        // Check dot products: direction * (target - player) and direction * (projectedPoint - player)
        float dot1 = *(float*)(thisPtr + 0x2F0) * (fVar1 - fVar2) +
                     *(float*)(thisPtr + 0x2F4) * (fVar3 - fVar4) +
                     *(float*)(thisPtr + 0x2F8) * (fVar5 - fVar6);
        float dot2 = *(float*)(thisPtr + 0x2F0) * (local_18 - *(float*)(iVar9 + 0x30)) +
                     *(float*)(thisPtr + 0x2F4) * (local_14 - *(float*)(iVar9 + 0x34)) +
                     *(float*)(thisPtr + 0x2F8) * (fVar8 - *(float*)(iVar9 + 0x38));

        if (dot1 * dot2 <= g_fVisibilityEpsilon) // _DAT_00d577a0
        {
            // Return player position pointer masked (likely as uint)
            return uVar12 & 0xFFFFFF00;
        }
    }

    // Build a result from the global manager shifted and low byte set to 1
    return CONCAT31((int3)(uVar12 >> 8), 1);
}