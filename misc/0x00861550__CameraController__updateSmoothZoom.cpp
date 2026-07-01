// FUNC_NAME: CameraController::updateSmoothZoom
// Function address: 0x00861550
// Role: Update a smoothed float (e.g., camera distance/zoom) and interpolate target transform based on delta time.
// The function selects parameter sets via a flag at this+0xC88 and updates a float at this+0x1030.

extern float s_defaultDeltaThreshold; // DAT_00d75870
extern float s_defaultStep;          // DAT_00d5eee4
extern float s_defaultWComponent;    // DAT_00d75778
extern float s_altDeltaThreshold;    // DAT_00d75874
extern float s_altStep;              // DAT_00d5c458 (overlapping with _DAT_)
extern float s_altWComponent;        // DAT_00d5d7b8
extern float s_targetValue;          // DAT_01205214 (threshold/limit)

void* getTransformData();  // FUN_00471610 (likely singleton getter, e.g., Player::getTransform)
void interpolateCameraTransform(void* transformVec, float deltaTime, int mode); // FUN_00416340

void __thiscall CameraController::updateSmoothZoom(float deltaTime)
{
    float threshold;
    float step;
    float wComponent;

    // Check bit 2 of flags at offset 0xC88 to select parameter set
    if ((*(unsigned int*)(this + 0xC88) >> 2) & 1)
    {
        threshold = s_altDeltaThreshold;
        step      = s_altStep;
        wComponent = s_altWComponent;
    }
    else
    {
        threshold = s_defaultDeltaThreshold;
        step      = s_defaultStep;
        wComponent = s_defaultWComponent;
    }

    // Only proceed if delta time exceeds threshold (to avoid tiny updates)
    if (threshold < deltaTime)
    {
        float* currentValue = (float*)(this + 0x1030); // +0x1030: smoothed float (zoom/distance)

        // If current value is <= target and target is different, advance towards target+offset
        if (*currentValue <= s_targetValue && s_targetValue != *currentValue)
        {
            *currentValue = s_targetValue + step; // Step beyond target (overshoot or bounce)

            // Obtain target transform data (e.g., player camera socket) from a singleton
            void* transformData = getTransformData();

            // Build a 4-component vector from transform offsets + w component
            float vec[4];
            vec[0] = *(float*)((int)transformData + 0x30);
            vec[1] = *(float*)((int)transformData + 0x34);
            vec[2] = *(float*)((int)transformData + 0x38);
            vec[3] = wComponent;

            // Interpolate the camera transform towards this target (mode 8 = e.g., linear)
            interpolateCameraTransform(vec, deltaTime, 8);
        }
    }
}