// FUN_004bd160: Sphere::approach
void __thiscall Sphere::approach(float* thisSphere, float* targetSphere)
{
    float thisRadius = thisSphere[3]; // thisSphere: x, y, z, radius (indices 0-3)
    float targetRadius = targetSphere[3];

    // If either sphere has zero or negative radius, handle copy-only cases
    if ((thisRadius <= 0.0f) || (targetRadius <= 0.0f))
    {
        // If target has positive radius, copy entire target sphere into this
        if (0.0f < targetRadius)
        {
            thisSphere[0] = targetSphere[0];
            thisSphere[1] = targetSphere[1];
            thisSphere[2] = targetSphere[2];
            thisSphere[3] = targetRadius;
        }
        return;
    }

    // Both radii positive: compute differences and distance squared
    float targetX = targetSphere[0];
    float targetY = targetSphere[1];
    float targetZ = targetSphere[2];

    float dx = targetX - thisSphere[0];
    float dy = targetY - thisSphere[1];
    float dz = targetZ - thisSphere[2];
    float distanceSq = dx*dx + dy*dy + dz*dz;

    float radiusDiff = targetRadius - thisRadius;
    float radiusDiffSq = radiusDiff * radiusDiff;

    // If spheres are not overlapping (distance^2 > radiusDiff^2)
    if (radiusDiffSq < distanceSq)
    {
        float distance = sqrtf(distanceSq); // SQRT function from decompiler
        // Compute desired new radius: blend of both radii plus distance, scaled by global constant (likely 0.5f)
        float newRadius = (targetRadius + thisRadius + distance) * DAT_00e2cd54; // e.g., 0.5f for average

        // Only blend if the distance is above a global threshold (to avoid jitter at very small separations)
        if (DAT_00e44598 < distance) // DAT_00e44598 is a small epsilon threshold
        {
            // Linear interpolation factor along line from this to target
            float t = (newRadius - thisRadius) / distance;
            thisSphere[0] = t * dx + thisSphere[0];
            thisSphere[1] = t * dy + thisSphere[1];
            thisSphere[2] = t * dz + thisSphere[2];
            // Interpolate radius as well
            thisSphere[3] = t * (targetRadius - thisRadius) + thisRadius;
        }
        // Always update radius to the computed newRadius (even if distance was tiny)
        thisSphere[3] = newRadius;
        return;
    }

    // Spheres overlap or are inside one another: copy target if target radius >= this radius
    if (thisRadius <= targetRadius)
    {
        thisSphere[0] = targetX;
        thisSphere[1] = targetY;
        thisSphere[2] = targetZ;
        thisSphere[3] = targetRadius;
        return;
    }
    // Otherwise (this larger than target, overlapping), do nothing
}