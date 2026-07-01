// FUNC_NAME: AudioManager::updateVoiceSlots
void __thiscall AudioManager::updateVoiceSlots(int *this, int *output, float currentTime)
{
    bool bVar2;
    bool bVar1;
    char cVar3;
    int iVar4;
    int *piVar5;
    uint uVar6;
    int *piVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float local_10;
    float local_c;
    float local_8;

    // Global constants (from data section)
    extern float DAT_00e544d8; // total duration?
    extern float _DAT_00d5780c; // some time offset
    extern float _DAT_00e544d0; // multiplier
    extern float DAT_00d5eee4; // multiplier
    extern float DAT_00d5f168; // another offset
    extern float DAT_00d5efa8; // multiplier
    extern float _DAT_00d5c458; // minimum threshold
    extern float _DAT_00d577a0; // zero threshold?
    extern float DAT_00e44590; // random scale

    fVar9 = _DAT_00d5780c;
    output[0] = 0;
    output[1] = 0;
    output[2] = 0;
    fVar10 = DAT_00e544d8;
    fVar9 = fVar9 / DAT_00e544d8;
    local_10 = 0.0f;
    local_c = 0.0f;
    bVar2 = false;

    // Get some global object and copy its transform/position?
    iVar4 = FUN_00471610(); // likely getGlobalObject()
    *(long long *)(this + 0x71b) = *(long long *)(iVar4 + 0x20);
    this[0x71d] = *(int *)(iVar4 + 0x28);

    FUN_00800670(); // some update function

    if (fVar10 <= currentTime)
    {
        if ((char)this[0x288] != '\0') // isActive?
        {
            local_c = (currentTime - fVar10) * fVar9 * _DAT_00e544d0 * DAT_00d5eee4;
        }
        fVar9 = (_DAT_00d5780c - currentTime) * fVar9;
    }
    else
    {
        if ((char)this[0x288] != '\0')
        {
            local_c = (currentTime - (fVar10 - DAT_00d5f168)) * fVar9 * _DAT_00e544d0;
        }
        fVar9 = (fVar10 - currentTime) * fVar9 * DAT_00d5efa8 + _DAT_00d5780c;
    }

    this[0x207] = this[0x207] & 0xfffff0ff; // clear some bits
    piVar7 = this + 0x1d7; // voice slot array (8 pointers)
    iVar4 = 8;
    piVar5 = piVar7;
    do
    {
        if (*piVar5 != 0) // voice slot active
        {
            fVar8 = FUN_008c95c0(); // random float?
            fVar10 = fVar8 + local_c;
            if (fVar8 + local_c < _DAT_00d5c458)
            {
                fVar10 = _DAT_00d5c458;
            }
            if ((((*(byte *)((int)this + 0x8e6) & 1) == 0) || (*(int *)(*piVar5 + 0x40) == 2)) ||
               (*(int *)(*piVar5 + 0x40) == 3))
            {
                local_10 = fVar10 + local_10;
            }
        }
        piVar5 = piVar5 + 2; // each slot is 2 ints? Actually pointer + something? But we treat as array of pointers
        iVar4 = iVar4 + -1;
    } while (iVar4 != 0);

    if ((this[0x1ea] != 0) &&
       ((cVar3 = (**(code **)(*this + 0x194))(this[0x1ea]), cVar3 != '\0' ||
        (local_10 == _DAT_00d577a0))))
    {
        bVar2 = true;
        fVar8 = FUN_008c95c0();
        local_10 = fVar8 + local_c + local_10;
    }

    if (this[0x1e9] != 0)
    {
        fVar8 = FUN_008c95c0();
        fVar10 = fVar8 + local_c;
        if (fVar8 + local_c < _DAT_00d5c458)
        {
            fVar10 = _DAT_00d5c458;
        }
        local_10 = fVar10 + local_10;
    }

    local_8 = 0.0f;
    bVar1 = true;
    if ((*(byte *)((int)this + 0x8e6) & 1) == 0)
    {
        iVar4 = _rand();
        local_8 = (float)iVar4 * DAT_00e44590 * local_10;
    }

    uVar6 = 0;
    do
    {
        if (!bVar1) break;
        if (*piVar7 != 0)
        {
            fVar8 = FUN_008c95c0();
            fVar10 = fVar8 + local_c;
            if (fVar8 + local_c < _DAT_00d5c458)
            {
                fVar10 = _DAT_00d5c458;
            }
            local_8 = local_8 - fVar10;
            if (local_8 <= 0.0f)
            {
                bVar1 = false;
                FUN_008c93f0(this); // stop voice?
                fVar8 = FUN_008c9590(); // random?
                this[0x1e8] = uVar6; // voice index
                this[0x1e7] = (int)(fVar8 * fVar9); // some time value
                FUN_008c98a0(output); // set output
                this[0x207] = this[0x207] & 0xfffffff9; // clear bits
            }
        }
        uVar6 = uVar6 + 1;
        piVar7 = piVar7 + 2;
    } while (uVar6 < 8);

    if ((bVar2) && (bVar1))
    {
        fVar8 = FUN_008c95c0();
        fVar10 = fVar8 + local_c;
        if (fVar8 + local_c < _DAT_00d5c458)
        {
            fVar10 = _DAT_00d5c458;
        }
        if (local_8 - fVar10 <= 0.0f)
        {
            bVar1 = false;
            FUN_008c93f0(this);
            fVar8 = FUN_008c9590();
            this[0x1e7] = (int)(fVar8 * fVar9);
            this[0x1e8] = 8; // special index
            FUN_008c98a0(output);
            this[0x207] = this[0x207] | 0x200; // set bit
        }
    }

    if ((this[0x1e9] != 0) && (bVar1))
    {
        FUN_008c93f0(this);
        fVar8 = FUN_008c9590();
        this[0x1e7] = (int)(fVar8 * fVar9);
        this[0x1e8] = 8;
        FUN_008c98a0(output);
        this[0x207] = this[0x207] | 0x800; // set bit
    }

    this[0x260] = 0;
    this[0x25f] = 0;
    this[0x25c] = this[0x25c] | 0x200;
    this[0x25c] = this[0x25c] | 0x400;
    return;
}