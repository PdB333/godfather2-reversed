// FUNC_NAME: ColorCorrection::applyColorMatrix
void ColorCorrection::applyColorMatrix(float* outColor, float r, float g, float b, float a)
{
    bool bEnabled = *(char*)PTR_DAT_00f17650 == '\0'; // Check if color correction is enabled (global flag)
    
    // Store input color components into the output array (likely a 4-float vector)
    outColor[0] = r;
    outColor[1] = g;
    outColor[2] = b;
    outColor[3] = a;
    
    if (bEnabled) {
        // Apply color matrix multiplication (4x4 matrix stored at _DAT_0119d0b0)
        float fR = outColor[0] * _DAT_0119d0b0;   // +0x00
        float fG = outColor[1] * _DAT_0119d0b4;   // +0x04
        float fB = outColor[2] * _DAT_0119d0b8;   // +0x08
        float fA = outColor[3] * DAT_0119d0bc;    // +0x0C
        
        outColor[0] = fR;
        outColor[1] = fG;
        outColor[2] = fB;
        outColor[3] = fA;
        
        // Add offset vector (stored at _DAT_0119d0c0)
        outColor[0] = fR + DAT_0119d0c0;   // +0x10
        outColor[1] = fG + _DAT_0119d0c4;  // +0x14
        outColor[2] = fB + _DAT_0119d0c8;  // +0x18
        outColor[3] = fA + _DAT_0119d0cc;  // +0x1C
        
        // Clamp to [0, 1] range using SSE minps/maxps
        // _DAT_00e2b2d0 = {0,0,0,0} (min clamp)
        // _DAT_00e2b2e0 = {1,1,1,1} (max clamp)
        outColor[0] = min(outColor[0], 1.0f);
        outColor[1] = min(outColor[1], 1.0f);
        outColor[2] = min(outColor[2], 1.0f);
        outColor[3] = min(outColor[3], 1.0f);
        
        outColor[0] = max(outColor[0], 0.0f);
        outColor[1] = max(outColor[1], 0.0f);
        outColor[2] = max(outColor[2], 0.0f);
        outColor[3] = max(outColor[3], 0.0f);
    }
}