// FUNC_NAME: ColorArray::setColor
void __thiscall ColorArray::setColor(int thisPtr, float r, float g, float b, float a)
{
    // Global max color value (likely 1.0f or 255.0f)
    extern float s_maxColorValue;
    // Scale factor to convert float to byte (e.g., 255.0f)
    extern float s_colorScale;

    // Clamp each component to [0.0, s_maxColorValue]
    if (r < 0.0f) r = 0.0f;
    else if (r > s_maxColorValue) r = s_maxColorValue;
    if (g < 0.0f) g = 0.0f;
    else if (g > s_maxColorValue) g = s_maxColorValue;
    if (b < 0.0f) b = 0.0f;
    else if (b > s_maxColorValue) b = s_maxColorValue;
    if (a < 0.0f) a = 0.0f;
    else if (a > s_maxColorValue) a = s_maxColorValue;

    // Scale to byte and pack as RGBA
    uint packedColor = ((uint)(uint8)(r * s_colorScale)) |
                       ((uint)(uint8)(g * s_colorScale) << 8) |
                       ((uint)(uint8)(b * s_colorScale) << 16) |
                       ((uint)(uint8)(a * s_colorScale) << 24);

    // Access global render context via FS:0x2c (thread-local storage)
    // The context has a color buffer at offset 0x98, and the index is stored at this+0x18
    uint* colorBuffer = *(uint**)(*(int*)(*(int*)(__readfsdword(0x2c)) + 8) + 0x98);
    int colorIndex = *(int*)(thisPtr + 0x18);
    colorBuffer[colorIndex] = packedColor;
}