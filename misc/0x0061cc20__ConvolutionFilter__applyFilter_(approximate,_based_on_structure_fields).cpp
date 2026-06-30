// FUNC_NAME: ConvolutionFilter::applyFilter (approximate, based on structure fields)
// Function at 0x0061cc20: Applies a convolution filter (possibly 4-component color) using a resampling ratio.
// Input: this pointer (ESI) to a struct with data pointer, stride, sizes, weight index.
// Parameter: startIndex in EBX (not declared in original but used as offset)
// Calls helper FUN_0061c8f0 (compute kernel/range) and FUN_0061cb30 (write output sample)
// Global constants: DAT_00e2b1a4 (min ratio), DAT_00e2cd54 (min scaled), DAT_00e445ac (extra allocation), DAT_00f0ce48 (weight array), DAT_00e44640 (scaling factor)

struct ConvolutionFilter {
    byte* data;             // +0x00: pointer to source byte data (4 components per element)
    int stride;             // +0x04: bytes between consecutive elements (e.g., row stride)
    short innerCount;       // +0x06: number of inner iterations (e.g., kernel taps per output)
    int weightIndex;        // +0x08: index into global weight array DAT_00f0ce48
    short inputSize;        // +0x0A: numerator for resizing ratio (e.g., input sample count)
    short outputSize;       // +0x1A: denominator for ratio, and outer loop count
};

// Memory manager interface (virtual table at DAT_01205868)
struct MemManagerVTable {
    void* (*allocate)(int size, void* descriptor); // offset 0
    void  (*free)(void* ptr, int unused);          // offset 4
};

// Global min/max and constants:
extern float DAT_00e2b1a4;   // min ratio
extern float DAT_00e2cd54;   // min scaled value
extern float DAT_00e445ac;   // additional size for allocation
extern float DAT_00f0ce48[]; // weight array indexed by weightIndex
extern float DAT_00e44640;   // scaling factor for convolution (square)
extern MemManagerVTable* DAT_01205868; // memory manager

void ConvolutionFilter::applyFilter(int startIndex) {
    float ratio = (float)this->inputSize / (float)this->outputSize;
    if (ratio <= DAT_00e2b1a4) ratio = DAT_00e2b1a4;
    ratio *= DAT_00f0ce48[this->weightIndex];
    if (ratio <= DAT_00e2cd54) ratio = DAT_00e2cd54;

    // Allocate temporary float buffer for convolution weights/results
    int allocSize = (int)(ratio + ratio + DAT_00e445ac);
    // Descriptor for allocation: flags in struct local_3c (2, very small float, 0.0)
    struct AllocDesc {
        int flags;     // =2
        float param1;  // =2.24208e-44 (likely unused)
        float param2;  // =0.0
    } desc = { 2, 2.24208e-44f, 0.0f };
    float* weightBuffer = (float*)DAT_01205868->allocate(allocSize * 4, &desc);

    float invRatio = DAT_00e2b1a4 / ratio;
    // fStack_68 appears uninitialized; possibly a leftover. Condition seems redundant.
    // Assuming it's a bug: use the condition with DAT_00e2cd54 to clamp.
    if (ratio <= DAT_00e2cd54) {
        invRatio = DAT_00e2b1a4;
    }

    int outputIndex = 0;
    if (this->outputSize != 0) {
        do {
            // Compute kernel/range for current output index
            // Parameters: outputIndex, ratio, inputSize, invRatio, weightIndex, output of weight count
            int weightCount; // something like number of weights or output size from helper
            FUN_0061c8f0(outputIndex, ratio, this->inputSize, invRatio, this->weightIndex,
                         &weightBuffer, &weightCount);

            int innerIdx = 0;
            if (this->innerCount != 0) {
                float accR = 0.0f, accG = 0.0f, accB = 0.0f, accA = 0.0f;
                float scale = DAT_00e44640;

                do {
                    // Accumulate weighted contributions from source data
                    float accumR = accR, accumG = accG, accumB = accB, accumA = accA;
                    if (startIndex < weightCount) {
                        byte* srcPtr = this->data + this->stride * startIndex + innerIdx * 4;
                        int remaining = weightCount - startIndex;
                        float* weight = weightBuffer;
                        do {
                            byte r = *srcPtr;
                            byte g = srcPtr[1];
                            byte b = srcPtr[2];
                            byte a = srcPtr[3];

                            float w = *weight * scale * scale;
                            weight++;
                            srcPtr += this->stride;

                            float weightedR = w * (float)r;
                            float weightedG = w * (float)g;
                            float weightedB = w * (float)b;
                            float weightedA = w * (float)a;

                            accumR += weightedR;
                            accumG += weightedG;
                            accumB += weightedB;
                            accumA += weightedA;

                            remaining--;
                        } while (remaining != 0);
                    }
                    // Write the accumulated result (likely to output buffer)
                    FUN_0061cb30();

                    innerIdx++;
                } while (innerIdx < (int)(uint)(short)this->innerCount);
            }
            outputIndex++;
        } while (outputIndex < (int)(uint)(short)this->outputSize);
    }

    // Free temporary buffer
    DAT_01205868->free(weightBuffer, 0);
}