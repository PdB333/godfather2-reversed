// FUN_NAME: AlphaFader::updateFade

void __thiscall AlphaFader::updateFade(void* target, uint unused)
{
    // Global current progress value (time or alpha)
    const float currentTime = g_currentTime;
    float blend = 0.0f;
    float localBlend = 0.0f;

    // Piecewise linear interpolation between keyframe times in the object
    if (this->startTime <= currentTime) {
        blend = this->mid1Time; // initial value, will be overwritten
        if (currentTime < this->mid1Time) {
            // First segment: linear from 0 to 1 between startTime and mid1Time
            blend = (currentTime - this->mid1Time) / (this->mid1Time - this->startTime);
        }
        else {
            float mid2 = this->mid2Time;
            if (currentTime < mid2) {
                // Constant plateau at 1.0 (or specified constant)
                localBlend = 1.0f; // _DAT_00d5780c is assumed to be 1.0
                blend = 1.0f;
            }
            else {
                blend = localBlend; // 0.0 initially
                if (currentTime < this->endTime) {
                    // Third segment: linear from 1 back to 0 between mid2Time and endTime
                    blend = 1.0f - (currentTime - mid2) / (this->endTime - mid2);
                }
            }
        }
    }

    // Apply the computed blend to the target object
    setAlpha(target, this->targetHandle, blend);

    // Check if we've reached the end of the fade and reset state if so
    if (this->endTime <= currentTime && currentTime != this->endTime) {
        this->flags = 0;           // +0x14
        this->targetHandle = 0;    // +0x10
    }
}