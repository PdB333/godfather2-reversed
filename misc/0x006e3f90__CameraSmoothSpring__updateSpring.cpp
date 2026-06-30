// FUNC_NAME: CameraSmoothSpring::updateSpring
// Address: 0x006e3f90
// Function: Updates a spring-damper system for camera smoothing.
// Uses a pair of floats per axis (position, velocity) stored in an array at this+0x128.
// Applies sinusoidal interpolation and damping based on thresholds and stiffness.

float CameraSmoothSpring::updateSpring(int this, int axisIndex, float deltaTime, float threshold, float stiffness)
{
    float *axisData = *(float **)(this + 0x128) + (axisIndex * 2); // Each axis has 2 floats: [position, velocity]
    float targetValue = DAT_01205228; // Global target value (e.g., desired position)
    float diff = targetValue - axisData[0]; // Difference from current position to target
    
    if (diff < threshold)
    {
        float velocityDiff = deltaTime - axisData[1]; // deltaTime minus current velocity (??)
        // Compute sine of scaled difference
        double sinArg = (double)((diff / threshold) * DAT_00d5f00c); // DAT_00d5f00c likely 2*PI or similar
        sin_radians(); // FPU call to sin, result on stack
        float sinVal = (float)sinArg;
        float newVelocity = sinVal * velocityDiff + axisData[1];
        axisData[1] = newVelocity;
        
        if (stiffness > 0.0f)
        {
            if (deltaTime <= stiffness)
            {
                if (deltaTime < (DAT_00e44564 - stiffness))
                {
                    stiffness = stiffness * DAT_00d5eee4; // Scale stiffness (DAT_00d5eee4 likely 0.5 or similar)
                    newVelocity = stiffness * sinVal + newVelocity;
                    axisData[1] = newVelocity;
                    if (stiffness <= newVelocity)
                    {
                        axisData[1] = newVelocity - stiffness;
                        axisData[0] = targetValue;
                        return axisData[1];
                    }
                }
                // else fall through to final
                goto setTargetAndReturn;
            }
            else // deltaTime > stiffness
            {
                stiffness = stiffness * DAT_00d5eee4;
                newVelocity = newVelocity - stiffness * sinVal;
                axisData[1] = newVelocity;
                if (newVelocity >= 0.0f)
                    goto setTargetAndReturn;
                deltaTime = newVelocity + stiffness;
            }
        }
    }
    axisData[1] = deltaTime;

setTargetAndReturn:
    axisData[0] = targetValue;
    return axisData[1];
}