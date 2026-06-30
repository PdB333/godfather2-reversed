// FUNC_NAME: clampVectorLength
void clampVectorLength(float *x, float *y, float blendFactor)
{
    float origX = *x;
    float origY = *y;
    float length = sqrt(origX * origX + origY * origY);
    float maxSpeed = *(float*)0x00d5780c; // +0x00 global maximum speed constant

    float clampedLength;
    if (length > 0.0f)
    {
        if (length > maxSpeed)
            clampedLength = maxSpeed;
        else
            clampedLength = length;
    }
    else
    {
        clampedLength = 0.0f;
    }

    // Blend original length with clamped length using blendFactor
    float finalLength = length * (maxSpeed - blendFactor) + clampedLength * blendFactor;

    // Preserve direction by scaling normalized components
    if (length > 0.0f)
    {
        *x = (origX / length) * finalLength;
        *y = (origY / length) * finalLength;
    }
    else
    {
        *x = 0.0f;
        *y = 0.0f;
    }
}