// FUNC_NAME: EARS::AudioCodec::TransformBlock
//
// Reconstructed from 0x00651740.
// Processes audio data in two stages: first splits into 128-byte chunks,
// then applies a butterfly-style step with increasing stride.
// The 'blockCount' is passed in register EDI (unaff_EDI) per the original calling convention.

struct TransformState {
    // +0x14: pointer to a temporary buffer used for swap operations
    int* pBufferSwap;
    // (other fields omitted for brevity)
};

// Helper functions (unknown implementation)
void processChunk(int* start, int* end, int param);
void updateTempBuffer(int* buffer);
void applyButterflyStep(int* data, int* base, int stride);

void EARS::AudioCodec::TransformBlock(
    int* pAudio,
    int* pTemp,
    TransformState* pState,
    int unknownParam,
    int blockCount)          // originally in EDI (unaff_EDI)
{
    int* currentPos = pAudio;
    int numFullGroups   = blockCount >> 5;   // blockCount / 32
    int remainingGroups = blockCount & 0x1F; // blockCount % 32

    // Stage 1: process full 128‑byte groups (32 ints each)
    for (int i = 0; i < numFullGroups; i++)
    {
        processChunk(currentPos, currentPos + 0x20, unknownParam);
        currentPos += 0x20; // advance by 0x80 bytes (32 ints)
    }
    // Process the remaining partial group
    processChunk(currentPos, pTemp, unknownParam);

    // Stage 2: butterfly‑like step (only if more than 32 groups exist)
    int stride = 0x20;
    if (blockCount > 0x20)
    {
        do {
            // Copy the first element of the swap buffer to the second
            pState->pBufferSwap[1] = pState->pBufferSwap[0];

            updateTempBuffer(pTemp);
            applyButterflyStep(&pState->pBufferSwap[1], pAudio, stride * 2);

            stride <<= 2; // multiply by 4
        } while (stride < blockCount);
    }
}