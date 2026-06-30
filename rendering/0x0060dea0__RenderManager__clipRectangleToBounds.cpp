// FUNC_NAME: RenderManager::clipRectangleToBounds
void __thiscall RenderManager::clipRectangleToBounds(int left, int right, int top, int bottom)
{
    // Global clipping region data: array of structs with offsets 0x0, 0x4, 0x8, 0xC (left, top, width, height)
    // Indexed by currentClipIndex (DAT_012058b0)
    int clipIndex = DAT_012058b0 * 0x18; // 0x18 = 24 bytes per entry (6 ints? but only 4 used)
    int clipLeft = *(int *)(&DAT_011f3918 + clipIndex);
    int clipTop = *(int *)(&DAT_011f391c + clipIndex);
    int clipRight = *(int *)(&DAT_011f3920 + clipIndex) + clipLeft; // width + left
    int clipBottom = *(int *)(&DAT_011f3924 + clipIndex) + clipTop; // height + top

    // Clip left edge
    if (left < clipLeft) {
        right = right + (left - clipLeft);
        left = clipLeft;
    }
    // Clip right edge
    if (clipRight < left) {
        right = 0;
        left = clipRight;
    }
    // Clip bottom edge
    if (clipBottom < bottom) {
        top = 0;
        bottom = clipBottom;
    }
    // Clip top edge
    if (bottom < clipTop) {
        top = top + (bottom - clipTop);
        bottom = clipTop;
    }
    // Ensure right does not exceed clipRight after adjustments
    if (clipRight < right + left) {
        right = (clipLeft - left) + *(int *)(&DAT_011f3920 + clipIndex);
    }
    // Ensure bottom does not exceed clipBottom after adjustments
    if (clipBottom < bottom + top) {
        top = (clipTop - bottom) + *(int *)(&DAT_011f3924 + clipIndex);
    }
    // Clamp to non-negative
    if (right < 0) {
        right = 0;
    }
    if (top < 0) {
        top = 0;
    }
    // Call function to apply clipped rectangle (likely sets rendering viewport)
    FUN_00609640(right, top);
}