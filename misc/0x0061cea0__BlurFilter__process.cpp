// FUNC_NAME: BlurFilter::process
void __thiscall BlurFilter::process() {
    // +0x00: m_pData (pointer to source pixel data)
    // +0x04: m_pitch (bytes between passes or rows)
    // +0x06: m_height (number of rows)
    // +0x08: m_channelIndex (index into weight array)
    // +0x0A: m_width (pixel width)
    // +0x1A: m_extraPassCount (number of additional filtering passes)
    //
    // Global constants:
    // DAT_00e2b1a4: kMinRatio
    // DAT_00e2cd54: kMinBlurRadius
    // DAT_00e445ac: kKernelPadding
    // DAT_00e44640: kBlurWeight
    // DAT_00f0ce48: array of channelWeights[4]
    // DAT_01205868: pointer to memory manager vtable (alloc + free)

    float ratio = (float)this->m_width / (float)this->m_height;
    if (ratio <= kMinRatio) ratio = kMinRatio;

    float blurRadius = ratio * channelWeights[this->m_channelIndex];
    if (blurRadius <= kMinBlurRadius) blurRadius = kMinBlurRadius;

    int kernelSize = (int)(blurRadius + blurRadius + kKernelPadding + 0.5f); // ROUND
    float* kernel = (float*)(*(void* (*)(int, int*))DAT_01205868)(kernelSize * 4, &local_3c);
    // local_3c is a dummy parameter (maybe flags or alignment)

    float invBlur = kMinRatio / blurRadius;
    if (invBlur <= kMinBlurRadius) invBlur = kMinRatio;

    for (int row = 0; row < this->m_height; row++) {
        int sampleStart;
        int sampleCount;
        // Compute kernel row data and return valid pixel range for this row
        FUN_0061c8f0(row, blurRadius, this->m_width, invBlur, this->m_channelIndex, &sampleStart, &sampleCount, kernel);

        if (this->m_extraPassCount != 0) {
            float accumR = 0.0f, accumG = 0.0f, accumB = 0.0f, accumA = 0.0f;
            for (int pass = 0; pass < this->m_extraPassCount; pass++) {
                int pixelIdx = sampleStart;
                for (int i = 0; i < sampleCount; i++) {
                    // Source pixel address: base + pass offset + pixel offset
                    byte* src = (byte*)(this->m_pData + this->m_pitch * pass + pixelIdx * 4);
                    float weight = kernel[i];
                    float factor = weight * (float)(*src) * kBlurWeight * kBlurWeight;
                    accumR += factor * (float)(*src);
                    accumG += factor * (float)(*(src + 1));
                    accumB += factor * (float)(*(src + 2));
                    accumA += factor * (float)(*(src + 3));
                    pixelIdx++;
                }
                // After each pass, apply the accumulated result (likely store to output)
                FUN_0061cb30();
            }
        }
    }

    // Free kernel memory
    (*(void (*)(float*, int))(*DAT_01205868 + 4))(kernel, 0);
}