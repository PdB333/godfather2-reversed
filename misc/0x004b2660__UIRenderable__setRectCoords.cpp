// FUNC_NAME: UIRenderable::setRectCoords

void __thiscall UIRenderable::setRectCoords(float x1, float y1, float x2, float y2, float widthScale, float heightScale)
{
    // Global Z-depth value used for both min and max corners
    extern float g_fDepthZ;  // DAT_00e2b1a4

    float invWidthScale = g_fDepthZ / widthScale;
    float invHeightScale = g_fDepthZ / heightScale;

    // Map input coordinates to screen space using the inverse scales
    float scaledX1 = invWidthScale * x1;
    float scaledY1 = invHeightScale * y1;

    // Check if this object has a valid sub-structure (quad/rect) enabled
    if (*(int*)(this + 0x98) != 0) {
        int rectPtr = *(int*)(this + 0x9c);
        // +0x9c points to a Rect2D structure with two vertices (each 4 floats)
        *(int*)(rectPtr + 0xdc) = 0;  // Clear a dirty flag or similar

        float* vertexMin = (float*)(rectPtr + 0x10);
        if (vertexMin != (float*)0x0) {
            // Set min vertex (x,y,z,w)
            vertexMin[0] = scaledX1;      // +0x10: minX
            vertexMin[1] = scaledY1;      // +0x14: minY
            vertexMin[2] = 0.0f;          // +0x18: minZ (always 0)
            vertexMin[3] = g_fDepthZ;     // +0x1c: minW (depth value)

            // Set max vertex (computed from second pair of input)
            float scaledX2 = invWidthScale * x2 + scaledX1;
            float scaledY2 = invHeightScale * y2 + scaledY1;

            float* vertexMax = (float*)(rectPtr + 0x20);
            vertexMax[0] = scaledX2;      // +0x20: maxX
            vertexMax[1] = scaledY2;      // +0x24: maxY
            vertexMax[2] = 0.0f;          // +0x28: maxZ
            vertexMax[3] = g_fDepthZ;     // +0x2c: maxW
        }
    }
}