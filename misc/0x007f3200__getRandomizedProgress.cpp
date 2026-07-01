// FUNC_NAME: getRandomizedProgress
float __thiscall getRandomizedProgress(void* this, float inputTime)
{
    // Global constants
    const float ONE = 1.0f;                       // DAT_00d5780c
    const float FRAMES_PER_SECOND = 60.0f;          // DAT_00d5e288
    const float BASE_OFFSET = 1.0f;                 // DAT_00e44564 (assumed)
    const float ROUND_ADJUST = 1.0f;                // DAT_00e44578 (assumed)
    const float SPEED_SCALE = 1.0f;                 // DAT_00d5f374 (assumed)
    const uint RANDOM_MASK = DAT_010c2678;          // mask for random index
    const float* RANDOM_VALUES = (float*)&DAT_010c2680; // array of random values
    static uint randomCounter = DAT_012054b4;       // shared counter

    // Known offsets for this object
    int   index = *(int*)((uint)this + 0x04);                 // animation index
    float* dataArray = *(float**)((uint)this + 0x08);          // pointer to keyframe data
    float* currentStep = (float*)((uint)this + 0x0C);         // current interpolation step
    float* currentPosition = (float*)((uint)this + 0x10);     // current progress position
    float* targetTime = (float*)((uint)this + 0x14);          // target time

    float target = *targetTime;
    if ((target <= inputTime) || (inputTime <= *currentPosition + *currentStep))
    {
        if (target < inputTime)
        {
            // Reset position to target
            *currentPosition = target;

            // Get random value for position interpolation
            uint randIdx = RANDOM_MASK & randomCounter++;
            float posStart = *(dataArray + 0x2c / 4 + index); // offset 0x2c
            float posEnd   = *(dataArray + 0x30 / 4 + index); // offset 0x30
            float diff = BASE_OFFSET - posEnd;
            float interp = (posEnd - diff) * RANDOM_VALUES[randIdx] + diff + posStart;
            if (interp < 0.0f)
                interp = posStart;
            *targetTime = interp * SPEED_SCALE + *currentPosition;

            // Get random value for step calculation
            randIdx = RANDOM_MASK & randomCounter++;
            float stepStart = *(dataArray + 0x34 / 4 + index); // offset 0x34
            float stepEnd   = *(dataArray + 0x38 / 4 + index); // offset 0x38
            diff = BASE_OFFSET - stepEnd;
            interp = (stepEnd - diff) * RANDOM_VALUES[randIdx] + diff + stepStart;
            *currentStep = interp * SPEED_SCALE;
            if (*currentStep <= 0.0f)
                *currentStep = stepStart * SPEED_SCALE;
        }

        // Convert remaining time to frame count
        float remainingTime = inputTime - *currentPosition;
        if (remainingTime >= 0.0f)
        {
            int frameCount = (int)(remainingTime / *currentStep * FRAMES_PER_SECOND);
            float progress = (float)frameCount;
            if (frameCount < 0)
                progress += ROUND_ADJUST;

            // Read full duration and end offset for clamping
            float fullDuration = *(dataArray + 0x3c / 4 + index); // offset 0x3c
            float endOffset   = *(dataArray + 0x40 / 4 + index); // offset 0x40

            if (fullDuration < progress)
            {
                if (progress > FRAMES_PER_SECOND - endOffset)
                {
                    // Clamp towards 1.0
                    progress = ONE - ((progress - FRAMES_PER_SECOND) + endOffset) / endOffset;
                }
                else
                {
                    return (float)ONE;
                }
            }
            else
            {
                progress /= fullDuration;
            }

            // Clamp progress to [0, 1]
            if (progress >= 0.0f)
            {
                if (progress > ONE)
                    progress = ONE;
                return progress;
            }
            return 0.0f;
        }
    }
    // If conditions not met, return 0
    return 0.0f;
}