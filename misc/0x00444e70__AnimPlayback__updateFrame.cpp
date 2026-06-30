// FUNC_NAME: AnimPlayback::updateFrame
int AnimPlayback::updateFrame() {
    float frameDelta = g_frameTime; // DAT_00e2cd54 - time increment per frame
    uint timeDelta = g_gameTime - this->animStartTime; // current time minus start time (uint)
    AnimData* pAnimData = this->pAnimData; // +0x10
    int nextIdx = this->currentIdx + 1; // +0x0c
    bool bError = false;
    bool bFirstEntry = true; // flag to handle first entry before any advancement

    short numFrames = pAnimData->numFrames; // +0x06

    // Advance through keyframes that are within the time delta
    while (nextIdx < numFrames) {
        AnimKeyframe& key = pAnimData->pKeyframes[nextIdx]; // each keyframe is 4 bytes
        uint keyTime = key.timestamp; // first 2 bytes (ushort)
        if (timeDelta < keyTime) {
            if (bFirstEntry) {
                goto processCurrentFrame; // delta smaller than first frame, process current idx
            }
            break; // stop advancing past this keyframe
        }
        byte value = key.value; // byte at offset 3
        bFirstEntry = false;

        uint flags = key.flags; // byte at offset 2
        if ((flags & 0xF0) != 0) {
            uint typeIdx = (flags >> 4) - 1;
            float speedFactor = g_keyframeSpeedFactors[typeIdx]; // DAT_01223430 + 0x2e0
            if (speedFactor >= 0.0f) {
                value = (byte)(int)((value + frameDelta) * speedFactor);
            } else {
                bError = true;
            }
        }
        uint boneIdx = flags & 0xF;
        this->boneValues[boneIdx] = value; // +0x04 + boneIdx (byte array)

        this->currentIdx = nextIdx;
        nextIdx++;
    }

processCurrentFrame:
    // Handle the current frame (either first or after loop when delta falls within a frame)
    int curIdx = this->currentIdx;
    if (curIdx >= 0 && curIdx < numFrames) {
        AnimKeyframe& key = pAnimData->pKeyframes[curIdx];
        uint flags = key.flags;
        if ((flags & 0xF0) != 0) {
            uint typeIdx = (flags >> 4) - 1;
            float speedFactor = g_keyframeSpeedFactors[typeIdx];
            if (speedFactor >= 0.0f) {
                byte value = key.value;
                uint boneIdx = flags & 0xF;
                this->boneValues[boneIdx] = (byte)(int)((value + frameDelta) * speedFactor);
            } else {
                bError = true;
            }
        }
    }

    // Determine if animation is still playing
    if ((this->currentIdx != (numFrames - 1)) && (!bError)) {
        return 1; // still playing
    }

    // Animation finished, reset state
    this->pAnimData = nullptr;        // +0x10
    *(short*)(&this->animState) = 0; // +0x04 (assume short at +4 stores state)
    *(byte*)((char*)this + 6) = 0;  // +0x06 (byte flag)

    return 2; // animation ended
}