// FUN_NAME: 0x00457780: PlayerController::processMovementUpdate

void __thiscall PlayerController::processMovementUpdate(void *thisPtr, int *packetData)
{
    float fVar1;
    undefined4 uVar2;
    bool bVar3;
    bool bVar4;
    bool bVar5;
    int iVar6;
    float fVar7;
    float local_30;
    float local_2c;
    undefined8 local_28;
    undefined4 local_20;
    float local_18;
    undefined4 local_10;

    // Check command type matches expected global
    if (*packetData != MOVEMENT_COMMAND_ID) {
        return;
    }

    uVar2 = *(undefined4 *)((int)thisPtr + 0xd8);
    local_30 = DEFAULT_SPEED_VALUE;
    local_2c = DEFAULT_SPEED_VALUE;

    iVar6 = FUN_005dc670(*(undefined4 *)((int)thisPtr + 0xd0));
    if (iVar6 != 0) {
        FUN_005dd8a0(uVar2, &local_30);
    }

    fVar1 = *(float *)((int)thisPtr + 0xf0);
    fVar7 = *(float *)((int)thisPtr + 0xec);
    // Delta from previous velocity and threshold check
    bVar4 = VELOCITY_THRESHOLD < (float)((uint)(fVar7 - *(float *)((int)thisPtr + 0xe8)) & VELOCITY_MASK);
    bVar5 = VELOCITY_THRESHOLD < (float)((uint)(local_30 - *(float *)((int)thisPtr + 0xe4)) & VELOCITY_MASK);
    bVar3 = local_2c != *(float *)((int)thisPtr + 0xf4);

    if (bVar4) {
        // Velocity change in x dimension
        *(float *)((int)thisPtr + 0xe8) = fVar7;
        local_30 = fVar7 * local_30;
    }
    else {
        if (bVar5) {
            // Velocity change in y dimension
            fVar7 = *(float *)((int)thisPtr + 0xe8) * local_30;
            *(float *)((int)thisPtr + 0xe4) = local_30;
            local_30 = fVar7;
            if (fVar1 <= 0.0) {
                *(undefined4 *)((int)thisPtr + 0xf0) = VELOCITY_RESET_VALUE;
                goto LAB_004578cc;
            }
        }
        else if (fVar1 <= 0.0) {
            goto LAB_004578cc;
        }
        // Apply decay
        *(float *)((int)thisPtr + 0xf0) = fVar1 - VELOCITY_DECAY_CONSTANT;
    }

LAB_004578cc:
    // Clamp velocity to zero if below threshold
    if (*(float *)((int)thisPtr + 0xf0) <= 0.0 && *(float *)((int)thisPtr + 0xf0) != 0.0) {
        *(undefined4 *)((int)thisPtr + 0xf0) = 0;
    }

    // If any state changed and network system is active, send update
    if ((((bVar4) || (bVar5)) || (bVar3)) && (GAME_NETWORK_MANAGER != 0)) {
        FUN_00c9cbe0(GAME_NETWORK_MANAGER,
                     *(undefined4 *)(*(int *)(*(int *)((int)thisPtr + 0xc0) + 4) + 0x10),
                     0,
                     &local_28);
        local_28 = 0;
        local_18 = local_30;
        local_20 = *(undefined4 *)((int)thisPtr + 0xf0);
        local_10 = 0;
        FUN_00c9eac0(); // Begin packet build
        if ((bVar4) || (bVar5 != bVar4)) {
            FUN_00c9cd40(0, &local_28); // Add vector data
        }
        if (bVar3) {
            // Handle steering change
            if (0.0 < local_2c) {
                if (local_2c < ANGLE_CLAMP_MAX) {
                    local_30 = local_2c;
                }
                else {
                    local_30 = ANGLE_CLAMP_MAX;
                }
            }
            else {
                local_30 = 0.0;
            }
            FUN_00ca4e90(0, local_30); // Add angle data
            *(float *)((int)thisPtr + 0xf4) = local_2c;
        }
        FUN_00c9eae0(); // End and send packet
    }

    FUN_00457a10(); // Update other components

    // If object is active and velocity is zero, trigger stop event
    if ((*(char *)((int)thisPtr + 0xe0) != '\0') &&
        (*(float *)((int)thisPtr + 0xf0) <= VELOCITY_THRESHOLD &&
         VELOCITY_THRESHOLD != *(float *)((int)thisPtr + 0xf0))) {
        FUN_00458370(0);
    }
    return;
}