// FUNC_NAME: Scene::computeLightingForSlot
void __fastcall Scene::computeLightingForSlot(float *outColor, int slotIndex, int sceneObj, int *lightArray, float intensity)
{
    float fVar1;
    byte bVar2;
    int iVar3;
    int lightContext;
    float fVar5;
    float fVar6;
    float fVar7;
    int lightSlotPtr;
    float fVar9;
    float fVar11;
    float fVar12;
    __m128 clamped;
    __m128 minBounds;
    __m128 maxBounds;

    // Get the engine's thread-local global pointer (FS segment offset 0x2c)
    // This points to some global "Engine" or "World" object with a pointer at +8
    iVar3 = *(int *)(**(int **)(__readfsdword(0x2c) + 8) + 8);  // Simplified: FS:[0x2c] -> some pointer -> +8

    // Read light contribution factor from the light array (each light slot is 0x50 bytes)
    // lightArray points to the base of the array; slotIndex selects the slot
    fVar9 = *(float *)(*lightArray + slotIndex * 4 + iVar3);  // Access some value at offset slotIndex*4 from light base, plus global offset

    // Get the lighting context from the scene object (sceneObj+4 contains a pointer to it)
    lightContext = *(int *)(sceneObj + 4);

    // Direction / scale factors from lighting context
    fVar11 = *(float *)(lightContext + 0x14);  // +0x14: y component factor
    fVar12 = *(float *)(lightContext + 0x18);  // +0x18: z component factor

    lightSlotPtr = slotIndex * 0x50 + *lightArray;  // Address of the light slot data
    fVar1 = *(float *)(lightSlotPtr + 0x4c + iVar3);  // +0x4c: w component factor? (with global offset)

    // Compute world-space position contribution
    outColor[0] = fVar9 * *(float *)(lightContext + 0x10) + *(float *)(lightContext + 0x40);   // +0x10: x factor, +0x40: base x
    outColor[1] = fVar9 * fVar11 + *(float *)(lightContext + 0x44);   // +0x44: base y
    outColor[2] = fVar9 * fVar12 + *(float *)(lightContext + 0x48);   // +0x48: base z
    outColor[3] = fVar9 * fVar1 + *(float *)(lightContext + 0x4c);    // +0x4c: base w

    // Apply fog factor: fVar9 = fogFactor * originalFVar9 + fogBias
    fVar9 = *(float *)(lightContext + 0x78) * fVar9 + *(float *)(lightContext + 0x7c);
    if (fVar9 < outColor[3]) {
        outColor[3] = fVar9;  // Min with fog?
    }

    // Retrieve light color bytes from the slot (offsets 0x5d,0x5e,0x5f within slot)
    bVar2 = *(byte *)(lightSlotPtr + 0x5f);  // +0x5f: blue? (or order may differ)
    lightContext = *(int *)(sceneObj + 4);   // Reload lighting context (could be different after previous use?)

    // Scale final w by intensity
    outColor[3] = outColor[3] * intensity;

    // Build SIMD color from byte components multiplied by global brightness and current position
    // DAT_00e2dd1c is a global brightness scalar
    // DAT_00e44764 is another global multiplier for the alpha (w) component
    clamped.m128_f32[0] = DAT_00e2dd1c * (float)*(byte *)(lightSlotPtr + 0x5e) * outColor[0];  // Red from slot byte at 0x5e
    clamped.m128_f32[1] = DAT_00e2dd1c * (float)bVar2 * outColor[1];  // Blue? from byte at 0x5f
    clamped.m128_f32[2] = DAT_00e2dd1c * (float)*(byte *)(lightSlotPtr + 0x5d) * outColor[2];  // Green from slot byte at 0x5d
    clamped.m128_f32[3] = DAT_00e2dd1c * DAT_00e44764 * outColor[3];  // Alpha

    // Clamp the color vector against min/max bounds stored in the lighting context
    // +0x20: min bounds, +0x30: max bounds (likely 4 floats each)
    maxBounds = *(__m128 *)(lightContext + 0x30);
    clamped = _mm_min_ps(clamped, maxBounds);
    minBounds = *(__m128 *)(lightContext + 0x20);
    clamped = _mm_max_ps(clamped, minBounds);

    // Apply final global multiplier (DAT_00e4484c) and output
    outColor[0] = clamped.m128_f32[0] * DAT_00e4484c;
    outColor[1] = clamped.m128_f32[1] * DAT_00e4484c;
    outColor[2] = clamped.m128_f32[2] * DAT_00e4484c;
    outColor[3] = clamped.m128_f32[3] * DAT_00e4484c;
    return;
}