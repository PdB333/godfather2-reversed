// FUNC_NAME: ColorToneMapAndClamp
// Address: 0x0061cb30
// This function converts a float4 HDR color to a byte4 (0-255) color with clamping and tone mapping.
// Input: float4 color via EAX (inColor), output: 4-byte buffer (outColor) via ECX (fastcall).
// Uses global constants: exposure (DAT_00e44584), whitePoint (DAT_00e44724), bloomFactor (DAT_00e2b1a4), flag (DAT_00e44680, _DAT_00e2e084).

void __fastcall ColorToneMapAndClamp(uint8_t* outColor, float* inColor)
{
    // Constants from global data
    const float whitePoint = *(float*)0x00e44724;       // +0x00e44724
    const float exposure = *(float*)0x00e44584;         // +0x00e44584
    const float bloomFactor = *(float*)0x00e2b1a4;      // +0x00e2b1a4
    const uint32_t flagMask = *(uint32_t*)0x00e44680;   // +0x00e44680 (bitwise mask)
    const float threshold = *(float*)0x00e2e084;        // +0x00e2e084 (internal threshold)

    // Input value from XMM2 (passed as float, but used as integer for the flag)
    float inputFlag = *(float*)&inputFlag; // Actually from XMM2 register, we assume passed as second argument via XMM2? 
    // For reconstruction, we treat it as a local derived from a global? The decompiled code uses in_XMM2_Da which is from a register.
    // Since the callers likely set this via XMM2, we'll leave it as a variable that is set before the function? Not clean.
    // Better to assume this is a second float parameter (like a bloom factor or tone mapping slider). We'll add a parameter.
    // But the original has no explicit parameter for it. We'll define it as a stack variable from a register.
    // Given complexity, we'll keep the original logic.

    // Determine tone mapping factor
    float toneFactor;
    if (*(float*)&((uint32_t)inputFlag & flagMask) <= threshold) {
        toneFactor = bloomFactor;
    } else {
        toneFactor = inputFlag; // Actually the original uses in_XMM2_Da when condition false, but then it's overwritten?
    }

    // Scale input by toneFactor
    float scale = (bloomFactor / toneFactor) * exposure;
    // Scale each component
    float x = inColor[0] * scale;
    float y = inColor[1] * scale;
    float z = inColor[2] * scale;
    float w = inColor[3] * scale;

    // Apply second scale (overwrites x) - likely a second pass or result of previous calculation?
    x = inputFlag * exposure; // This seems to be the final x? but it ignores scaling? Possibly a bug.

    // Add white point offset
    x += whitePoint;
    y += whitePoint;
    z += whitePoint;
    w += whitePoint;

    // Clamp to [0, exposure] (since exposure is used as max)
    x = (x < exposure) ? x : exposure;
    y = (y < exposure) ? y : exposure;
    z = (z < exposure) ? z : exposure;
    w = (w < exposure) ? w : exposure;

    // Clamp to >= 0
    x = (x > 0.0f) ? x : 0.0f;
    y = (y > 0.0f) ? y : 0.0f;
    z = (z > 0.0f) ? z : 0.0f;
    w = (w > 0.0f) ? w : 0.0f;

    // Convert to byte (0-255)
    outColor[0] = (uint8_t)(int)x;
    outColor[1] = (uint8_t)(int)y;
    outColor[2] = (uint8_t)(int)z;
    outColor[3] = (uint8_t)(int)w;
}