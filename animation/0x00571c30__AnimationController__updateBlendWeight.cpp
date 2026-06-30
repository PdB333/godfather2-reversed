// FUNC_NAME: AnimationController::updateBlendWeight
// Address: 0x00571c30
// Role: Updates animation blend weight based on state and node data

// Globals (from address references)
extern float DAT_00e2b05c;      // blend threshold
extern float DAT_00e44598;      // speed threshold
extern float _DAT_011260b0;     // blend divisor
extern void (*DAT_01205578)();  // callback

// Node data structure (unaff_ESI)
struct AnimBlendNode {
    /* +0x9 */ char srcIndex;
    /* +0xA */ char dstIndex;
    /* +0xC */ int tablePtr;   // pointer to array of AnimTableEntry
};

// Table entry (size 8 bytes)
struct AnimTableEntry {
    float value0;   // at +0x0
    float value1;   // at +0x4
};

class AnimationController {
public:
    /* +0x78 */ float baseBlendValue;
    /* +0xBC */ int enableFlag;
    /* +0xC0 */ float blendWeights[16]; // actually variable size, but char index implies <= 256
    /* +0x110 */ int stateTimer;
    /* +0x114 */ float stateFloat;

    __thiscall void updateBlendWeight(AnimBlendNode* node) {
        // Condition: either timer not negative OR float <= threshold, AND flag != 0
        if ((((stateTimer >= -1) || (stateFloat <= DAT_00e2b05c)) && (enableFlag != 0)) &&
            // and either dstIndex is sentinel (-1) or blend weight is below/equal base
            ((node->dstIndex < 0) ||
             (blendWeights[node->dstIndex] < baseBlendValue) ||
             (blendWeights[node->dstIndex] == baseBlendValue))) {

            // If srcIndex is valid, compute new weight
            if (node->srcIndex >= 0) {
                AnimTableEntry* table = (AnimTableEntry*)node->tablePtr;
                float speedValue = table[node->srcIndex].value1; // offset 4
                if (DAT_00e44598 < speedValue) {
                    blendWeights[node->dstIndex] = speedValue / _DAT_011260b0 + baseBlendValue;
                }
            }

            // Callback if registered
            if (DAT_01205578 != nullptr) {
                DAT_01205578();
            }
        }
    }
};