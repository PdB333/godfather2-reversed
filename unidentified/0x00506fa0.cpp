// FUN_NAME: renderBillboardedSprite
void renderBillboardedSprite(float centerX, float centerY, float angleDeg, float scaleX, float scaleY)
{
    // Global scale factor (e.g., world-to-screen scaling)
    float worldScale = *(float*)0x00e2b04c;
    // Screen dimension scaling factors (likely half width/height)
    float screenWidthScale = *(float*)0x01218e44 * worldScale;
    float screenHeightScale = *(float*)0x01218e48 * worldScale;
    // Screen offset (e.g., half screen size for centering)
    float screenOffsetY = *(float*)0x00e2b1a4;  // fVar3
    // UV offset constant
    float uvOffset = *(float*)0x00e2cd54;       // fVar4

    // Compute rotation factors from angle (presumably degrees)
    double angleRad = (double)angleDeg;
    float cosA = (float)(cos(angleRad)) * worldScale;  // fVar7
    float sinA = (float)(sin(angleRad)) * worldScale;  // fVar8

    // Allocate vertex buffer: 6 quads x 10 vertices each? (unknown usage)
    float* vertexBuf = (float*)FUN_0060cd00(6, 10, 0, 1, 0);
    if (vertexBuf != (float*)0x0)
    {
        float* srcVertex = (float*)0x01128124;  // g_spriteVertexOffsets
        float* dstVertex = vertexBuf;
        do
        {
            float srcX = srcVertex[-1];  // previous float, i.e., first of pair
            float srcY = srcVertex[0];   // second of pair

            // Transformed vertex screen position
            dstVertex[0] = ((srcX * cosA * scaleX - srcY * sinA * scaleY) + centerX) * screenWidthScale - screenOffsetY;
            dstVertex[1] = screenOffsetY - ((srcY * cosA * scaleY + srcX * sinA * scaleX) + centerY) * screenHeightScale;
            // UV coordinates (offset by constant)
            dstVertex[2] = srcX + uvOffset;
            dstVertex[3] = srcY + uvOffset;

            srcVertex += 2;  // advance by 2 floats (one pair)
            dstVertex += 4;  // advance to next vertex (4 floats per vertex)
        } while ((int)srcVertex < 0x1128174);  // until end of source array

        // Submit rendered sprite to hardware
        FUN_0060cde0();
    }
    return;
}