// FUNC_NAME: Graphics::unpackVertexColors
// Function at 0x005b2a70: Unpacks two packed 32-bit colors (ARGB and RGBA) into 8 floats scaled by global factors.
// Input: pointer to two consecutive uint32 colors (first ARGB, second RGBA)
// Output: pointer to 8 floats (first 4 from ARGB, next 4 from RGBA)
// Global scale factors at 0x00e2bcd0-0x00e2bcdc (likely 1/255.0f per channel)

void __fastcall unpackVertexColors(const uint* packedColors, float* outFloats)
{
    // Extract first packed color (ARGB format)
    uint color1 = packedColors[0];
    uint color2 = packedColors[1];

    // Unpack ARGB: high byte = Alpha, third byte = Red, second byte = Green, low byte = Blue
    float a1 = (float)(color1 >> 24);          // Alpha
    float r1 = (float)(*(byte*)((int)packedColors + 2)); // Red (third byte)
    float g1 = (float)(*(byte*)((int)packedColors + 1)); // Green (second byte)
    float b1 = (float)(color1 & 0xFF);         // Blue

    // Apply per-channel scale factors
    outFloats[0] = a1 * g_scaleFactors[0];
    outFloats[1] = r1 * g_scaleFactors[1];
    outFloats[2] = g1 * g_scaleFactors[2];
    outFloats[3] = b1 * g_scaleFactors[3];

    // Second packed color (RGBA format)
    if (color2 == 0) {
        // If zero, set all to zero
        outFloats[4] = 0.0f;
        outFloats[5] = 0.0f;
        outFloats[6] = 0.0f;
        outFloats[7] = 0.0f;
        return;
    }

    // Unpack RGBA: high byte = Red, next = Green, next = Blue, low = Alpha
    float r2 = (float)(color2 >> 24);
    float g2 = (float)((color2 >> 16) & 0xFF);
    float b2 = (float)((color2 >> 8) & 0xFF);
    float a2 = (float)(color2 & 0xFF);

    // Apply same scale factors per output index
    outFloats[4] = r2 * g_scaleFactors[0];
    outFloats[5] = g2 * g_scaleFactors[1];
    outFloats[6] = b2 * g_scaleFactors[2];
    outFloats[7] = a2 * g_scaleFactors[3];
}