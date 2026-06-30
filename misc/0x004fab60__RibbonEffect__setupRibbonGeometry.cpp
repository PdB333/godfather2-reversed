// FUNC_NAME: RibbonEffect::setupRibbonGeometry
void __thiscall RibbonEffect::setupRibbonGeometry(float* startPos1, float* startPos2, float* endPos1, float* endPos2,
                                                  float startWidth, float endWidth, float baseWidth, float widthStep,
                                                  float texCoordStart, float texCoordEnd, bool useAlternateUV)
{
    // Global scaling factors (likely time/speed related)
    const float g_timeScale = DAT_00e2cd54;
    const float g_speedScale = DAT_00e35654;

    // Compute interpolation increments for the two sides of the ribbon
    float incX1 = g_timeScale * (startPos1[0] - endPos1[0]);
    float incY1 = g_timeScale * (startPos1[1] - endPos1[1]);
    float incZ1 = g_timeScale * (startPos1[2] - endPos1[2]);

    float incX2 = g_speedScale * (endPos2[0] - startPos2[0]);
    float incY2 = g_speedScale * (endPos2[1] - startPos2[1]);
    float incZ2 = g_speedScale * (endPos2[2] - startPos2[2]);

    // Call some math function (likely vector normalization or zeroing)
    FUN_00414aa0();
    FUN_00414aa0();

    // Initialize cumulative offsets for interpolation
    float offsetX1 = incX1;
    float offsetY1 = incY1;
    float offsetZ1 = incZ1;
    float offsetX2 = incX2;
    float offsetY2 = incY2;
    float offsetZ2 = incZ2;

    // Pointer to vertex array at this+0x70 (each vertex is 4 floats)
    float* vertexPtr = reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x70);
    int vertexIndex = 2; // Start at index 2 (skip first two vertices? Actually writes 6 vertices total)

    do {
        // Write vertex from startPos2 + cumulative offset (side A)
        vertexPtr[0] = startPos2[0] + offsetX2;
        vertexPtr[1] = startPos2[1] + offsetY2;
        vertexPtr[2] = startPos2[2] + offsetZ2;
        vertexPtr[3] = startPos2[3]; // Preserve original w component
        // Note: vertexPtr[3] is overwritten with original value after setting

        // Advance cumulative offset for side A
        offsetX2 += incX2;
        offsetY2 += incY2;
        offsetZ2 += incZ2;

        if (vertexIndex + 1 > 6) break; // Only write 6 vertices total

        // Write vertex from endPos1 + cumulative offset (side B)
        vertexPtr[4] = endPos1[0] + offsetX1;
        vertexPtr[5] = endPos1[1] + offsetY1;
        vertexPtr[6] = endPos1[2] + offsetZ1;
        vertexPtr[7] = endPos1[3]; // Preserve original w component

        vertexIndex += 2;
        vertexPtr += 8; // Move to next pair of vertices

        // Advance cumulative offset for side B
        offsetX1 += incX1;
        offsetY1 += incY1;
        offsetZ1 += incZ1;

        if (vertexIndex != 6) {
            // Extra advance for side A when not at last pair
            offsetX2 += incX2;
            offsetY2 += incY2;
            offsetZ2 += incZ2;
        }
    } while (vertexIndex < 7);

    // Pointer to some data object at this+0x3c
    int* dataPtr = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x3c);

    // Compute width interpolation factor
    float widthFactor = (endWidth - startWidth) * g_timeScale + startWidth;

    // Set various ribbon attributes (widths, texture coordinates, etc.)
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x130) = dataPtr[0x84/4] * startWidth; // +0x84
    float data80 = *reinterpret_cast<float*>(reinterpret_cast<char*>(dataPtr) + 0x80);
    float data84 = *reinterpret_cast<float*>(reinterpret_cast<char*>(dataPtr) + 0x84);
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x138) = widthFactor;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x134) = data80 * data84 * startWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x13c) = data80 * widthFactor;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x140) = widthFactor;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x144) = data80 * data84 * endWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x148) = data84 * endWidth;

    float currentWidth = *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x168);
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xc0) = baseWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xd0) = baseWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xc4) = currentWidth;
    float scaledWidthStep = widthStep * g_speedScale;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xd4) = currentWidth + dataPtr[0x4c/4];
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xe0) = scaledWidthStep + baseWidth;
    float nextWidth = scaledWidthStep + scaledWidthStep + baseWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xe4) = currentWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xf0) = nextWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xf4) = currentWidth + dataPtr[0x4c/4];
    float nextNextWidth = scaledWidthStep + nextWidth;
    float finalWidth = scaledWidthStep + nextNextWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x100) = nextNextWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x104) = currentWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x110) = finalWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x114) = currentWidth + dataPtr[0x4c/4];
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x120) = finalWidth;
    *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x124) = currentWidth;

    if (useAlternateUV) {
        float scaledTexCoordEnd = texCoordEnd * g_speedScale;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 200) = texCoordStart;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xd8) = texCoordStart;
        float texCoordMid = scaledTexCoordEnd + scaledTexCoordEnd + texCoordStart;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xe8) = scaledTexCoordEnd + texCoordStart;
        float texCoordNext = scaledTexCoordEnd + texCoordMid;
        float texCoordFinal = scaledTexCoordEnd + texCoordNext;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xcc) = 0.0f;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xdc) = DAT_00e2b1a4;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xec) = 0.0f;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xf8) = texCoordMid;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xfc) = DAT_00e2b1a4;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x108) = texCoordNext;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x10c) = 0.0f;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x118) = texCoordFinal;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x11c) = DAT_00e2b1a4;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x128) = texCoordFinal;
        *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 300) = 0.0f;
    }
}