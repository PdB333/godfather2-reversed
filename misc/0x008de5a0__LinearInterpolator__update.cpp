// FUNC_NAME: LinearInterpolator::update
// Address: 0x008de5a0
// Role: Updates a linear interpolation (fade in/out) based on elapsed time,
//       clamps result to [0, kThreshold], and marks completion.
// Structure offsets (param_1 is 'this'):
//   [0x00] mFinished (int32) - 1 if target reached, 0 otherwise
//   [0x04] mMode     (int32) - 1 = fade in, else fade out
//   [0x08] mCurrent  (float) - current interpolated value
//   [0x0C] mDurationIn  (float) - fade in duration (used when mMode==1)
//   [0x10] mDurationOut (float) - fade out duration
//   [0x14] mStartValue  (float) - target value for fade in (start value rate scaling)
//   [0x18] mLastTime    (float) - last time stamp update

void __thiscall LinearInterpolator::update(int* thisPtr, int newMode)
{
    float* fields = reinterpret_cast<float*>(thisPtr);
    int mode = thisPtr[1];                    // [0x04]
    float current = fields[2];                // [0x08]
    float durationIn = fields[3];             // [0x0C]
    float durationOut = fields[4];            // [0x10]
    float startValue = fields[5];             // [0x14]
    float lastTime = fields[6];               // [0x18]

    float deltaTime = gFrameTime;            // DAT_01205228 (global constant frame time, e.g., ~0.0167f)
    float kThreshold = gInterpolationThreshold; // _DAT_00d5780c (global threshold, likely 1.0f or similar)

    float newValue;
    if (mode == 1)
    {
        // Fade in: linear approach to startValue over durationIn
        // newCurrent = current + (startValue / durationIn) * (deltaTime - lastTime)
        newValue = (startValue / durationIn) * (deltaTime - lastTime) + current;
    }
    else
    {
        // Fade out: linear decay to zero over durationOut
        // newCurrent = current - (deltaTime - lastTime) / durationOut
        newValue = current - (deltaTime - lastTime) / durationOut;
    }

    // Update current value
    fields[2] = newValue;

    // Clamp and set finished flag
    float clampedValue = kThreshold; // default if newValue >= threshold
    if (newValue < kThreshold)
    {
        clampedValue = 0.0f;
        if (newValue > 0.0f)
            goto skip_finished_flag;
        *thisPtr = 0; // mFinished = 0 (not finished, hit zero)
    }
    else
    {
        *thisPtr = 1; // mFinished = 1 (reached threshold)
    }
    fields[2] = clampedValue;

skip_finished_flag:
    // Update last time and mode
    fields[6] = deltaTime;           // mLastTime = frame time
    thisPtr[1] = newMode;            // mMode = new mode for next update
}