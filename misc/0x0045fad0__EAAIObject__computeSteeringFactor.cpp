// FUNC_NAME: EAAIObject::computeSteeringFactor
// Function address: 0x0045fad0
// Purpose: Computes a normalized steering factor based on current vs target angle and a speed constant.
// The substruct at +0x218 holds steering state: +0x1c current angle, +0x24 target angle, +0x130 steering speed.
// The global at 0x011260b0 is a time scale factor.

double __fastcall EAAIObject::computeSteeringFactor()
{
    int* pSteeringState = *(int**)((int)this + 0x218);  // +0x218: pointer to steering state struct
    if (pSteeringState == 0) {
        return 0.0;
    }
    float currentAngle = *(float*)(pSteeringState + 0x1c);    // +0x1c: current steering angle
    float targetAngle = *(float*)(pSteeringState + 0x24);     // +0x24: target steering angle
    float steeringSpeed = *(float*)(pSteeringState + 0x130);  // +0x130: steering speed factor (inverse of time constant)
    float timeScale = *(float*)0x011260b0;                     // global time scale (e.g., frame delta multiplier)
    return (targetAngle - currentAngle) / (steeringSpeed * timeScale);
}