// FUNC_NAME: Sound3D::updateOutput
void __thiscall Sound3D::updateOutput(int this, int listener, uint param3, uint param4)
{
    // Get pointer to the output structure from this+4
    SoundOutput* output = *(SoundOutput**)(this + 4);
    // Get engine global pointer from TLS (fs:0x2c)
    Engine* engine = **(Engine***)(__readfsdword(0x2c));
    // Store a value from the listener's sound parameters into the output
    output->field_1F4 = *(int*)(*(int*)(engine + 8) + 0x94 + *(int*)(listener + 0x18));
    
    // If this output is the currently active sound output (global pointer), update something
    if (gActiveSoundOutput == output && output->field_1F0 != 0) {
        FUN_006063b0(); // Likely updates some global state, e.g., reverb or DSP
    }
    
    // Compute sound position in a buffer (140 bytes, likely a 4x4 matrix or multiple vectors)
    char buffer[140];
    FUN_0056c640(*(int*)(engine + 8) + *(int*)(listener + 0x18), buffer);
    
    // Read two floats from the same base: offset 0x6c and 0x70
    float f1 = *(float*)(*(int*)(engine + 8) + *(int*)(listener + 0x18) + 0x6c);
    float f2 = *(float*)(*(int*)(engine + 8) + 0x70 + *(int*)(listener + 0x18));
    
    // Process these values through trigonometric functions (likely sin/cos of the same angle)
    double d1 = (double)f1;
    FUN_00b99e20(); // Possibly sin(d1) or cos(d1) using x87 stack
    double d2 = (double)f1;
    FUN_00b99fcb(); // The other trig function
    // After these calls, d1 and d2 might hold results? The decompiler doesn't capture side effects.
    // Assuming d1 and d2 remain unchanged? Actually the ratio used later suggests they might be sin and cos.
    // We'll keep the original d1 and d2 for the ratio, but note the functions might modify FPU stack.
    
    // Determine speaker indices based on a condition (left/right or speaker assignment)
    uint speakerIndex = (uint)(*(int*)(engine + 0x34) != 0);
    float panA, panB;
    if (gSpeakerConfig[speakerIndex] == -1) {
        panA = 0.0f;
        panB = gPanSpread; // DAT_00e2b1a4
    } else {
        panA = (float)gSpeakerPositions[speakerIndex * 3];     // DAT_011f6bb8
        panB = (float)gSpeakerPositions[speakerIndex * 3 + 1]; // DAT_011f6bbc
    }
    
    // Compute spatial factor (pan/volume modulation)
    float spatialFactor = (panB * f2 - panA) * (gPanSpread / (f2 - gPanSpread));
    
    // Compute a volume or distance factor
    float volumeFactor = gMaxVolume - (float)d1 / (float)d2;
    
    // Normalize or adjust vectors (two calls)
    FUN_00417560(); // Possibly NormalizeVector?
    FUN_00417560();
    
    // Fill the output spatial parameters (from offset 0x200 to 0x23c)
    output->spatialParams.channelVolume = volumeFactor;  // +0x200
    output->spatialParams.zero1 = 0;                      // +0x204
    output->spatialParams.zero2 = 0;                      // +0x208
    output->spatialParams.zero3 = 0;                      // +0x20c
    output->spatialParams.zero4 = 0;                      // +0x210
    output->spatialParams.ratio = (float)d1 / (float)d2;  // +0x214
    output->spatialParams.zero5 = 0;                      // +0x218
    output->spatialParams.zero6 = 0;                      // +0x21c
    output->spatialParams.zero7 = 0;                      // +0x220
    output->spatialParams.zero8 = 0;                      // +0x224
    output->spatialParams.spatialFactor = spatialFactor;   // +0x228
    output->spatialParams.panSpread = gPanSpread;          // +0x22c
    output->spatialParams.zero9 = 0;                      // +0x230
    output->spatialParams.zero10 = 0;                     // +0x234
    output->spatialParams.panOffset = panA - spatialFactor; // +0x238
    output->spatialParams.zero11 = 0;                     // +0x23c
    
    // If this is the active sound output, apply the computed parameters to the audio system
    if (gActiveSoundOutput == output) {
        FUN_0060b020(*(uint*)(output + 0x14), *(uint*)(output + 0x1F8), (int)&output->spatialParams);
    }
    
    // Continue processing for this listener (possibly next stage)
    FUN_00419ce0(listener, param3, param4);
}
```