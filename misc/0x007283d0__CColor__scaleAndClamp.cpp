// FUNC_NAME: CColor::scaleAndClamp
// Address: 0x007283d0
// Multiplies each color component (RGBA) by a scale factor, then clamps each component to [0.0f, kMaxColorValue]
void __thiscall CColor::scaleAndClamp(float* thisPtr, float scale)
{
    // DAT_00d6247c is a constant, likely 1.0f or 255.0f (max color value)
    const float kMaxColorValue = DAT_00d6247c;

    // Multiply each component by scale (thisPtr is the 'this' pointer, points to 4 floats)
    float r = thisPtr[0] * scale;
    float g = thisPtr[1] * scale;
    float b = thisPtr[2] * scale;
    float a = thisPtr[3] * scale;

    // Clamp red: if positive, min with max, else 0
    if (r > 0.0f) {
        r = (r > kMaxColorValue) ? kMaxColorValue : r;
    } else {
        r = 0.0f;
    }
    thisPtr[0] = r;

    // Clamp green
    if (g > 0.0f) {
        g = (g > kMaxColorValue) ? kMaxColorValue : g;
    } else {
        g = 0.0f;
    }
    thisPtr[1] = g;

    // Clamp blue
    if (b > 0.0f) {
        b = (b > kMaxColorValue) ? kMaxColorValue : b;
    } else {
        b = 0.0f;
    }
    thisPtr[2] = b;

    // Clamp alpha
    if (a > 0.0f) {
        a = (a > kMaxColorValue) ? kMaxColorValue : a;
    } else {
        a = 0.0f;
    }
    thisPtr[3] = a;
}