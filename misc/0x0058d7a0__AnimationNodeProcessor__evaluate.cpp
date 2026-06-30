// FUNC_NAME: AnimationNodeProcessor::evaluate
undefined4 __thiscall AnimationNodeProcessor::evaluate(
    float deltaTime,
    int entity,
    int nodeDesc,
    int *transformArray,
    float blendWeight1,
    float blendWeight2,
    uint flags,
    float blendWeight3
)
{
    byte bVar1;
    uint *puVar2;
    uint uVar3;
    float *pfVar4;
    undefined4 uVar5;
    float in_XMM0_Da; // from xmm0 register
    float fVar6;
    float local_4;

    // Check node state: byte at nodeDesc+1 indicates active? 0 means inactive
    if (*(char *)(nodeDesc + 1) < 1) {
        return 0;
    }

    puVar2 = *(uint **)(nodeDesc + 4);       // +0x04: pointer to keyframe data (array of uints?)
    uVar3 = *puVar2;                         // first uint: current index?
    local_4 = deltaTime;
    // Check if index out of bounds (transformArray[1] is count?)
    if ((uint)transformArray[1] <= uVar3) {
        in_XMM0_Da = 0.0f;
        local_4 = 0.0f;
        clampToZero(&local_4);               // FUN_00591c00
    }

    fVar6 = *(float *)(*transformArray + uVar3 * 4); // keyframe value from array

    // Condition: if not flag 4, no blend, and entity has some flag and state
    if ((((flags & 4) == 0) && (puVar2[1] == 0)) &&
        ((*(byte *)(*(int *)(entity + 0x7c) + 0x10) & 1) != 0) &&
        (*(char *)(*(int *)(entity + 0x7c) + 0x30) != 0)) {
        debugLog();                            // FUN_00593700
        // Compute blend result from keyframe data
        local_4 = in_XMM0_Da * (float)puVar2[3] + (float)puVar2[2];
        pfVar4 = (float *)getTransformArray(transformArray); // FUN_0058abc0
        *pfVar4 = local_4;
        fVar6 = local_4;
    }

    // If result non-positive, use global minimum constant
    if (fVar6 <= 0.0f) {
        fVar6 = g_minAnimationValue; // DAT_00e2b1a4
    }

    bVar1 = **(byte **)(nodeDesc + 0xc);       // +0x0c: node type byte
    if ((bVar1 & 0x3f) < 0x23) {
        // Dispatch to specific handler based on node type
        fVar6 = g_minAnimationValue / fVar6;
        uVar5 = (*(code **)(g_nodeHandlerTable + (bVar1 & 0x3f) * 4)) // DAT_0103afc0
                    (entity, *(byte **)(nodeDesc + 0xc), transformArray,
                     fVar6 * blendWeight1, fVar6 * blendWeight2,
                     flags, fVar6 * blendWeight3);
        return uVar5;
    }

    return 0;
}