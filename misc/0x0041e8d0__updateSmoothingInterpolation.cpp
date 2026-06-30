// FUNC_NAME: updateSmoothingInterpolation

// Global state for smooth interpolation
// Timer counting down from a starting value
extern float gSmoothTimer;           // DAT_012053a4
// Frame delta time (seconds)
extern float gFrameDeltaTime;        // DAT_01206800
// Scaling factor for step size (used as multiplier on timer)
extern float gSmoothStepScale;       // DAT_012053a8

// Target (source) values to interpolate towards
extern float gSmoothTargetX;         // DAT_0120538c
extern float gSmoothTargetY;         // DAT_01205390
extern float gSmoothTargetZ;         // DAT_01205394

// Per-axis interpolation stiffness factors
extern float gSmoothStiffnessX;      // DAT_01205398
extern float gSmoothStiffnessY;      // DAT_0120539c
extern float gSmoothStiffnessZ;      // DAT_012053a0

// Current smoothed values (output)
extern float gSmoothCurrentX;        // DAT_011280f0
extern float gSmoothCurrentY;        // DAT_011280f4
extern float gSmoothCurrentZ;        // DAT_011280f8

void updateSmoothingInterpolation()
{
    float stepFactor = 0.0f;

    // If timer still active, decrement by frame delta
    if (gSmoothTimer != 0.0f)
    {
        gSmoothTimer -= gFrameDeltaTime;
        if (gSmoothTimer >= 0.0f)
        {
            // Compute normalized step factor: timer * scale
            stepFactor = gSmoothStepScale * gSmoothTimer;
        }
        else
        {
            // Clamp timer to zero
            gSmoothTimer = 0.0f;
        }

        // Update X component if target differs from current
        if (gSmoothTargetX != gSmoothCurrentX)
        {
            gSmoothCurrentX = gSmoothTargetX - gSmoothStiffnessX * stepFactor;
        }

        // Update Y component if target differs from current
        if (gSmoothTargetY != gSmoothCurrentY)
        {
            gSmoothCurrentY = gSmoothTargetY - gSmoothStiffnessY * stepFactor;
        }

        // Update Z component if target differs from current
        if (gSmoothTargetZ != gSmoothCurrentZ)
        {
            gSmoothCurrentZ = gSmoothTargetZ - gSmoothStiffnessZ * stepFactor;
        }
    }
}