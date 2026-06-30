// FUNC_NAME: Animation::loopTime

struct LoopTimeResult {
    float time;           // +0x00
    int32_t startFrame;   // +0x04 (stored as float, but used as integer)
    int32_t endFrame;     // +0x08 (stored as float, used as integer)
    float fraction;       // +0x0C
    bool wrapped;         // +0x10
};

// Global constants from the game binary
extern const float kLoopEpsilon;      // DAT_00e2b1a4
extern const float kLoopThreshold;    // DAT_00e2cd54
extern const float kLoopMax;          // DAT_00e2b334
extern const float kLoopMin;          // DAT_00e4461c
extern const float kLoopUnknown;      // DAT_00e44564
extern const uint32_t kLoopMask;      // DAT_00e44680

void __thiscall Animation::loopTime(
    LoopTimeResult* _this,
    float currentTime,
    float duration,
    char loop,
    uint32_t flags
) {
    float fVar1 = kLoopEpsilon;        // Basic wrap unit
    float maxTime = duration;          // Provided via XMM2 register
    float curTime = currentTime;       // Provided via XMM3 register

    // Negative wrap
    if (curTime < 0.0f) {
        if (loop == 0 || maxTime <= fVar1) {
            curTime = 0.0f;
        } else {
            do {
                curTime = (maxTime - fVar1) + curTime;
            } while (curTime < 0.0f);
        }
    }

    // Scale by frame size (assumed 1/step)
    float stepScale = fVar1 / _this->time; // Note: _this->time reused, but stepScale = 1/step essentially
    _this->time = stepScale * curTime;

    // Note: unaff_EDI is assumed to be a hidden parameter (numFrames).
    // Here it's represented as a member variable of the calling class.
    // For reconstruction we use an arbitrary constant.
    int32_t numFrames = 10; // Placeholder; should be passed in EDI

    if (numFrames < 1 || _this->time < (float)(numFrames - 1)) {
        _this->startFrame = (int32_t)_this->time;
        if (_this->startFrame < 0) {
            _this->startFrame = 0;
        }
        float frac = _this->time - (float)_this->startFrame;
        _this->endFrame = (_this->startFrame + 1) % (int32_t)maxTime;
        _this->fraction = frac;
    } else {
        float overflow = (_this->time - (float)numFrames) + fVar1;
        _this->startFrame = numFrames - 1;
        _this->endFrame = 0;
        if (overflow != 0.0f) {
            float nextOverflow = ((maxTime - fVar1) * stepScale - (float)numFrames) + fVar1;
            if (nextOverflow != 0.0f) {
                overflow = overflow / nextOverflow;
                _this->fraction = overflow;
            } else {
                _this->fraction = 0.0f;
            }
        } else {
            _this->fraction = 0.0f;
        }
    }

    _this->wrapped = _this->endFrame < _this->startFrame;

    // If not looping, snap end to start
    if (_this->endFrame < _this->startFrame && loop == 0) {
        _this->endFrame = _this->startFrame;
        _this->time = (float)numFrames - fVar1;
        _this->wrapped = false;
    }

    // Second wrapping pass based on flags
    float fVar3 = kLoopThreshold;
    if ((flags & 0x8000) == 0) {
        fVar3 = kLoopMax;
        if ((flags & 0x4000) != 0) {
            fVar3 = kLoopMin;
        }
    }

    float cond1 = (float)((uint32_t)(kLoopUnknown - _this->fraction) & kLoopMask);
    float cond2 = (float)((uint32_t)(fVar1 - _this->fraction) & kLoopMask);

    if (fVar3 < cond1) {
        if (fVar3 > cond2) {
            _this->endFrame = _this->startFrame;
            goto done;
        }
    } else {
        _this->endFrame = _this->startFrame;
    }

    _this->time = (float)_this->startFrame;

done:
    if (_this->startFrame == _this->endFrame) {
        _this->fraction = 0.0f;
        _this->time = (float)_this->startFrame;
    }
}