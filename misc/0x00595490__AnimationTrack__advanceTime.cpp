// FUNC_NAME: AnimationTrack::advanceTime
// Function address: 0x00595490
// Advances the animation track's time by a delta, updating the current keyframe index based on keyframe times.
class AnimationTrack {
public:
    // +0x00: accumulated elapsed time
    float elapsed;
    // +0x04: current keyframe index (ushort)
    uint16_t curIndex;
    // +0x06: total number of keyframes (ushort)
    uint16_t keyCount;
    // +0x08: keyframe stride mode (0=8,1=16,2=20,3=24 bytes per keyframe)
    uint16_t mode;
    // +0x0C: pointer to keyframe data array (first float is time)
    float* keyframeData;

    // Advance the track by delta time
    void __thiscall advanceTime(float delta) {
        // Update accumulated time
        elapsed += delta;
        float curTime = elapsed;
        uint16_t idx = curIndex;
        uint16_t count = keyCount;
        uint16_t strideMode = mode;
        float* keyBase = keyframeData;

        switch (strideMode) {
        case 0: { // stride = 8
            // If time regressed below previous keyframe time, reset to index 1
            if (curTime < *(float*)((uint8_t*)keyBase - 8 + idx * 8)) {
                curIndex = 1;
                idx = 1;
            }
            // Advance while current keyframe time is <= elapsed time
            while (idx < count) {
                if (curTime < *(float*)((uint8_t*)keyBase + idx * 8)) {
                    break;
                }
                idx++;
                curIndex = idx;
                if (count <= idx) {
                    return;
                }
            }
            break;
        }
        case 1: { // stride = 16
            if (curTime < *(float*)((uint8_t*)keyBase - 16 + idx * 16)) {
                curIndex = 1;
                idx = 1;
            }
            while (idx < count) {
                if (curTime < *(float*)((uint8_t*)keyBase + idx * 16)) {
                    break;
                }
                idx++;
                curIndex = idx;
                if (count <= idx) {
                    return;
                }
            }
            break;
        }
        case 2: { // stride = 20
            if (curTime < *(float*)((uint8_t*)keyBase - 20 + idx * 20)) {
                curIndex = 1;
                idx = 1;
            }
            while (idx < count) {
                if (curTime < *(float*)((uint8_t*)keyBase + idx * 20)) {
                    break;
                }
                idx++;
                curIndex = idx;
                if (count <= idx) {
                    return;
                }
            }
            break;
        }
        case 3: { // stride = 24
            if (curTime < *(float*)((uint8_t*)keyBase - 24 + idx * 24)) {
                curIndex = 1;
                idx = 1;
            }
            // do-while style: check and increment
            if (idx < count) {
                do {
                    if (curTime < *(float*)((uint8_t*)keyBase + idx * 24)) {
                        return;
                    }
                    idx++;
                    curIndex = idx;
                } while (idx < count);
            }
            break;
        }
        }
    }
};