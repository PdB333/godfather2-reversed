// FUNC_NAME: ColorUtils::float3ClampToPackedRGB
// Address: 0x00522b00
// Converts a 3-component float color (0-1) to packed 24-bit RGB (0x00RRGGBB format)
uint ColorUtils::float3ClampToPackedRGB(const float* color) // pointer passed in EAX
{
    // Clamp each component to [0.0, 1.0] using min/max SSE constants
    float r = color[0];
    float g = color[1];
    float b = color[2];

    // _DAT_00e38320 = 1.0f (upper clamp), _DAT_00e38310 = 0.0f (lower clamp)
    r = fmaxf(0.0f, fminf(1.0f, r));
    g = fmaxf(0.0f, fminf(1.0f, g));
    b = fmaxf(0.0f, fminf(1.0f, b));

    // Scale to 0-255 and round to nearest integer
    // _DAT_00e38330 = 255.0f; _DAT_00e38334, _DAT_00e38338 = 255.0f (decompiler duplicated)
    int ri = (int)(r * 255.0f + 0.5f); // round (original uses direct truncation? Actually ROUND is round-to-nearest)
    int gi = (int)(g * 255.0f + 0.5f);
    int bi = (int)(b * 255.0f + 0.5f);

    // Pack as uint: 0x00RRGGBB (big-endian in memory? Actually low byte is red, then green, then blue)
    return (uint)(bi << 16) | (uint)(gi << 8) | (uint)(ri);
}