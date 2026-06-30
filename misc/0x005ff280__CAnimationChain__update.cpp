// FUNC_NAME: CAnimationChain::update

void __thiscall CAnimationChain::update(int this)
{
    int *piVar1;
    int *piVar2;
    uint uVar3;
    char cLocalVar;
    undefined4 uVar4;
    undefined4 *puVar5;
    int iVar6;
    float *extraout_EDX;
    float fVar7;
    float fVar8;
    float fVar9;

    // +0x118: pointer to slot manager (vtable)
    if (*(int *)(this + 0x118) == 0)
        return;

    // +0x94 and +0x9c are part of a slot pair; if either is null, initialize the chain
    if (*(int *)(this + 0x94) == 0 || *(int *)(this + 0x9c) == 0)
    {
        cLocalVar = FUN_005fe2e0(this, this + 0x88, this + 0x94, 0);
        if (cLocalVar == 0 &&
            ((*(int *)(this + 0x7c) == 0 || *(int *)(this + 0x84) == 0) &&
             (*(int **)(this + 0x118) != (int *)0x0)))
        {
            // vtable offset 0xc: get output slot pointer
            uVar4 = (*(code **)(**(int **)(this + 0x118) + 0xc))(*(undefined4 *)(this + 0x120));
            FUN_005f7ba0(uVar4); // apply output transformation
        }
    }

    // Pointer swapping chain (shift input slots)
    piVar1 = (int *)(this + 0x7c); // +0x7c: m_pSlotA
    piVar2 = (int *)(this + 0x70); // +0x70: m_pSlotB
    if (piVar2 != piVar1)
    {
        iVar6 = *piVar1;
        if (*piVar2 != iVar6)
        {
            if (*piVar2 != 0)
                FUN_004daf90(piVar2); // release old slot
            *(int *)(this + 0x70) = iVar6;
            if (iVar6 != 0)
            {
                *(undefined4 *)(this + 0x74) = *(undefined4 *)(iVar6 + 4); // slot next/prev
                *(int **)(iVar6 + 4) = (int *)(this + 0x70);
            }
        }
    }

    piVar2 = (int *)(this + 0x88); // +0x88: m_pSlotC
    *(undefined4 *)(this + 0x78) = *(undefined4 *)(this + 0x84); // copy tail pointer
    if (piVar1 != piVar2)
    {
        iVar6 = *piVar2;
        if (*piVar1 != iVar6)
        {
            if (*piVar1 != 0)
                FUN_004daf90(piVar1);
            *piVar1 = iVar6;
            if (iVar6 != 0)
            {
                *(undefined4 *)(this + 0x80) = *(undefined4 *)(iVar6 + 4);
                *(int **)(iVar6 + 4) = piVar1;
            }
        }
    }

    *(undefined4 *)(this + 0x84) = *(undefined4 *)(this + 0x90); // copy tail pointer
    if (piVar2 != (int *)(this + 0x94))
    {
        iVar6 = *(int *)(this + 0x94);
        if (*piVar2 != iVar6)
        {
            if (*piVar2 != 0)
                FUN_004daf90(piVar2);
            *piVar2 = iVar6;
            if (iVar6 != 0)
            {
                *(undefined4 *)(this + 0x8c) = *(undefined4 *)(iVar6 + 4);
                *(int **)(iVar6 + 4) = piVar2;
            }
        }
    }

    *(undefined4 *)(this + 0x90) = *(undefined4 *)(this + 0x9c); // copy tail
    FUN_005f5ce0(); // global sync/update

    // Copy position from active slot to this->m_vBlendTarget (+0x60..+0x68)
    if (((*piVar1 != 0) && (puVar5 = *(undefined4 **)(this + 0x84), puVar5 != (undefined4 *)0x0)) ||
        ((*(int *)(this + 0x70) != 0 && (puVar5 = *(undefined4 **)(this + 0x78), puVar5 != (undefined4 *)0x0))))
    {
        *(undefined4 *)(this + 0x60) = *puVar5;
        *(undefined4 *)(this + 0x64) = puVar5[1];
        *(undefined4 *)(this + 0x68) = puVar5[2];
    }

    FUN_00414aa0(); // matrix calculation

    // Compute distance from current world position to the chain input slot
    if ((*piVar2 != 0) && (puVar5 = *(undefined4 **)(this + 0x90), puVar5 != (undefined4 *)0x0))
    {
        *(undefined4 *)(this + 0x10) = *puVar5;
        *(undefined4 *)(this + 0x14) = puVar5[1];
        *(undefined4 *)(this + 0x18) = puVar5[2];
        fVar9 = extraout_EDX[2] - *(float *)(this + 0x18);
        fVar8 = extraout_EDX[1] - *(float *)(this + 0x14);
        fVar7 = *extraout_EDX - *(float *)(this + 0x10);
        *(float *)(this + 0xc4) = SQRT(fVar9 * fVar9 + fVar8 * fVar8 + fVar7 * fVar7);
        *(undefined4 *)(this + 0xc0) = 0; // flag

        // Advance slot index (+0x120) if not at max
        if (*(int **)(this + 0x118) != (int *)0x0)
        {
            uVar3 = *(uint *)(this + 0x120);
            iVar6 = (*(code **)(**(int **)(this + 0x118) + 8))(); // get max index
            if (uVar3 < iVar6 - 1U)
                *(uint *)(this + 0x120) = uVar3 + 1;
        }

        // Invoke optional callback at +0xa4
        if (*(code **)(this + 0xa4) != (code *)0x0)
            (*(code **)(this + 0xa4))(this, this + 0x70, piVar1, piVar1, piVar2);
    }

    FUN_005fea70(0); // post-update cleanup
}