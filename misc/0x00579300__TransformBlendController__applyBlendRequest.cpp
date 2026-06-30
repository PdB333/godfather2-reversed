// FUNC_NAME: TransformBlendController::applyBlendRequest
// Address: 0x00579300
// Role: Applies a blend target to a transform interpolation state, updating the current blend state.

char __thiscall TransformBlendController::applyBlendRequest(int this, int blendRequest) // this: pointer to BlendController, blendRequest: pointer to BlendRequest
{
    char cVar1;
    int iVar2;
    undefined4 uVar3;
    int local_5c; // start of interpolation parameters struct (stored on stack)
    int local_58;
    int local_54; // interpolation type (blend mode)
    undefined4 local_50; // padding/unused
    char local_4c; // flag indicating interpolation is active after setup
    undefined4 local_48; // unused
    int local_40; // pointer to this for interpolation computation
    undefined4 local_3c; // source x (from this+0x20)
    float local_38; // source y (from this+0x24 minus offset)
    float local_30; // output interpolated x (position)
    undefined4 uStack_2c; // output interpolated y
    undefined4 uStack_28; // output interpolated z
    float fStack_24; // output interpolated w (if quaternion)
    undefined4 local_20; // output interpolated x2 (rotation quaternion)
    undefined4 uStack_1c; // output interpolated y2
    undefined4 uStack_18; // output interpolated z2
    float fStack_14; // output interpolated w2

    cVar1 = FUN_00581f60(blendRequest); // Check if blending is allowed or if request is active

    if (*(char *)(blendRequest + 0x10) != '\0') { // Check blend request flag (+0x10)
        // Initialize interpolation parameters structure on stack
        local_50 = 0;
        local_54 = (uint)(cVar1 != '\0') * 2 + -4; // Set blend mode: -2 if active, -4 otherwise
        local_4c = '\0'; // Will be set by the setup function if interpolation is possible
        local_48 = 0;
        local_5c = this; // Pointer to self as current state
        local_58 = this; // Duplicate pointer (maybe for source)
        iVar2 = FUN_00587a00(&local_5c); // Initialize interpolation parameters (fills local_4c)

        if (-1 < iVar2) { // Success
            if (local_4c != '\0') { // Interpolation is now active
                // Prepare input for interpolation computation
                uStack_28 = 0;
                uStack_2c = 0;
                local_30 = 0;
                uStack_18 = 0;
                uStack_1c = 0;
                local_20 = 0;
                local_3c = *(undefined4 *)(this + 0x20); // Current target x from this->targetOffset
                local_38 = *(float *)(this + 0x24) - DAT_00e2b1a4; // Current target y minus some constant (likely zero offset)
                fStack_24 = DAT_00e2b1a4; // Set to zero
                fStack_14 = DAT_00e2b1a4; // Set to zero
                local_40 = this; // Pass self to compute interpolation
                FUN_00581d70(&local_40); // Compute interpolated transform (output stored in local_30..fStack_14)

                // Copy interpolated result to this object at offset +0x40 to +0x5c (likely position + rotation)
                *(undefined4 *)(this + 0x40) = local_30;
                *(undefined4 *)(this + 0x44) = uStack_2c;
                *(undefined4 *)(this + 0x48) = uStack_28;
                *(float *)(this + 0x4c) = fStack_24;
                *(undefined4 *)(this + 0x50) = local_20;
                *(undefined4 *)(this + 0x54) = uStack_1c;
                *(undefined4 *)(this + 0x58) = uStack_18;
                *(float *)(this + 0x5c) = fStack_14;

                // Get current game time and set as blend start time
                uVar3 = FUN_00579870(); // Get game time (ms?)
                FUN_00579450(this, uVar3); // Set blend start timestamp at this+0x14?

                // Mark interpolation as active (bit 0)
                *(uint *)(this + 0x10) = *(uint *)(this + 0x10) | 1;

                // Accumulate blend request delta (offset) into this->blendAccumulator (+0x1c)
                *(float *)(this + 0x1c) = *(float *)(blendRequest + 8) + *(float *)(this + 0x1c);

                return cVar1;
            }
            // If interpolation not active (local_4c==0), still set start time? 
            uVar3 = FUN_00579870();
            FUN_00579450(this, uVar3);
        }
    }
    return cVar1;
}