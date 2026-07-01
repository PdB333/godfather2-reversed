// FUNC_NAME: AnimationState::advanceTime
// Function address: 0x008c28b0
// Role: Updates a clamped animation time variable, optionally processing animation events when a condition is met.
// Fields:
//   this+0x54 : uint (animation ID or current state pointer)
//   this+0x104 : float (animation time or blend weight)
//   this+0x230 : int (flag enabling time update)
//   param_2+0xC0 : void* (pointer to animation event list)
//   param_2+0xC4 : int (event processing flag, 1 = process)
// Globals:
//   g_animTimeMin (0x00d7bcac)
//   g_animTimeMax (0x00d7bca8)

void __thiscall AnimationState::advanceTime(int param_2, float deltaTime)
{
    float fVar1;
    int iVar2, iVar3;
    uint uVar4;
    int updateFlag;

    // Truncate deltaTime to integer value (likely frame-based stepping)
    deltaTime = (float)(int)deltaTime;

    if (*(int *)(param_2 + 0xC4) == 1) {
        FUN_008c1d40(); // Reset or prepare animation state
        iVar3 = *(int *)(param_2 + 0xC0);
        if ((iVar3 != 0) && 
            (iVar2 = FUN_0084a410(), iVar2 == *(int *)(this + 0x54))) { // Current animation ID matches expected
            iVar2 = FUN_0084a5b0(); // Get current time stamp
            uVar4 = 0;
            if (*(int *)(iVar3 + 8) != 0) {
                do {
                    FUN_0084a3c0(uVar4); // Process event at index uVar4
                    FUN_006b3220();
                    uVar4 = uVar4 + 1;
                } while (uVar4 < *(uint *)(iVar3 + 8)); // Loop over event count
            }
            iVar3 = FUN_0084a5b0();
            deltaTime = (float)(iVar3 - iVar2) + deltaTime; // Add elapsed time
        }
    }

    // Determine update type based on deltaTime sign
    if (0.0f <= deltaTime) {
        if (*(int *)(this + 0x230) == 0) goto LAB_008c295d;
        updateFlag = 4;   // Positive direction flag
    } else {
        if (*(int *)(this + 0x230) == 0) goto LAB_008c295d;
        updateFlag = 10;  // Negative direction flag
    }
    FUN_00892490(deltaTime, updateFlag); // Apply time to blend or animation

LAB_008c295d:
    deltaTime = deltaTime + *(float *)(this + 0x104); // Add to current accumulated time
    fVar1 = g_animTimeMin; // 0x00d7bcac
    // Clamp deltaTime between min and max
    if ((deltaTime <= g_animTimeMin) || (fVar1 = g_animTimeMax, g_animTimeMax <= deltaTime)) {
        deltaTime = fVar1;
    }
    *(float *)(this + 0x104) = deltaTime;
    return;
}