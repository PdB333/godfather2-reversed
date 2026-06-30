// FUNC_NAME: MathUtils::normalizedDirection
void __fastcall MathUtils::normalizedDirection(float *vecFrom, float *vecOut, float *vecTo)
{
    // Compute difference vector from vecFrom to vecTo
    float diffX = vecTo[0] - vecFrom[0];
    float diffY = vecTo[1] - vecFrom[1];
    float diffZ = vecTo[2] - vecFrom[2];

    // Squared distance
    float distSq = diffX * diffX + diffY * diffY + diffZ * diffZ;

    float scale;
    if (distSq <= DAT_00e2cbe0) // Minimum distance squared (dead zone threshold)
    {
        scale = 0.0f;
    }
    else
    {
        // Normalize using inverse square root scaling factor
        scale = DAT_00e2b1a4 / sqrtf(distSq);
    }

    // Store normalized direction (or zero if within dead zone)
    vecOut[0] = diffX * scale;
    vecOut[1] = diffY * scale;
    vecOut[2] = diffZ * scale;
}