// FUNC_NAME: computeThrowTrajectory
// Address: 0x0084f8c0
// Calculates a projectile trajectory direction vector from `from` to `to` given a `speed`.
// Output is a normalized direction scaled by some factor, with a vertical component computed using global constants.
void computeThrowTrajectory(float* from, float* to, float* outDirection, float speed)
{
    float dx = to[0] - from[0];
    float dz = to[2] - from[2];
    // Compute horizontal travel time based on speed
    float time = sqrtf(dx * dx + dz * dz) / speed;

    // Global constants (likely from game physics tuning)
    // _DAT_00d5780c : constant scaling factor for horizontal components
    // DAT_00e4499c : gravity or vertical acceleration factor
    // DAT_00e44564 : base vertical offset
    // _DAT_00d74f54 : additional vertical scaling
    // DAT_00d5c458 : linear vertical term

    float scaleFactor = _DAT_00d5780c / time;
    float resultY = DAT_00e44564 - (time - (scaleFactor * (to[1] - from[1]) * _DAT_00d74f54 + time * _DAT_00d5c458)) * DAT_00e4499c;

    outDirection[0] = scaleFactor * dx;
    outDirection[1] = resultY;
    outDirection[2] = scaleFactor * dz;
    outDirection[3] = 0.0f;
}