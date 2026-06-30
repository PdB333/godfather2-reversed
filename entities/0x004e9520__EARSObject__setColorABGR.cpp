// FUNC_NAME: EARSObject::setColorABGR
void __thiscall EARSObject::setColorABGR(int this, float r, float g, float b, float a)
{
    // Clamp each component to [0, g_colorClampMax]
    // g_colorClampMax is likely 1.0f (since input is expected 0-1)
    if (r < 0.0f) r = 0.0f;
    else if (r > g_colorClampMax) r = g_colorClampMax;

    if (g < 0.0f) g = 0.0f;
    else if (g > g_colorClampMax) g = g_colorClampMax;

    if (b < 0.0f) b = 0.0f;
    else if (b > g_colorClampMax) b = g_colorClampMax;

    if (a < 0.0f) a = 0.0f;
    else if (a > g_colorClampMax) a = g_colorClampMax;

    // Scale to byte range and pack as ABGR (Alpha, Blue, Green, Red)
    // g_colorScaleToByte is likely 255.0f
    uint8_t rByte = (uint8_t)(r * g_colorScaleToByte);
    uint8_t gByte = (uint8_t)(g * g_colorScaleToByte);
    uint8_t bByte = (uint8_t)(b * g_colorScaleToByte);
    uint8_t aByte = (uint8_t)(a * g_colorScaleToByte);
    uint32_t packed = (aByte << 24) | (bByte << 16) | (gByte << 8) | rByte;

    // Destination: derived from TLS pointer and this object's offset at +0x18
    // Get pointer from thread-local storage (FS:0x2c -> TLS array, index 8)
    uint** tlsArray = *(uint***)(__readfsdword(0x2c));  // TLS array pointer
    uint* enginePtr = (uint*)tlsArray[2];               // Offset 8 (two DWORDs) -> engine global
    // enginePtr[0x98 / 4] is a base pointer, then add this->field18 as offset
    uint* colorBuffer = (uint*)(*(int*)((char*)enginePtr + 0x98) + *(int*)((char*)this + 0x18));
    *colorBuffer = packed;
}