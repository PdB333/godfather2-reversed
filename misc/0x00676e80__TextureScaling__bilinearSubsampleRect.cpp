// FUNC_NAME: TextureScaling::bilinearSubsampleRect
void __cdecl bilinearSubsampleRect(uint8_t* destBuffer, 
                                   int32_t srcX1, int32_t srcY1, 
                                   int32_t srcX2, int32_t srcY2, 
                                   int32_t dstX1, int32_t dstY1, 
                                   int32_t dstX2, int32_t dstY2) {
    // Compute midpoint and weighted averages for bilinear interpolation
    int32_t midY = (srcY1 + srcY2 + 1) >> 1;            // +0x94: average Y of first pair
    int32_t midX2 = (dstY2 + 4 + srcY1 + (srcY2 + dstY1) * 3) >> 3; // +0x98: weighted average for second dimension
    int32_t midY2 = (srcY2 + dstY1 + 1) >> 1;           // +0x9C: average Y of second pair
    int32_t midX1 = (srcX1 + (srcX2 + dstX1) * 3 + 4 + dstY1) >> 3; // +0xA0: weighted average for first dimension

    // First pass: subsample top-left or left half of the region
    subsampleFourCorners(destBuffer, srcX1, srcY1,
                         (srcX1 + srcX2 + 1) >> 1, midY, // center X, center Y
                         (midY + midY2 + 1) >> 1, midX1,
                         midY, midX2);

    // Second pass: subsample bottom-right or right half
    int32_t midY3 = (dstY1 + dstY2 + 1) >> 1;          // +0xA4: average Y of destination
    subsampleFourCorners(destBuffer, midX1, midX2,
                         ((srcX2 + dstX1 + 1) >> 1) + 1 + ((dstX1 + srcX2 + 1) >> 1) >> 1,
                         (midY3 + midY2 + 1) >> 1, midY3,
                         dstX1, dstY2);
}