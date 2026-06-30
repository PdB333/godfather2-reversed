// FUNC_NAME: AnimationController::processKeyframe
void __thiscall AnimationController::processKeyframe(float time, AnimationKeyframeData* keyframeData, float** outputBuffer) {
    // this +0x7c points to a state struct; +0x2c is the animation state enum
    if (*(int*)(*(int*)((int)this + 0x7c) + 0x2c) == 2) {
        return;  // animation not in a state that allows keyframe processing
    }

    // keyframeData+0x4 points to an array of keyframe parameters
    int* keyframeParams = *(int**)((int)keyframeData + 4);
    int keyframeId = keyframeParams[0];       // index into the function table
    float adjustedTime = time;                // copy since callback may modify it

    // Check keyframeId against global function table bounds
    if (keyframeId >= 0 && keyframeId < sKeyframeOpsCount) {
        // sKeyframeOpsTable: array of 0xC-byte entries; function pointer at offset +4
        KeyframeOpFunc callback = *(KeyframeOpFunc*)(sKeyframeOpsTable + 4 + keyframeId * 0xC);
        if (callback != nullptr) {
            callback(this, keyframeId, &adjustedTime);
        }
    }

    int currentIndex = keyframeParams[3];  // next write index in output buffer
    int capacity = (*outputBuffer)[1];     // outputBuffer[0] = float* base, [1] = capacity

    // Bounds check: if index exceeds capacity, report error and possibly reset
    if ((unsigned int)capacity <= (unsigned int)currentIndex) {
        int dummy = 0;
        reportError(&dummy);  // FUN_00591c00: likely handles overflow / logging
    }

    // Normalize adjustedTime relative to base (keyframeParams[1]) and range (keyframeParams[2])
    // Store into output buffer at current index
    float* bufferBase = *outputBuffer;
    bufferBase[currentIndex] = (adjustedTime - (float)keyframeParams[1]) / (float)keyframeParams[2];
}