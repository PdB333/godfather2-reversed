// FUNC_NAME: RenderUtils::colorBlendWithMask
// Address: 0x0061cac0
// Blends a destination color (4 floats) with a source byte mask (4 bytes) scaled by a factor and a global multiplier.
// The mask is passed in EAX register (x86 custom calling convention).
// Destination is in ECX (this pointer) as a float[4], factor in EDX (stack param).
void __thiscall RenderUtils::colorBlendWithMask(float* destColor, float blendFactor) {
    // Source byte mask (passed in EAX via custom convention)
    const uint8_t* maskBytes = reinterpret_cast<const uint8_t*>(in_EAX); // in_EAX from decompiled

    uint8_t rByte = maskBytes[0];
    uint8_t gByte = maskBytes[1];
    uint8_t bByte = maskBytes[2];
    uint8_t aByte = maskBytes[3];

    // Global color modifier (likely a per-scene or per-frame brightness/gamma factor, squared here)
    // DAT_00e44640 is a global float constant (e.g., 1.0f for identity)
    float globalMod = DAT_00e44640; // from global data
    float scale = static_cast<float>(rByte) * blendFactor * globalMod * globalMod; // base scale for all channels (uses red byte)

    // Apply additive blend: dest = dest + scale * sourceByte
    destColor[0] = scale * static_cast<float>(rByte) + destColor[0]; // R channel
    destColor[1] = scale * static_cast<float>(gByte) + destColor[1]; // G channel
    destColor[2] = scale * static_cast<float>(bByte) + destColor[2]; // B channel
    destColor[3] = scale * static_cast<float>(aByte) + destColor[3]; // A channel
}