// FUNC_NAME: AnimationBlender::updateNodes
void AnimationBlender::updateNodes(AnimationContext* ctx, void* outPose, void* blendBuffer)
{
    int count = *(int*)((char*)ctx + 0x34);
    int nodeBase = *(int*)((char*)ctx + 0x50);
    int nodePtr = nodeBase;
    float delta = gBlendDelta;

    while (nodePtr != count * 0xB0 + nodeBase) {
        gBlendDelta = delta; // restore global each iteration (unnecessary but preserves behavior)

        AnimationNode* node = (AnimationNode*)nodePtr;

        if (node->active == 1) {
            if (node->flags & 8) { // bit 3 set
                if (node->otherFlag == 0) {
                    // first sub-case: interpolate from node's own keyframes
                    if (ctx->flag2f != 0 || (node->flags & 0x10) == 0) {
                        FUN_00417560(); // some setup
                        float* keyFrames = node->keyFramesPtr;
                        float dx = (keyFrames[4] - keyFrames[0]) * delta;
                        float dy = (keyFrames[5] - keyFrames[1]) * delta;
                        float dz = (keyFrames[6] - keyFrames[2]) * delta;
                        float dist = sqrtf(dx*dx + dy*dy + dz*dz);
                        float interpolatedPos[3];
                        interpolatedPos[0] = keyFrames[0] + dx;
                        interpolatedPos[1] = keyFrames[1] + dy;
                        interpolatedPos[2] = keyFrames[2] + dz;
                        // compute blend result into local_50 buffer (size 76)
                        FUN_0042a1a0(interpolatedPos, local_50); 
                        blendResult = local_60; // 16-byte buffer, maybe quaternion
                    }
                } else { // otherFlag != 0
                    // second sub-case: use keyframes from another array, indexed by node
                    if (ctx->flag2f != 0) {
                        int nodeIndex = (nodePtr - nodeBase) / 0xB0;
                        int arrayOffset = (int)ctx + 0x58 + (*(char*)((char*)ctx + 0x2D) ^ 1) * 4;
                        int keyArrayBase = *(int*)arrayOffset;
                        float* keyFrames = (float*)(nodeIndex * 0x20 + keyArrayBase);
                        float dx = (keyFrames[4] - keyFrames[0]) * delta;
                        float dy = (keyFrames[5] - keyFrames[1]) * delta;
                        float dz = (keyFrames[6] - keyFrames[2]) * delta;
                        float dist = sqrtf(dx*dx + dy*dy + dz*dz);
                        float interpolatedPos[3];
                        interpolatedPos[0] = keyFrames[0] + dx;
                        interpolatedPos[1] = keyFrames[1] + dy;
                        interpolatedPos[2] = keyFrames[2] + dz;
                        // second arg: node->someOffset + 0x30 (maybe a transform to blend into)
                        FUN_0042a1a0(interpolatedPos, *(int*)(nodePtr + 0x5C) + 0x30);
                        blendResult = local_60;
                    }
                }
            }
        } else {
            // node not active: directly compute blend from node's data at +0x10 into outPose
            FUN_0042a1a0((char*)node + 0x10, outPose);
            blendResult = local_60;
        }

        // always apply blend output if blendType is in accepted range
        if (node->blendType <= 5) {
            FUN_004c4d80(outPose, blendResult);
        }

        nodePtr += 0xB0;
        delta = gBlendDelta;
    }

    gBlendDelta = delta;
}