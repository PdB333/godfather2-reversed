// FUNC_NAME: AnimationBlendInterpolator::update
// Function address: 0x006db5d0
// This function advances a linear interpolation blend between two pose buffers.
// When the blend is complete (progress >= duration), it snaps to the target pose and resets state.
// Member fields (offsets relative to 'this'):
// +0x10 : currentPose (100 bytes, presumably 25 floats for joint transforms or similar)
// +0x74 : targetPose (100 bytes, the fully blended result)
// +0xd8 : blendDuration (float)
// +0xdc : blendElapsed (float, accumulates time)
// +0x1a0 : unknownByte (saved/restored across a call to FUN_006db520)
// +0x1a8 : blendState (int, 2 = running, 0 = idle)

void __thiscall AnimationBlendInterpolator::update(int this, float deltaTime)
{
    int iVar2;
    int *src;
    int *dst;

    if (*(int *)(this + 0x1a8) == 2) { // if blend is active
        if (*(float *)(this + 0xdc) <= *(float *)(this + 0xd8)) { // not yet finished? Actually condition: elapsed <= duration? Wait code: <=
            // Not finished: interpolation not executed? Actually the code does the ELSE if elapsed <= duration? The condition checks if elapsed <= duration, if true then copy? Let's re-read original:
            // if (*(float *)(param_1 + 0xd8) <= *(float *)(param_1 + 0xdc)) { // original: duration <= elapsed? No: (param_1+0xd8) is duration, (param_1+0xdc) is elapsed. So condition checks if duration <= elapsed. So if elapsed >= duration, it's done.
            // The decompiler wrote <= but that's the opposite? Let's double-check original line:
            // if (*(float *)(param_1 + 0xd8) <= *(float *)(param_1 + 0xdc)) 
            // param_1+0xd8 is duration, param_1+0xdc is elapsed. So if duration <= elapsed, that means blend has completed.
            // So condition is satisfied when blend is complete.
            // So the "if true" branch (complete) copies target to current, resets state.
            // The else branch does the interpolation.
        }
        // If completion condition holds (duration <= elapsed):
        // copy targetPose to currentPose
        src = (int *)(this + 0x74);
        dst = (int *)(this + 0x10);
        for (iVar2 = 0x19; iVar2 != 0; iVar2 = iVar2 + -1) {
            *dst = *src;
            src = src + 1;
            dst = dst + 1;
        }
        *(int *)(this + 0x1a8) = 0; // set state to idle
        return;
    }
    else {
        // Not complete: interpolate using ratio = elapsed/duration
        FUN_006dacd0(this + 0x74, *(float *)(this + 0xdc) / *(float *)(this + 0xd8));
        // FUN_006dacd0 likely performs a lerp or blend between source and target stored elsewhere, output to +0x74?
        // Save byte at +0x1a0 around call to FUN_006db520
        char savedByte = *(char *)(this + 0x1a0);
        FUN_006db520(); // update something (could be mark dirty or notify)
        *(char *)(this + 0x1a0) = savedByte; // restore
        *(float *)(this + 0xdc) = *(float *)(this + 0xdc) + deltaTime; // advance elapsed time
    }
    return;
}