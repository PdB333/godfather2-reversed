// FUNC_NAME: ColorScaleManager::initColorScales
void __thiscall ColorScaleManager::initColorScales(int this)
{
    uint bucketIdx;
    undefined4 *dst;
    undefined4 *src;
    int relOffset;
    int loopCount;
    undefined4 val;

    for (bucketIdx = 0; bucketIdx < 3; bucketIdx++) {
        if (bucketIdx == 2) {
            val = getColorScaleAllocator();          // +0xbc special bucket
            *(undefined4 *)(this + 0xbc) = val;
        } else {
            val = getColorScaleAllocator();          // +0xb4, +0xb8
            *(undefined4 *)(this + 0xb4 + bucketIdx * 4) = val;
        }

        // Each bucket gets 14 entries at offsets: 0x118, 0x150, 0x188
        dst = (undefined4 *)(this + (bucketIdx + 5) * 0x38);
        // Calculate relative offset to global color scale array "PTR_s_color_scale_010bec4c"
        relOffset = (int)&PTR_s_color_scale_010bec4c - (int)dst;
        loopCount = 14;
        do {
            val = copyColorScale(*(undefined4 *)(this + 0xb4 + bucketIdx * 4),       // source
                                 *(undefined4 *)((int)dst + relOffset));              // from global table
            *dst = val;
            dst = dst + 1;
            loopCount = loopCount - 1;
        } while (loopCount != 0);
    }

    // Second phase: 22 gradient tables, each with 15 entries
    dst = (undefined4 *)(this + 0xc0);          // gradient table pointers start here
    src = (undefined4 *)(this + 0x1c0);         // gradient table data start here
    // param_1 reused as negative offset to global gradient data
    int globalOffset = (int)&PTR_PTR_010beac4 - this;

    for (bucketIdx = 0; bucketIdx < 0x58; bucketIdx += 4) {
        val = getGradientTable(*(undefined4 *)((int)&PTR_PTR_01128330 + bucketIdx));
        *dst = val;                             // store gradient table pointer

        loopCount = 15;
        do {
            val = copyColorScale(*dst, *(undefined4 *)((int)src + globalOffset));
            *src = val;
            src = src + 1;
            loopCount = loopCount - 1;
        } while (loopCount != 0);

        dst = dst + 1;
        globalOffset -= 0x3c;                   // move to next gradient table in global data (15 ints)
    }

    return;
}