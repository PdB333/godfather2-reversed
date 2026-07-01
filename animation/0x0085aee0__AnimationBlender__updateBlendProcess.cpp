// FUNC_NAME: AnimationBlender::updateBlendProcess
int __thiscall AnimationBlender::updateBlendProcess(int this, int blendIndex, float* startPos, float* endPos, float weightThreshold, float* outPos, int blendTime)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar18;
    int iVar8;
    int iVar9;
    bool anyBelowThreshold;
    byte flagByte;
    char activeFlag;
    int loopIndex;
    int* layerPtr;
    uint bitMask;
    float* weightPtr;
    uint loopIdx2;
    float fVar18Local;

    // Constants (likely 1.0f and 0.0f)
    const float ONE = 1.0f; // placeholder for _DAT_00d5780c
    const float ZERO = 0.0f; // placeholder for _DAT_00d577a0

    fVar1 = *startPos;
    fVar2 = startPos[1];
    fVar3 = startPos[2];
    fVar4 = *endPos;
    fVar5 = endPos[1];
    fVar6 = endPos[2];

    // Temporary arrays for weights (8 entries of 5 floats?) and output positions (8 entries of 3 floats)
    float blendWeights[8*5]; // oversized for clarity
    float outputPositions[8*3]; // actually local_70

    float *weightArrayStart = blendWeights; // local_3a8
    float *positionArrayStart = outputPositions; // local_3a0
    uint positionIndex = 0;
    uint weightIndex = 0;
    bitMask = 0;
    uint underThresholdMask = 0;
    flagByte = *(byte*)(this + 0x1c0) & 1; // +0x1c0: flag for world/local space? 0 = local?

    // Initialize blend weights to ONE
    for (int i = 0; i < 8*5; i++) {
        blendWeights[i] = ONE;
    }

    // First pass: compute blended positions for active layers
    layerPtr = (int*)(this + 0x128); // +0x128: array of 8 pointers to layer data
    for (size_t i = 0; i < 8; i++) {
        iVar8 = layerPtr[8]; // offset 8 in layer struct: maybe bone index?
        iVar9 = *layerPtr;    // offset 0: maybe animation controller?

        if ((iVar8 != 0) && (iVar9 != 0)) {
            // Get some transform ID
            int transformId = FUN_005466a0(); // likely returns a transform handle
            FUN_00aa1cf0(transformId + 0xe0, iVar9 + 0xe0); // copy transform matrices

            // Call virtual function at vtable+0x20 on object at iVar8 (likely a bone or controller)
            activeFlag = (**(code (__thiscall*)(int))(** (int**)(iVar8 + 0x10) + 0x20))(iVar8 + 0x10);

            if (activeFlag != 0) {
                fVar7 = *weightArrayStart;
                fVar18 = ONE - fVar7;
                // Lerp between startPos and endPos using weight
                positionArrayStart[0] = fVar7 * fVar4 + fVar18 * fVar1;
                positionArrayStart[1] = fVar5 * fVar7 + fVar18 * fVar2;
                positionArrayStart[2] = fVar6 * fVar7 + fVar3 * fVar18;

                if (fVar7 <= weightThreshold) {
                    anyBelowThreshold = true;
                }

                if (ZERO <= fVar7) {
                    fVar18 = positionArrayStart[1];
                    fVar7 = positionArrayStart[2];
                    *outPos = *positionArrayStart;
                    outPos[1] = fVar18;
                    outPos[2] = fVar7;
                }

                underThresholdMask++;
                bitMask |= 1 << (i & 0x1f);
            }
        }
        weightArrayStart += 5; // each entry is 5 floats? (0x14 bytes)
        positionArrayStart += 3;
        loopIndex = i;
    }

    if (anyBelowThreshold) {
        if (underThresholdMask == 0) {
            return 0;
        }

        weightArrayStart = (float*)(&blendWeights); // reset to start of weights array
        positionArrayStart = (float*)(this + 0x148); // +0x148: array of 8 pointers to output structures
        float* srcPositions = outputPositions;

        for (size_t i = 0; i < 8; i++) {
            if ((bitMask & (1 << (i & 0x1f))) != 0) {
                if ((i < 8) || ((byte)(*(uint*)(this + 0xd0) >> (*(char*)(&DAT_00e5407c)[i*2] * 4 & 0x1f)) & 0xf) < 0xc) {
                    // Perform collision query
                    bool collisionResult = FUN_00854e90(blendTime, (int)*positionArrayStart + 0x10, weightArrayStart, startPos, srcPositions, *(int*)(this + 0xf8), *(int*)((int)*positionArrayStart + 0x10), 0);
                    if (flagByte == 0) {
                        FUN_00854750(*(int*)(this + 0xf8), srcPositions, (uint)i, 0x10);
                    }
                }
            }
            positionArrayStart++;
            weightArrayStart = (float*)((int)weightArrayStart + 0x50); // skip 0x50 bytes (8*? )
            srcPositions += 3;
        }
    }

    if (underThresholdMask != 0) {
        if (flagByte != 0) {
            return 2;
        }
        char code = FUN_00859fd0(blendIndex, *(int8_t*)startPos, startPos[2], *(int8_t*)endPos, endPos[2], blendTime);
        if (code == 0) {
            return ( (underThresholdMask < 2) ? 0xfffffffe : 0 ) + 3; // return 3 if >=2 else 1?
        }
    }
    return 0;
}