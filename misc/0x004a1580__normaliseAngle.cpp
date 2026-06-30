// FUNC_NAME: normaliseAngle

// Normalizes an angle value to a standard range using piecewise wrapping.
// Used extensively throughout the game's math/rotation code.
// Constants are defined globally and likely represent boundaries and period for angle wrapping (e.g., degrees or radians).

// Global constants (inferred from decompiled code; actual values unknown):
// gUpperBound       - upper bound of the target range (e.g., 180.0f or PI)
// gSecondUpperBound - secondary upper threshold
// gPeriod           - the wrapping period (e.g., 360.0f or 2*PI)
// gReciprocalPeriod - 1.0 / gPeriod (stored as a float for performance)
// gLowerBound       - lower bound of the target range (e.g., -180.0f or -PI)
// gNegativeBound    - negative threshold for adding period

extern float gUpperBound;          // DAT_00e2afac
extern float gSecondUpperBound;    // DAT_00e44608
extern float gPeriod;              // DAT_00e2a848
extern float gReciprocalPeriod;    // _DAT_00e2a858
extern float gLowerBound;          // DAT_00e44588
extern float gNegativeBound;       // _DAT_00e44604

double normaliseAngle(float angle)
{
    if (gUpperBound < angle)
    {
        if (angle < gSecondUpperBound)
        {
            // Simple wrap: subtract one period
            return (double)angle - (double)gPeriod;
        }
        // Wrap down by multiple periods using floor division
        // (angle + gUpperBound) * gReciprocalPeriod  ->  (angle + upper) / period
        int numPeriods = (int)((angle + gUpperBound) * (double)gReciprocalPeriod);
        return (double)angle - (double)numPeriods * (double)gPeriod;
    }

    if (gLowerBound < angle)
    {
        // Already in range, no correction needed
        return (double)angle;
    }

    if (gNegativeBound < angle)
    {
        // Just below range: add one period
        return (double)angle + (double)gPeriod;
    }

    // Far below range: wrap up by multiple periods
    // (angle - gUpperBound) * gReciprocalPeriod  ->  (angle - upper) / period
    int numPeriods = (int)((angle - gUpperBound) * (double)gReciprocalPeriod);
    return (double)angle - (double)numPeriods * (double)gPeriod;
}