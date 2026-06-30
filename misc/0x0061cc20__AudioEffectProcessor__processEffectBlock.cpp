// FUNC_NAME: AudioEffectProcessor::processEffectBlock
// Function at 0x0061cc20 applies a multi-channel audio effect (likely reverb/convolution)
// Uses per-sample processing with 4-byte interleaved samples (4 channels, 8-bit each)
// Called from a higher-level audio processing loop

#include <cstdint>

struct AudioEffectProcessor {
    // Offsets (packed struct):
    // +0x00: uint8_t* pSampleBuffer;  // interleaved sample data
    // +0x04: int32_t bytesPerFrame;    // stride: bytes to next sample (typically 4)
    // +0x06: uint16_t numChannels;     // number of channels (4)
    // +0x08: int32_t sampleRateIndex;  // index into global sample rate table
    // +0x0A: uint16_t sampleCount;     // samples per block (from offset 0x0A)
    // +0x1A: uint16_t blockCount;      // number of blocks to process (from offset 0x1A)
};

// Function called per-channel to accumulate filtered output
extern void writeAccumulatedOutput(/* parameters */);

// Helper to compute filter coefficients for a block
extern int computeFilterBlock(int blockIndex, float scale, uint16_t sampleCount,
                              float invScale, int rateIndex, int *pOutBlockSize,
                              int *pOutParam, float *outCoeffs);

void AudioEffectProcessor::processEffectBlock(void) {
    uint8_t *pBuffer = *(uint8_t **)((intptr_t)this + 0x00);
    int32_t bytesPerFrame = *(int32_t *)((intptr_t)this + 0x04);
    uint16_t numChannels = *(uint16_t *)((intptr_t)this + 0x06);
    int32_t sampleRateIndex = *(int32_t *)((intptr_t)this + 0x08);
    uint16_t sampleCount = *(uint16_t *)((intptr_t)this + 0x0A);
    uint16_t blockCount = *(uint16_t *)((intptr_t)this + 0x1A);

    // Global constants
    const float kMinScale = *(float *)0x00e2b1a4; // DAT_00e2b1a4
    const float kMinScale2 = *(float *)0x00e2cd54; // DAT_00e2cd54
    const float kConstant = *(float *)0x00e445ac;  // DAT_00e445ac
    const float kVolumeFactor = *(float *)0x00e44640; // DAT_00e44640

    // Compute scaling factor from sample counts
    float scaleFactor = (float)sampleCount / (float)(*(uint16_t *)((intptr_t)this + 0x1A));
    if (scaleFactor <= kMinScale)
        scaleFactor = kMinScale;

    // Multiply by sample-rate-dependent table value
    float *rateTable = (float *)0x00f0ce48;
    scaleFactor *= rateTable[sampleRateIndex];
    if (scaleFactor <= kMinScale2)
        scaleFactor = kMinScale2;

    // Allocate coefficient array: length = 2 * scaleFactor + kConstant rounded
    uint32_t coeffLength = (uint32_t)(scaleFactor * 2.0f + kConstant + 0.5f); // ROUND
    uint32_t allocSize = coeffLength * sizeof(float);
    void *(*allocator)(uint32_t, uint32_t*) = *(void *(**)(void))0x01205868;
    uint32_t allocParams[2] = { 2, 0 }; // dummy
    float *filterCoeffs = (float *)allocator(allocSize, allocParams);

    // Inverse scale for internal use
    float invScale = kMinScale / scaleFactor;
    if (invScale <= kMinScale2)
        invScale = kMinScale;

    // Process each block
    for (uint16_t blockIdx = 0; blockIdx < blockCount; blockIdx++) {
        int blockSize;
        int tempParam; // unused but returned from helper
        computeFilterBlock(blockIdx, scaleFactor, sampleCount, invScale,
                           sampleRateIndex, &blockSize, &tempParam, filterCoeffs);

        // Process each channel within the block
        for (uint16_t chIdx = 0; chIdx < numChannels; chIdx++) {
            float acc0 = 0.0f, acc1 = 0.0f, acc2 = 0.0f, acc3 = 0.0f;
            int sampleIdx = blockIdx; // starting sample index (unaff_EBX)
            if (sampleIdx < blockSize) {
                uint8_t *samplePtr = pBuffer + bytesPerFrame * sampleIdx + chIdx * 4; // read 4 bytes
                float *coeffPtr = filterCoeffs;
                int remaining = blockSize - sampleIdx;
                do {
                    // Read four 8-bit channels from current sample
                    float ch0 = (float)samplePtr[0];
                    float ch1 = (float)samplePtr[1];
                    float ch2 = (float)samplePtr[2];
                    float ch3 = (float)samplePtr[3];

                    float weight = *coeffPtr * kVolumeFactor * kVolumeFactor;
                    float weightedCh0 = weight * ch0;
                    float weightedCh1 = weight * ch1;
                    float weightedCh2 = weight * ch2;
                    float weightedCh3 = weight * ch3;

                    acc0 += weightedCh0 * ch0;
                    acc1 += weightedCh0 * ch1;  // Note: original code uses weighted from first channel? Actually they multiply again by each byte
                    acc2 += weightedCh0 * ch2;
                    acc3 += weightedCh0 * ch3;

                    // Advance to next sample
                    coeffPtr++;
                    samplePtr += bytesPerFrame;
                    remaining--;
                } while (remaining != 0);
            }

            // Write accumulated output for this channel
            writeAccumulatedOutput(/* accumulators and other state */);
        }
    }

    // Free coefficient array
    void (*deallocator)(void*, uint32_t) = *(void (**)(void*, uint32_t))(*(uint32_t *)0x01205868 + 4);
    deallocator(filterCoeffs, 0);
}