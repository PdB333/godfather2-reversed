// FUNC_NAME: computeAlignedTotalSize

// This function computes the total size of a resource or buffer allocation,
// applying alignment rounding to two dimensions (e.g., width/height or count/size)
// and adding a fixed header overhead of 0x48 bytes.
// The input struct layout:
//   +0x00: uint32_t dimA          (value to be aligned)
//   +0x04: uint32_t alignmentA    (alignment for dimA, minimum 4)
//   +0x08: uint32_t multiplierA   (multiplier for aligned dimA)
//   +0x0C: uint32_t dimB          (second value to be aligned)
//   +0x10: uint32_t alignmentB    (alignment for dimB, minimum 4)
//   +0x14: uint32_t multiplierB   (multiplier for aligned dimB)
// Returns: multiplierA * alignedDimA + multiplierB * alignedDimB + 0x48

typedef struct {
    uint32_t dimA;          // +0x00
    uint32_t alignmentA;    // +0x04
    uint32_t multiplierA;   // +0x08
    uint32_t dimB;          // +0x0C
    uint32_t alignmentB;    // +0x10
    uint32_t multiplierB;   // +0x14
} AlignedSizeParams;

int32_t __fastcall computeAlignedTotalSize(AlignedSizeParams *params) {
    uint32_t alignA = params->alignmentA;
    if (alignA < 4) alignA = 4;
    uint32_t alignedDimA = params->dimA;
    uint32_t remainderA = (alignA - 1) & alignedDimA;
    if (remainderA != 0) {
        alignedDimA += alignA - remainderA;
    }

    uint32_t alignB = params->alignmentB;
    if (alignB < 4) alignB = 4;
    uint32_t alignedDimB = params->dimB;
    uint32_t remainderB = (alignB - 1) & alignedDimB;
    if (remainderB != 0) {
        alignedDimB += alignB - remainderB;
    }

    return params->multiplierA * alignedDimA + params->multiplierB * alignedDimB + 0x48;
}