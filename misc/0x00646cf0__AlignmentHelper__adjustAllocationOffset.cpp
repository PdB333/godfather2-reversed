// FUNC_NAME: AlignmentHelper::adjustAllocationOffset
int __fastcall AlignmentHelper::adjustAllocationOffset(int param_2, int param_3, int param_4, int *param_5)
{
    int alignment = in_EAX;       // Alignment value passed in EAX
    int baseAddr = param_2;       // Current base address
    int size = param_3;           // Size being allocated
    int extraOffset = param_4;    // Additional offset (e.g., from unaff_EDI)
    int *resultPtr = param_5;     // Output pointer for adjusted base

    int rawAddr = baseAddr + alignment + extraOffset;
    int negAlignment = -alignment;
    int alignedAddr = ((rawAddr + 7U & negAlignment) - extraOffset) + -8;
    int blockSize = *(int *)(baseAddr + 4) & 0x7ffffff8; // Block size from header

    if (alignedAddr != baseAddr) {
        if ((uint)(alignedAddr - baseAddr) < 0x10) {
            // If alignment adjustment is small, try different alignment boundary (0x17 = 23 aligns to 8+15)
            alignedAddr = ((rawAddr + 0x17U & negAlignment) - extraOffset) + -8;
        }
        int diff = ((blockSize - alignedAddr) - size) + baseAddr;
        if (diff != 0 && diff < 0x10) {
            return 0; // Not enough space after alignment
        }
    }
    if (alignedAddr != 0) {
        // Compute final aligned base address for output
        *resultPtr = (((blockSize - size) + baseAddr + 8 + extraOffset & negAlignment) - extraOffset) + -8;
    }
    return alignedAddr; // Returns aligned address or 0 on failure
}