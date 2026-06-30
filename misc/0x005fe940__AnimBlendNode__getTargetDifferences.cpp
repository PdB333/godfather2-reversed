// FUNC_NAME: AnimBlendNode::getTargetDifferences
// Address: 0x005fe940
// Computes differences between target and current values for three channels.
// First channel clamped non-negative, second and third wrapped as angles.
// Returns 0 if child pointers are null.
// Offsets: +0x94 = leftChild, +0x9c = rightChild,
// +0xc0 = current1, +0xc4 = target1, +0xf4 = current2, +0xfc = target2,
// +0x100 = current3, +0x108 = target3

class AnimBlendNode {
public:
    AnimBlendNode* leftChild;   // +0x94
    AnimBlendNode* rightChild;  // +0x9c
    float current1;             // +0xc0
    float target1;              // +0xc4
    // ... other members assumed between
    float current2;             // +0xf4
    float target2;              // +0xfc
    float current3;             // +0x100
    float target3;              // +0x108
};

// Global constants for angular wrapping
extern float g_angleMin;   // DAT_00e44588
extern float g_angleMax;   // DAT_00e2afac
extern float g_angleWrap;  // DAT_00e2a848

int __thiscall AnimBlendNode::getTargetDifferences(float* outDiff1, float* outDiff2, float* outDiff3) {
    // Ensure both children exist
    if (leftChild == nullptr || rightChild == nullptr) {
        return 0;
    }

    // Channel 1: non-negative difference (e.g., progress)
    float diff1 = target1 - current1;
    if (diff1 < 0.0f) {
        diff1 = 0.0f;
    }
    *outDiff1 = diff1;

    // Channel 2: wrapped angular difference
    float diff2 = target2 - current2;
    if (diff2 > g_angleMax) {
        diff2 -= g_angleWrap;
    } else if (diff2 < g_angleMin) {
        diff2 += g_angleWrap;
    }
    *outDiff2 = diff2;

    // Channel 3: wrapped angular difference (slightly different order)
    float diff3 = target3 - current3;
    if (g_angleMax < diff3) {
        *outDiff3 = diff3 - g_angleWrap;
        return 1;
    }
    if (diff3 < g_angleMin) {
        diff3 += g_angleWrap;
    }
    *outDiff3 = diff3;
    return 1;
}