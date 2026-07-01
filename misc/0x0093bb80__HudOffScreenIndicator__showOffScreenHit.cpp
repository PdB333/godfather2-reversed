// FUNC_NAME: HudOffScreenIndicator::showOffScreenHit
void __fastcall HudOffScreenIndicator::showOffScreenHit(int thisPtr)
{
    int iVar1;
    float fVar2, fVar3;
    float local_e0;
    undefined4 local_dc, local_d8, local_d4, local_d0, local_cc, local_c8, local_c4, local_bc;
    int local_b8;
    undefined4 local_b4, *local_b0;
    undefined8 local_ac;
    undefined4 local_a4;
    undefined1 local_a0[16];
    undefined1 local_90[12];
    undefined4 local_84, local_74, local_68, local_64;
    undefined8 local_70;
    undefined4 local_54;
    undefined1 local_50[76];

    // +0x60: some counter (e.g., hitCount, maybe number of hits queued)
    // +0x48: boolean flag (e.g., isEnabled)
    if ((*(int *)(thisPtr + 0x60) < 1) && (*(char *)(thisPtr + 0x48) != '\0'))
    {
        FUN_00425060(&local_dc, 0);                         // likely construct a quaternion/vector
        local_84 = 0;
        local_74 = 0;
        local_64 = 0;
        local_54 = _DAT_00d5780c;                            // identity quaternion or zero
        FUN_0056b8a0(local_d8, local_dc, local_d4, local_90);// likely matrix operation

        local_a4 = local_68;
        local_ac = local_70;
        // Compute angle between two directions (player forward vs target direction)
        fVar2 = (float10)FUN_004a0cd0(&stack0x00000004, &local_ac, &stack0x00000010, &DAT_00d8a550);
        local_e0 = (float)(fVar2 + (float10)_DAT_00d8ad70);   // add some bias
        fVar3 = local_e0;
        if (fVar2 + (float10)_DAT_00d8ad70 < (float10)0.0)
        {
            fVar3 = local_e0 + DAT_00d5d70c;                  // wrap around (add 2π)
        }
        fVar3 = fVar3 * _DAT_00d8ad6c;                       // convert to index (multiply by 8/(2π)?)
        if ((uint)(int)fVar3 < 8)
        {
            iVar1 = FUN_004262f0(0);                          // probably get player transform or camera
            FUN_00414c90(iVar1 + 0x40, local_50);             // read world matrix
            local_d0 = 0;
            local_cc = 0;
            local_c8 = 0;
            local_b0 = &local_d0;
            local_c4 = _DAT_00d5780c;
            local_b4 = 0xffffffff;
            local_bc = 5;                                    // render layer?
            local_b8 = iVar1;
            // Display off-screen hit indicator for the corresponding direction
            // String table: ["hud_offScreenHit_0", ... "_7"] at 0x00e567a4
            FUN_004eacb0((&PTR_s_hud_offScreenHit_90_00e567a4)[(int)fVar3]);
            FUN_004df3c0(&local_e0, local_a0, local_50, 0x1ff, 4, &local_bc);
            if (local_e0 != 0.0)
            {
                *(undefined4 *)((int)local_e0 + 8) = 0;      // clear some reference/pointer
            }
        }
    }
    return;
}