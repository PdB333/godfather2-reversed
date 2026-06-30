// FUNC_NAME: fftTransformBlocks
// Address: 0x00651740
// Role: Core FFT processing step: processes input data in 32-element blocks, then performs radix-4 butterfly passes with increasing step sizes.
// Parameters:
//   dataBuffer  (param_1) - input data array (size fftSize elements)
//   outputBuffer (param_2) - output data array
//   context     (param_3) - transform context structure (contains pointer table at +0x14)
//   unknownFlag (param_4) - flags (forward/inverse, windowing, etc.)
//   fftSize     (implicit from unaff_EDI) - total number of elements (must be multiple of 32)

void fftTransformBlocks(int *dataBuffer, int *outputBuffer, TransformContext *context, int unknownFlag, int fftSize)
{
    int *currentBlock;
    int i;
    int step;

    currentBlock = dataBuffer;
    if (fftSize > 31) {
        int numFullBlocks = fftSize >> 5; // number of 32-element blocks
        i = 0;
        do {
            int *nextBlock = currentBlock + 32; // 32 ints = 128 bytes
            processBlock32(currentBlock, nextBlock, unknownFlag); // FUN_00651690
            numFullBlocks--;
            currentBlock = nextBlock;
        } while (numFullBlocks != 0);
    }
    // Process remaining (or only) block
    processBlock32(currentBlock, outputBuffer, unknownFlag); // FUN_00651690

    // Radix-4 butterfly passes
    step = 32;
    if (fftSize > 32) {
        do {
            // Swap/duplicate first pointer in the table at context+0x14
            int **table = (int **)((char *)context + 0x14);
            table[0][1] = table[0][0]; // copy first entry to second

            // Apply butterfly using output buffer
            fftButterfly(outputBuffer); // FUN_00651ee0

            // Permute/reorder with twiddle factors
            fftPermute(table[0][1], dataBuffer, step * 2); // FUN_00652000

            step *= 4;
        } while (step < fftSize);
    }
}