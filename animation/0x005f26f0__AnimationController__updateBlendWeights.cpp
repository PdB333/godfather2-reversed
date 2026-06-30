// FUNC_NAME: AnimationController::updateBlendWeights
// Address: 0x005f26f0
// Role: Updates per-node blend weights and applies them to an animation pose.
// Takes a blend context (param_1), a blend state structure (param_2), and a scale factor (param_3).
// For each valid node pointer in the array at param_2+0xc (count = byte at param_2+0x6f),
// computes a weight and calls FUN_005dbc10 to set a blend value, then sets the node's target pose
// from param_1+4 and finalizes with FUN_005f37b0/FUN_005f1400.

#include <cstdint>

uint AnimationController::updateBlendWeights(int param_1, int param_2, float* param_3)
{
    uint result;
    uint eaxInput = in_EAX; // Presumed incoming EAX value (likely return from previous call)

    result = eaxInput & 0xFFFFFF00;

    if (param_1 != 0 && param_2 != 0) {
        FUN_005f2680(); // Likely lock or begin update

        uint8_t nodeCount = *(uint8_t*)(param_2 + 0x6F); // Number of nodes to process
        float speedScale = 0.0f;

        // Check flag at offset +8 of the structure pointed to by param_2+8
        if (*(uint8_t*)(*(int*)(param_2 + 8) + 8) & 2) {
            speedScale = *(float*)(*(int*)(param_2 + 8) + 0x24);
        }

        // Iterate over array of node pointers at param_2 + 0xC
        for (int* iter = (int*)(param_2 + 0xC);
             iter < (int*)(param_2 + 0xC + nodeCount * 4);
             ++iter) {
            int nodePtr = *iter;
            if (nodePtr != 0) {
                // Compute weight from node's byte at +0x1C multiplied by blend factor
                int weightShort = (int)(short)((float)*(uint8_t*)(nodePtr + 0x1C) * *param_3);
                FUN_005dbc10(weightShort, weightShort, (double)speedScale, (double)*param_3,
                             (double)*(float*)(param_2 + 0x54));

                // Copy target pose from param_1+4 into node's +0xC
                *(uint32_t*)(nodePtr + 0xC) = *(uint32_t*)(param_1 + 4);

                uint32_t poseResult = FUN_005f37b0(); // Get intermediate pose data
                FUN_005f1400(poseResult); // Apply final pose
            }
        }

        result = ((uint32_t)(uintptr_t)iter >> 8) | 0x01000000; // Construct return value (success indicator)
    }

    return result;
}