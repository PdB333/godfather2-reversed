// FUNC_NAME: Player::tick
// Function address: 0x00738d20
// This is the main update/tick function for the Player class (EARS engine).
// It handles state machine updates, proximity events, sound triggers, event subscriptions, and respawn logic.

void __thiscall Player::tick(int *thisObject)
{
    int *piVar1;
    char tempByte;
    undefined4 uVar3;
    int iVar4;
    int iVar5;
    undefined1 *puVar6;
    float fVar7, fVar8, fVar9;
    undefined4 unknown;
    undefined1 local_49;
    undefined8 uStack_48;
    float fStack_40;
    int *local_3c;
    code *pcStack_38;
    undefined4 local_34;
    undefined4 uStack_30;
    undefined4 local_2c;
    undefined1 *puStack_28;
    undefined1 auStack_24[4];
    undefined4 uStack_20;
    undefined1 uStack_14;
    undefined **ppuStack_c;

    // Initial debug/callout
    FUN_0072c800();
    // Some kind of command or state set (param2 = 2)
    FUN_0043c490(thisObject, 2);

    // If any of four flags at offsets 0x997..0x99a are set, clear them and log?
    if ((((thisObject[0x997] != 0) || (thisObject[0x998] != 0)) || (thisObject[0x999] != 0)) || (thisObject[0x99a] != 0))
    {
        local_49 = 0;
        uVar3 = FUN_00448100(thisObject + 0x997, &local_49);
        FUN_0077dd10(uVar3);
    }

    // General update
    FUN_00716db0(thisObject);

    // Subscribe to global event if DAT_0112dd08 exists
    if (DAT_0112dd08 != 0)
    {
        FUN_00408900(thisObject + 0xf, &DAT_0112dd08, 0x8000);
    }

    // Possibly update a timer or state based on offset 0x85e
    if ((thisObject[0x85e] != 0) && (thisObject[0x85e] != 0x48))
    {
        iVar4 = FUN_007914e0();
        thisObject[0x180] = iVar4;
    }

    FUN_00809330();

    // Set up a behavior/state machine (vtable or function table)
    pcStack_38 = FUN_00736570;
    iVar4 = thisObject[0x17d];
    *(ulonglong *)(iVar4 + 0x34) = CONCAT44(FUN_00736570, thisObject);
    local_34 = 0;
    uStack_30 = 0;
    *(undefined8 *)(iVar4 + 0x3c) = 0;
    puStack_28 = &LAB_0072dce0;
    local_2c = 0;
    *(undefined8 *)(iVar4 + 0x44) = 0x72dce000000000;
    *(uint *)(thisObject[0x17d] + 0x18) = *(uint *)(thisObject[0x17d] + 0x18) | 0x80000;
    local_3c = thisObject;
    FUN_00460020(1);

    // Update a linked list at offset 0x801 if any of the flags at 0x807..0x80a are set
    if (((thisObject[0x807] != 0) || (thisObject[0x808] != 0)) || ((thisObject[0x809] != 0 || (thisObject[0x80a] != 0))))
    {
        local_49 = 0;
        iVar4 = FUN_00448100(thisObject + 0x807, &local_49);
        piVar1 = thisObject + 0x801;
        if (iVar4 == 0)
            iVar4 = 0;
        else
            iVar4 = iVar4 + 0x48; // +0x48 offset for some node size
        if (*piVar1 != iVar4)
        {
            if (*piVar1 != 0)
                FUN_004daf90(piVar1); // Detach old
            *piVar1 = iVar4;
            if (iVar4 != 0)
            {
                thisObject[0x802] = *(int *)(iVar4 + 4);
                *(int **)(iVar4 + 4) = piVar1; // Link new node
            }
        }
    }

    // Get some global value and store at offset 0x7d4
    iVar4 = FUN_0043b870(DAT_0112afb8);
    thisObject[0x7d4] = iVar4;

    // Similar linked list update for offsets 0x803 based on flags at 0x80b..0x80e
    if (((thisObject[0x80b] != 0) || (thisObject[0x80c] != 0)) || ((thisObject[0x80d] != 0 || (thisObject[0x80e] != 0))))
    {
        local_49 = 0;
        iVar4 = FUN_00448100(thisObject + 0x80b, &local_49);
        piVar1 = thisObject + 0x803;
        if (iVar4 == 0)
            iVar4 = 0;
        else
            iVar4 = iVar4 + 0x3c; // +0x3c offset
        if (*piVar1 != iVar4)
        {
            if (*piVar1 != 0)
                FUN_004daf90(piVar1);
            *piVar1 = iVar4;
            if (iVar4 != 0)
            {
                thisObject[0x804] = *(int *)(iVar4 + 4);
                *(int **)(iVar4 + 4) = piVar1;
            }
        }
    }

    // Process some list at offsets 0x819..0x81c (call virtual destructor?)
    if (((thisObject[0x819] != 0) || (thisObject[0x81a] != 0)) || ((thisObject[0x81b] != 0 || (thisObject[0x81c] != 0))))
    {
        iVar4 = FUN_00800800(thisObject + 0x819);
        if (iVar4 != 0)
        {
            (**(code **)(*thisObject + 0x24c))(iVar4); // virtual call at vtable+0x24c
        }
    }

    // Copy a value
    thisObject[0x84e] = thisObject[0x7b5];

    // Subscribe to multiple global events
    if (DAT_0112adb8 != 0)
        FUN_00408900(thisObject + 0xf, &DAT_0112adb8, 0x8000);
    if (DAT_0112adc0 != 0)
        FUN_00408900(thisObject + 0xf, &DAT_0112adc0, 0x8000);
    if (DAT_0112ade8 != 0)
        FUN_00408900(thisObject + 0xf, &DAT_0112ade8, 0x8000);
    if (DAT_0112ada8 != 0)
        FUN_00408900(thisObject + 0xf, &DAT_0112ada8, 0x8000);
    if (DAT_0112ade0 != 0)
        FUN_00408900(thisObject + 0xf, &DAT_0112ade0, 0x8000);
    if (DAT_0112adc8 != 0)
        FUN_00408900(thisObject + 0xf, &DAT_0112adc8, 0x8000);
    if (DAT_0112b36c != 0)
        FUN_00408900(thisObject + 0xf, &DAT_0112b36c, 0x8000);
    if (DAT_0112e0fc != 0)
        FUN_00408900(thisObject + 0xf, &DAT_0112e0fc, 0x8000);

    // Register this object for game loop updates (IDs 1 and 0x17)
    FUN_008f6f50(1, thisObject);
    FUN_008f6f50(0x17, thisObject);

    FUN_007383a0();

    // Proximity-based event trigger (check bit 7 of flag at 0x7d5)
    if (((((uint)thisObject[0x7d5] >> 7 & 1) != 0) &&
         (iVar4 = **(int **)(DAT_012233a0 + 4), iVar4 != 0)) &&
        ((iVar4 + -0x1f30 != 0 &&
          ((_DAT_00d577a0 < *(float *)(iVar4 + 0x11b4) &&
           (DAT_01205228 - *(float *)(iVar4 + 0x11b4) < *(float *)(iVar4 + 0x11a4)))))))
    {
        // Extract position from object at iVar4
        fStack_40 = *(float *)(iVar4 + 0x11b0);
        uStack_48 = *(undefined8 *)(iVar4 + 0x11a8); // x, y
        iVar5 = FUN_00471610(); // Get camera position
        fVar7 = *(float *)(iVar5 + 0x30) - (float)uStack_48;
        fVar8 = *(float *)(iVar5 + 0x34) - uStack_48._4_4_;
        fVar9 = *(float *)(iVar5 + 0x38) - fStack_40;
        // Squared distance check
        if (fVar9 * fVar9 + fVar8 * fVar8 + fVar7 * fVar7 < *(float *)(iVar4 + 0x11a0))
        {
            // Trigger sound/effect
            FUN_006ada80(0, 0xffffffff);
            uStack_20 = 0x68286e39;           // Some hash
            FUN_0044b210(iVar4 + -0x1f30);    // Adjust pointer
            uStack_48 = CONCAT44(auStack_24, DAT_0112ad8c);
            fStack_40 = (float)((uint)fStack_40 & 0xffffff00);
            FUN_00408bf0(&uStack_48, thisObject + 0xf, 0); // Send event
            unknown = 0;
            uVar3 = FUN_006fbc40(0, 0);
            FUN_007f96a0(0, 0x10, uVar3, unknown);
            FUN_006fbc70();
            FUN_006ad490();
        }
    }

    // Check respawn/revive condition
    if ((thisObject[0x99f] != 0) && ((thisObject[0x7a7] == 0 || (thisObject[0x7a7] == 0x48))))
    {
        tempByte = FUN_007f7c60();
        if (tempByte == '\0')
        {
            FUN_007ff260(thisObject[0x99f]);
        }
    }

    // Handle death/respawn sequence
    tempByte = FUN_007f4800();
    if (tempByte != '\0')
    {
        FUN_0072de20(thisObject);
        uStack_14 = 1;
        ppuStack_c = &PTR_LAB_00e51890;
        FUN_0081dab0(auStack_24);
        FUN_0072c130();
    }

    // Virtual call with parameters (1,1)
    (**(code **)(*thisObject + 0x290))(1, 1);

    // Animation or state transition based on offset 0x842 and 0x841
    puVar6 = (undefined1 *)thisObject[0x842];
    if (puVar6 == (undefined1 *)0x0)
    {
        puVar6 = &DAT_0120546e;
    }
    iVar4 = thisObject[0x841];
    if ((iVar4 != 0x12) && (((uint)thisObject[0x7d5] >> 0x19 & 1) == 0))
    {
        tempByte = (**(code **)(*thisObject + 0x1bc))(); // Virtual check
        if (tempByte == '\0')
        {
            if ((*(byte *)(thisObject + 0x7e6) & 0x70) != 0)
            {
                iVar4 = 4;
            }
        }
        else
        {
            iVar4 = 3;
        }
    }

    FUN_00737940(iVar4, puVar6);

    // If bit 0 of flag at 0x7d5 is set, call function with global
    if ((*(byte *)(thisObject + 0x7d5) & 1) != 0)
    {
        FUN_004603c0(_DAT_00d6306c);
    }

    return;
}