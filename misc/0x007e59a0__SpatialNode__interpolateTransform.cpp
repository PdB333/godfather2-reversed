// FUNC_NAME: SpatialNode::interpolateTransform
void SpatialNode::interpolateTransform(EARSSVector3& outPos, const EARSSVector3& currentPos, const EARSSVector3& targetPos, int object)
{
    char cVar1;
    int iVar2;
    int nodeHandle;
    uint tickCount;
    float interpolateFactor;
    float local_d0;
    float local_cc;
    float local_c8;
    float local_c4;
    float local_c0;
    float local_bc;
    float local_b8;
    float local_b4;
    byte local_b0;
    uint local_ac;
    int local_a0[3];
    byte local_94[20];
    void** vtableCheck;
    float blendFactor;
    float local_60;
    uint local_5c;
    uint local_50;
    int local_20;
    uint local_30;

    // Store target position into object's transform
    *(EARSSVector2*)(object + 0x251c) = *(EARSSVector2*)targetPos;
    *(float*)(object + 0x2524) = targetPos[2];

    // Get tick count and log the interpolation
    tickCount = FUN_0043b490(); // getTickCount()
    FUN_00540bc0(0x64122, 0x100001, &tickCount, 1); // log event

    // Setup local vectors for collision test
    local_d0 = targetPos[0];
    local_c0 = currentPos[0];
    local_cc = targetPos[1];
    local_c8 = targetPos[2];
    local_bc = currentPos[1];
    local_b8 = currentPos[2];
    local_b0 = 0;
    local_ac = 0;
    local_c4 = _DAT_00d5780c; // likely 0.0f
    local_b4 = _DAT_00d5780c;
    local_ac = FUN_00540cc0(local_94); // getInterpolationFactor()?

    // Initialize locals
    local_5c = 0xffffffff;
    local_50 = 0xffffffff;
    local_20 = 0;
    local_30 = 0;
    local_b0 = 1;
    vtableCheck = &PTR_FUN_00e32a8c; // vtable or static pointer
    local_60 = _DAT_00d5780c;
    blendFactor = _DAT_00d5780c;

    // Perform swept collision test
    FUN_009e5ed0(&local_d0, &vtableCheck);

    if (local_20 == 0) {
        // No collision: use current position directly
        *(EARSSVector2*)outPos = *(EARSSVector2*)currentPos;
        outPos[2] = currentPos[2];
    } else {
        // Interpolate: outPos = targetPos + (currentPos - targetPos) * blendFactor
        outPos[0] = (currentPos[0] - targetPos[0]) * blendFactor + targetPos[0];
        outPos[1] = (currentPos[1] - targetPos[1]) * blendFactor + targetPos[1];
        outPos[2] = (currentPos[2] - targetPos[2]) * blendFactor + targetPos[2];
    }

    nodeHandle = 0;
    // Attempt to obtain a node from the collision result
    if ((local_20 != 0) && (*(char*)(local_20 + 0x10) + local_20 != 0) &&
        (FUN_004af8c0(local_a0, 0x2001), nodeHandle = local_a0[0], local_a0[0] == 0)) {
        nodeHandle = 0;
    }
    if (nodeHandle != 0) {
        nodeHandle = nodeHandle + 0x48;
    }

    iVar2 = *(int*)(object + 0x2528);
    if (iVar2 != nodeHandle) {
        if (iVar2 != 0) {
            FUN_004daf90((int*)(object + 0x2528)); // free old node
        }
        *(int*)(object + 0x2528) = nodeHandle;
        if (nodeHandle != 0) {
            *(undefined4*)(object + 0x252c) = *(undefined4*)(nodeHandle + 4);
            *(int**)(nodeHandle + 4) = (int*)(object + 0x2528);
        }
    }

    // Check game state conditions
    iVar2 = FUN_0043b870(DAT_01130fb0); // isGamePaused? getGameState?
    if (((iVar2 != 0) && ((*(byte*)(object + 0x249f) & 1) == 0)) &&
        (cVar1 = FUN_00481660(), cVar1 == '\0')) {
        // Game is active and no cutscene playing: apply direct transform
        FUN_007e5120(currentPos, targetPos, object, iVar2);
        return;
    }
    // Otherwise, set blend factor to zero (no interpolation)
    FUN_0081efa0(0);
    return;
}