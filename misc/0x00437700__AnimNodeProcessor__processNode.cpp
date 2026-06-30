// FUNC_NAME: AnimNodeProcessor::processNode
#include <cstdint>

// Function reconstructing behavior of FUN_00437700
// This function appears to process an animation blend node tree, evaluating types 3 and 4 nodes.
// Structure at param1 (this):
//   +0x08 - end pointer (upper bound of data buffer)
//   +0x0C - current position pointer in buffer of animation nodes
// Node type 3 = animation clip, type 4 = blend weight node (requires global flag)
// Subcalls read floats at indices 1 and 3 (likely weight/time and blend weight)
// The FPU control word is adjusted during float-to-int conversion.

void AnimNodeProcessor::processNode(void* param_1)
{
    int* currentPos = *(int**)((char*)param_1 + 0xC);
    int* endPos     = *(int**)((char*)param_1 + 0x8);

    if (currentPos >= endPos || currentPos == nullptr)
        return;

    // Check first node type (3 or 4)
    if (*currentPos != 3)
    {
        if (*currentPos != 4)
            return;
        // Type 4 requires a global flag (maybe "enableBlend")
        if (!FUN_00636850())
            return;
    }

    // Advance to next node (8 bytes from start)
    int* secondNode = (int*)((char*)currentPos + 8);
    if (secondNode >= endPos || secondNode == nullptr)
        return;

    if (*secondNode != 4 && *secondNode != 3)
        return;

    // Read float at index 1 (e.g., blend weight or time)
    float readFloat1 = (float)FUN_006259b0(param_1, 1);

    // Set rounding mode: truncate toward zero
    uint16_t controlWord = 0x0C00;  // RC=11 (truncate), PC=00 (single precision)
    // Inline assembly equivalent removed; controlWord used in later float cast

    // Advance internal state (e.g., skip/reset node iterator)
    FUN_00625a70(param_1, 2);

    // Optionally read a third node (16 bytes from start) for blend weight
    int* thirdNode = (int*)((char*)currentPos + 0x10);
    float readFloat3 = 0.0f;
    if (thirdNode < endPos && thirdNode != nullptr)
    {
        if (*thirdNode == 3 || (*thirdNode == 4 && FUN_00636850()))
        {
            controlWord = 0x0C01; // Adjust rounding mode for this read
            readFloat3 = (float)FUN_006259b0(param_1, 3);
        }
    }

    // Call global helper functions (likely playback or blending)
    uint32_t globalVar = DAT_012233fc; // Some global context
    FUN_004d3bc0();                     // E.g., start animation apply
    FUN_00458d10(globalVar, controlWord, readFloat3, 0); // Set blend weight

    // Round first float to integer; if non‑zero, call an uninitialized function pointer
    // (decompilation artifact – clear meaning unknown)
    int roundedValue = (int)(readFloat1 + 0.5f); // math.h round approximation
    if (roundedValue != 0)
    {
        // NOTE: local_44 was uninitialized in original decomp. Possibly a callback pointer
        // from a structure member or a vtable call. Skipped for safety.
        // (*local_44)(); // would call undefined behavior
    }

    return;
}