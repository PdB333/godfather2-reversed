// FUNC_NAME: WorldRenderer::iterateTilesInArea
void __thiscall WorldRenderer::iterateTilesInArea(WorldRenderer* this, float* pBounds, int param3, int param4)
{
    // Constants (likely from global data)
    const float s_worldOffset = DAT_00e448a4;   // offset for world coordinate system
    const float s_invTileSize = DAT_0110b15c;   // scale factor to convert world units to tile indices
    
    // Camera position from object (offsets +0x0C and +0x10)
    float cameraX = *(float*)((int)this + 0x0C); // +0x0C: camera X position
    float cameraY = *(float*)((int)this + 0x10); // +0x10: camera Y position

    // pBounds is assumed to be a rectangle with 4 floats: [x, y, width, height]
    // Using indexes: 0=x, 1=y (unused here?), 2=width, 3=height
    // First compute tile index range for min corner (left, top?)
    float minX = ((pBounds[0] - pBounds[3]) - s_worldOffset) - cameraX; // (x - height) - offset - camX
    float minY = ((pBounds[2] - pBounds[3]) - s_worldOffset) - cameraY; // (width - height) - offset - camY

    // Clamp to zero
    if (minX < 0.0f) minX = 0.0f;
    if (minY < 0.0f) minY = 0.0f;

    // Convert to tile indices
    int tileStartX = (int)(s_invTileSize * minX);
    int tileStartY = (int)(s_invTileSize * minY);

    // Clamp to maximum tile index (4095)
    if (tileStartX > 0xFFF) tileStartX = 0xFFF;
    if (tileStartY > 0xFFF) tileStartY = 0xFFF;

    // Compute tile index range for max corner (right, bottom?)
    float maxX = ((pBounds[3] + pBounds[0] + s_worldOffset) - cameraX); // (height + x + offset) - camX
    float maxY = ((pBounds[3] + pBounds[2] + s_worldOffset) - cameraY); // (height + width + offset) - camY

    if (maxX < 0.0f) maxX = 0.0f;
    if (maxY < 0.0f) maxY = 0.0f;

    int tileEndX = (int)(s_invTileSize * maxX);
    int tileEndY = (int)(s_invTileSize * maxY);

    if (tileEndX > 0xFFF) tileEndX = 0xFFF;
    if (tileEndY > 0xFFF) tileEndY = 0xFFF;

    // Iterate over tile rows (Y)
    for (int y = tileStartY; y <= tileEndY; y++)
    {
        // Iterate over tile columns (X)
        for (int x = tileStartX; x <= tileEndX; x++)
        {
            // Call per-tile processing function (FUN_00416260)
            FUN_00416260(this, pBounds, param3, param4);
        }
    }
}