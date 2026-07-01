//FUNC_NAME: clampFloatWithOffsetAndScale
// Address: 0x00974a70
// Clamps a float after applying a linear transformation (scale + offset).
// Constants are likely global configuration values.
float clampFloatWithOffsetAndScale(float input)
{
    // Scale and offset: result = scale * input + offset
    float scaled = DAT_00e57588 * input + DAT_00d8f7e8; // +0x00e57588: scale factor, +0x00d8f7e8: offset/min
    float clamped = scaled;

    // Clamp between DAT_00d8f7e8 (min) and DAT_00d8f7ec (max)
    if (scaled <= DAT_00d8f7e8)
    {
        clamped = DAT_00d8f7e8;
    }
    else if (scaled >= DAT_00d8f7ec)
    {
        clamped = DAT_00d8f7ec;
    }

    return clamped;
}