// FUNC_NAME: VehicleInputHandler::updateThrottleSteering

void __fastcall VehicleInputHandler::updateThrottleSteering(void* this) {
    float fVar1;
    int iVar2;
    int iVar3;
    bool bVar4;
    float10 fVar5;
    double dVar6;
    double dVar7;
    float fVar8;
    float local_1c;

    // Get input source pointer (likely from this->+0x58)
    if (*(int*)((int)this + 0x58) == 0) {
        iVar2 = 0;
    } else {
        iVar2 = *(int*)((int)this + 0x58) - 0x48; // offset to input state
    }

    if (*(int*)((int)this + 0x58) == 0) {
        iVar3 = 0;
    } else {
        iVar3 = *(int*)((int)this + 0x58) - 0x48;
    }

    // Check if input device type is keyboard/mouse (0 or 0x48)
    if ((*(int*)(iVar3 + 0x24cc) != 0) && (*(int*)(iVar3 + 0x24cc) != 0x48)) {
        // Direct input mode (gamepad maybe?)
        if ((*(byte*)((int)this + 0x60) & 1) == 0) {
            FUN_007f62e0(); // Enter critical section
            *(unsigned short*)((int)this + 0x60) = *(unsigned short*)((int)this + 0x60) | 1;
        }
        iVar2 = FUN_00471610(); // Get input device instance (e.g. XInputManager)
        iVar3 = FUN_00471610(); // Get another instance (maybe same or different axis)
        fVar8 = *(float*)(iVar2 + 0x30); // Thrust axis raw value
        fVar1 = *(float*)(iVar3 + 0x30); // Steering axis raw value
        dVar6 = (double)(*(float*)(iVar2 + 0x34) - *(float*)(iVar3 + 0x34)); // Difference in something
        FUN_00b9a9fa(); // probably fabs or something
        dVar7 = (double)(fVar8 - fVar1); // Difference in thrust/steering
        FUN_00b9a9fa();
        iVar2 = FUN_00471610();
        fVar8 = *(float*)(iVar2 + 0x20); // Another axis (maybe trigger/throttle)
        FUN_007222b0(1); // Set mode?
        FUN_00722330((float)dVar6); // Set pitch (or throttle)
        dVar6 = (double)fVar8;
        FUN_00b9a9fa();
        fVar5 = (float10)FUN_004a1580((float)dVar7 - (float)dVar6); // Clamp/smooth
        FUN_00722310((float)fVar5); // Set yaw (or steering)
        FUN_007223d0(); // Commit
        return;
    }

    // Gamepad/analog input with smoothing
    if ((*(float*)(iVar2 + 0x1f80) == 0.0f) && (*(float*)(iVar2 + 0x1f7c) == 0.0f)) {
        return; // No input, nothing to do
    }

    if ((*(byte*)((int)this + 0x60) & 1) != 0) {
        FUN_007fbe50(); // Leave critical section
        *(unsigned short*)((int)this + 0x60) = *(unsigned short*)((int)this + 0x60) & 0xfffe;
    }

    local_1c = *(float*)(iVar2 + 0x1f80); // Thrust (forward/back)
    fVar8 = DAT_012067e8 * DAT_00d5eee4; // Frame time?

    // Apply deadzone and smoothing for thrust
    if (local_1c <= 0.0f) {
        if (local_1c < 0.0f) {
            local_1c = local_1c + fVar8;
            bVar4 = local_1c < 0.0f;
            goto LAB_0073efd7;
        }
    } else {
        local_1c = local_1c - fVar8;
        bVar4 = 0.0f < local_1c;
LAB_0073efd7:
        if (!bVar4 && local_1c != 0.0f) {
            local_1c = 0.0f;
        }
    }
    FUN_00722330(local_1c); // Set pitch/thrust

    local_1c = *(float*)(iVar2 + 0x1f7c); // Steering (left/right)
    // Apply deadzone and smoothing for steering
    if (local_1c <= 0.0f) {
        if (0.0f <= local_1c) goto LAB_0073f02e;
        local_1c = local_1c + fVar8;
        bVar4 = local_1c < 0.0f;
    } else {
        local_1c = local_1c - fVar8;
        bVar4 = 0.0f < local_1c;
    }
    if (!bVar4 && local_1c != 0.0f) {
        local_1c = 0.0f;
    }
LAB_0073f02e:
    FUN_00722310(local_1c); // Set yaw/steering
    FUN_007223d0(); // Commit
    return;
}