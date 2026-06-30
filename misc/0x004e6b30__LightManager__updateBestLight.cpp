// FUNC_NAME: LightManager::updateBestLight

static float s_threshold; // 0x00e2af44
static float s_bestLightData[4]; // 0x011252a0
static float s_bestLightColor[4]; // 0x01125290

void __fastcall updateBestLight(LightManager* thisLight, const float* inputData)
{
    if (s_threshold <= inputData[3]) {
        s_bestLightData[0] = inputData[0];
        s_bestLightData[1] = inputData[1];
        s_bestLightData[2] = inputData[2];
        s_bestLightData[3] = inputData[3];
        
        // Copy from fields at offsets 0x24 and 0x28
        // The exact implementation is unclear due to decompilation artifacts.
        // It likely copies a 4-float structure from (thisLight+0x24) with some offset
        // and the float at thisLight+0x28.
        s_bestLightColor[0] = *(float*)((char*)thisLight + 0x28);
        // The next three floats are from a pointer at thisLight+0x24, offset 0x10 or 0x13?
        float* source = *(float**)((char*)thisLight + 0x24);
        s_bestLightColor[1] = source[4]; // assumed offset
        s_bestLightColor[2] = source[5];
        s_bestLightColor[3] = source[6];
    }
}