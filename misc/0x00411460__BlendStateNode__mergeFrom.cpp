// FUNC_NAME: BlendStateNode::mergeFrom
// Function at 0x00411460 merges a source BlendStateNode into this node.
// Used for priority-based blending: floats compared after mask, bytes/shorted filled if zero.
// Class layout (size ~0x41+):
// +0x00: float weight0 (masked by gFloatPriorityMask)
// +0x04: float weight1
// +0x08: float weight2
// +0x0C: float weight3
// +0x10: uint16 flags0
// +0x12: uint16 flags1
// +0x14: uint16 flags2
// +0x16: uint8 boneJointIndices[16]  // first block
// +0x26: uint8 boneJointWeights[16] // second block
// +0x36: uint16 boneCount0
// +0x38: uint16 boneCount1
// +0x3A: uint16 boneCount2
// +0x3C: uint16 boneCount3
// +0x3F: uint8 rootJointIndex
// +0x40: uint8 rootJointWeight

#include <cstdint>

// Global mask for float priority comparison (extracted from DAT_00e44680)
extern const uint32_t gFloatPriorityMask;

class BlendStateNode {
public:
    float weight0;
    float weight1;
    float weight2;
    float weight3;
    uint16_t flags0;
    uint16_t flags1;
    uint16_t flags2;
    uint8_t boneJointIndices[16];
    uint8_t boneJointWeights[16];
    uint16_t boneCount0;
    uint16_t boneCount1;
    uint16_t boneCount2;
    uint16_t boneCount3;
    uint8_t rootJointIndex;
    uint8_t rootJointWeight;

    // Merge source node into this one using priority rules
    void mergeFrom(const BlendStateNode* source) {
        // Compare masked float weights - take the larger (source overrides if greater)
        if (std::bit_cast<float>(reinterpret_cast<const uint32_t&>(weight0) & gFloatPriorityMask) < 
            std::bit_cast<float>(reinterpret_cast<const uint32_t&>(source->weight0) & gFloatPriorityMask)) {
            weight0 = source->weight0;
        }
        if (std::bit_cast<float>(reinterpret_cast<const uint32_t&>(weight1) & gFloatPriorityMask) < 
            std::bit_cast<float>(reinterpret_cast<const uint32_t&>(source->weight1) & gFloatPriorityMask)) {
            weight1 = source->weight1;
        }
        if (std::bit_cast<float>(reinterpret_cast<const uint32_t&>(weight2) & gFloatPriorityMask) < 
            std::bit_cast<float>(reinterpret_cast<const uint32_t&>(source->weight2) & gFloatPriorityMask)) {
            weight2 = source->weight2;
        }
        if (std::bit_cast<float>(reinterpret_cast<const uint32_t&>(weight3) & gFloatPriorityMask) < 
            std::bit_cast<float>(reinterpret_cast<const uint32_t&>(source->weight3) & gFloatPriorityMask)) {
            weight3 = source->weight3;
        }

        // OR combination for flags
        flags0 |= source->flags0;
        flags1 |= source->flags1;
        flags2 |= source->flags2;

        // Fill zero bone indices and weights from source
        for (int i = 0; i < 16; ++i) {
            if (boneJointIndices[i] == 0) {
                boneJointIndices[i] = source->boneJointIndices[i];
            }
            if (boneJointWeights[i] == 0) {
                boneJointWeights[i] = source->boneJointWeights[i];
            }
        }

        // Fill zero bone counts
        if (boneCount0 == 0) {
            boneCount0 = source->boneCount0;
        }
        if (boneCount1 == 0) {
            boneCount1 = source->boneCount1;
        }
        if (boneCount2 == 0) {
            boneCount2 = source->boneCount2;
        }
        if (boneCount3 == 0) {
            boneCount3 = source->boneCount3;
        }

        // Fill zero root joint
        if (rootJointIndex == 0) {
            rootJointIndex = source->rootJointIndex;
        }
        if (rootJointWeight == 0) {
            rootJointWeight = source->rootJointWeight;
        }
    }
};