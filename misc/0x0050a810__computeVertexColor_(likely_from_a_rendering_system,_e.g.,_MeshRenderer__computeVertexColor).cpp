// FUNC_NAME: computeVertexColor (likely from a rendering system, e.g., MeshRenderer::computeVertexColor)
void __fastcall computeVertexColor(float *outColor, int vertexIndex, int materialData, int *meshData, float alphaScale)
{
    // Thread-local storage offset (likely frame index or time)
    int threadLocalOffset = *(int *)(*(int *)(__readfsdword(0x2c)) + 8);
    // Base pointer to vertex array
    int vertexArrayBase = *meshData;
    // Factor from vertex array (float at index vertexIndex)
    float factor = *(float *)(vertexArrayBase + vertexIndex * 4 + threadLocalOffset);

    // Material data pointer (offset +4 from materialData)
    int materialPtr = *(int *)(materialData + 4);
    // Material vectors: base color (0x10,0x14,0x18) and additive color (0x40,0x44,0x48,0x4c)
    float baseR = *(float *)(materialPtr + 0x10);
    float baseG = *(float *)(materialPtr + 0x14);
    float baseB = *(float *)(materialPtr + 0x18);
    float addR = *(float *)(materialPtr + 0x40);
    float addG = *(float *)(materialPtr + 0x44);
    float addB = *(float *)(materialPtr + 0x48);
    float addA = *(float *)(materialPtr + 0x4c);

    // Vertex structure size = 0x50, get pointer to this vertex
    int vertexData = vertexIndex * 0x50 + vertexArrayBase;
    // Alpha factor from vertex data (offset 0x4c)
    float alphaFactor = *(float *)(vertexData + 0x4c + threadLocalOffset);
    // Byte color indices at offsets 0x5d,0x5e,0x5f (R,G,B)
    int byteR = *(byte *)(vertexData + 0x5d + threadLocalOffset);
    int byteG = *(byte *)(vertexData + 0x5e + threadLocalOffset);
    int byteB = *(byte *)(vertexData + 0x5f + threadLocalOffset);

    // Compute interpolated color: factor * base + additive
    outColor[0] = factor * baseR + addR;
    outColor[1] = factor * baseG + addG;
    outColor[2] = factor * baseB + addB;
    outColor[3] = factor * alphaFactor + addA;

    // Additional alpha clamp from material (offset 0x78,0x7c)
    float alphaClamp = *(float *)(materialPtr + 0x78) * factor + *(float *)(materialPtr + 0x7c);
    if (alphaClamp < outColor[3]) {
        outColor[3] = alphaClamp;
    }

    // Apply alpha scale
    outColor[3] *= alphaScale;

    // Scale byte indices to [0,1] and multiply by current color components
    // Then clamp to material bounds (0x20 min, 0x30 max) and scale back
    __m128 byteScaled;
    byteScaled.m128_f32[0] = DAT_00e2dd1c * (float)byteR * outColor[0];
    byteScaled.m128_f32[1] = DAT_00e2dd1c * (float)byteG * outColor[1];
    byteScaled.m128_f32[2] = DAT_00e2dd1c * (float)byteB * outColor[2];
    byteScaled.m128_f32[3] = DAT_00e2dd1c * DAT_00e44764 * outColor[3]; // DAT_00e44764 likely 1.0 or alpha weight

    // Clamp to material bounds (min at +0x20, max at +0x30)
    __m128 minBounds = *(__m128 *)(materialPtr + 0x20);
    __m128 maxBounds = *(__m128 *)(materialPtr + 0x30);
    byteScaled = _mm_max_ps(byteScaled, minBounds);
    byteScaled = _mm_min_ps(byteScaled, maxBounds);

    // Scale back to final color (DAT_00e4484c likely 255.0f)
    outColor[0] = byteScaled.m128_f32[0] * DAT_00e4484c;
    outColor[1] = byteScaled.m128_f32[1] * DAT_00e4484c;
    outColor[2] = byteScaled.m128_f32[2] * DAT_00e4484c;
    outColor[3] = byteScaled.m128_f32[3] * DAT_00e4484c;
}