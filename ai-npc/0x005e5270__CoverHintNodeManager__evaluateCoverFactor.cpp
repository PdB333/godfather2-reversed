// FUNC_NAME: CoverHintNodeManager::evaluateCoverFactor
// Address: 0x005e5270
// Role: Evaluates the effectiveness of cover at a given position by querying nearby cover nodes,
// computing the closest node, and applying distance-based attenuation to produce a cover factor (0-1).
// Also handles propagation of sound and updates sensor outputs.

#include <cmath>

// Constants (approximate values from data references)
const float kEpsilon = 0.001f;       // DAT_00e44598
const float kOne = 1.0f;             // DAT_00e2b1a4
const float kZero = 0.0f;            // DAT_00e2e50c
const float kInnerFactor = 0.5f;     // DAT_00e39f98 (1 / innerRadius?)
const float kOuterThreshold = 10.0f; // DAT_00e2dd14
const float kFactorA = 0.8f;         // DAT_00e2b04c
const float kFactorB = 0.3f;         // DAT_00e35654
const float kFactorC = 0.2f;         // DAT_00e2b334

// Forward declarations of called functions (assumed external)
extern int __cdecl tmpNodeVectorConstructor(void* element, int size, int count, void (*initFunc)(void*));
extern float __cdecl queryCoverNodes(float* outArray); // FUN_005e45d0
extern int __cdecl getRandomBool(int dummy);           // FUN_005e5980
extern void __cdecl computeSoundPropagation(float* out, float* inPos, void* soundID, float* result); // FUN_005e5c60
extern void* __cdecl getComponentFromID(uint id);      // FUN_005dc670
extern bool __cdecl getComponentFloat(void* component, float* out); // FUN_005dd8a0

class CoverHintNodeManager {
public:
    // Class fields (reconstructed from offsets)
    char flag0;          // +0x00
    char flag1;          // +0x01
    int soundIdOrPtr;    // +0x04 (used as fourth arg to computeSoundPropagation)
    float innerRadius;   // +0x08
    float outerRadius;   // +0x0C
    uint someComponentID; // +0x10 (used with getComponentFromID)
    uint anotherID;      // +0x14 (used with getComponentFloat)
    byte flags;          // +0x18 (bit 2 used)

    // Method: evaluateCoverFactor
    // Input:  pos - world position to evaluate
    // Output: outCoverFactor - cover effectiveness (0..1)
    //         outMinDist - distance to nearest cover node
    //         outRandomValue - if random trigger, else unchanged
    //         outPropagation - sound propagation result
    //         outComponentState - pointer to component state (or 0)
    // Returns: true always
    bool evaluateCoverFactor(const float* pos,
                             float* outMinDist,
                             float* outCoverFactor,
                             float* outRandomValue,
                             float* outPropagation,
                             uint* outComponentState) {
        float coverFactor = 0.0f;
        float minDist = 0.0f;

        // If flag1 is zero, early exit
        if (flag1 == 0) {
            goto exit;
        }

        // Temporary container for cover nodes (up to 4 nodes, each 48 bytes = 12 floats)
        float nodeBuffer[4][12]; // 4 nodes, each 12 floats (position + matrix/padding)
        tmpNodeVectorConstructor(nodeBuffer, sizeof(float[12]), 4, (void(*)(void*))0x005e4280);

        // Query cover nodes near position
        float numNodes = queryCoverNodes((float*)nodeBuffer);
        float posX = pos[0];
        float posY = pos[1];
        float posZ = pos[2];

        float localPos[3] = { posX, posY, posZ };
        float transformed[12]; // up to 4 * 3 components
        float nodeDistances[4];
        float bestDist = kZero;
        int bestIndex = -1;

        if (numNodes != 0.0f) {
            // Transform position into each node's local space
            float* pOut = transformed;
            for (int i = 0; i < (int)numNodes; i++) {
                float* node = (float*)nodeBuffer[i];
                float* rotMatrix = *(float**)(node + 8); // pointer at offset 32 bytes (float index 8)
                if (rotMatrix == nullptr) {
                    pOut[0] = kZero;
                    pOut[1] = kZero;
                    pOut[2] = kZero;
                } else {
                    // Compute relative vector from node position
                    float relX = posX - node[0];
                    float relY = posY - node[1];
                    float relZ = posZ - node[2];
                    // Transform by rotation matrix (3x4 or 3x3+translation)
                    pOut[0] = relX * rotMatrix[0] + relY * rotMatrix[4] + relZ * rotMatrix[8];
                    pOut[1] = relX * rotMatrix[1] + relY * rotMatrix[5] + relZ * rotMatrix[9];
                    pOut[2] = relX * rotMatrix[2] + relY * rotMatrix[6] + relZ * rotMatrix[10];
                    pOut[3] = relX * rotMatrix[3] + relY * rotMatrix[7] + relZ * rotMatrix[11]; // w component?
                }
                pOut += 3;
            }

            // Find node with smallest distance (magnitude of transformed vector)
            bestDist = kZero;
            float minDistSq = kZero; // actually sqrt magnitude
            for (int i = 0; i < (int)numNodes; i++) {
                float x = transformed[i * 3 + 0];
                float y = transformed[i * 3 + 1];
                float z = transformed[i * 3 + 2];
                float dist = sqrtf(x*x + y*y + z*z);
                nodeDistances[i] = dist;
                if (i == 0 || dist < minDistSq) {
                    minDistSq = dist;
                    bestIndex = i;
                    bestDist = dist;
                }
            }
        }

        // If best node has flag bit0 set, compute direct distance to node position
        if (numNodes != 0.0f && (nodeBuffer[bestIndex][0] & 1) != 0) {
            float* nodePos = (float*)nodeBuffer[bestIndex];
            float dx = posX - nodePos[0];
            float dy = posY - nodePos[1];
            float dz = posZ - nodePos[2];
            bestDist = sqrtf(dx*dx + dy*dy + dz*dz);
        }

        // Early exit if distance within threshold
        if (kEpsilon <= bestDist - outerRadius) {
            *outCoverFactor = 0.0f;
            goto exit;
        }

        // Compute cover factor based on distance and inner/outer radii
        if (bestDist < 0.0f) {
            coverFactor = 0.0f;
        } else {
            float range = outerRadius - innerRadius;
            float dist = bestDist - innerRadius;
            coverFactor = kOne;
            if (range > 0.0f && dist > 0.0f) {
                float t = kOne;
                if (kEpsilon < range) {
                    t = kInnerFactor / range;
                }
                float scaledDist = t * dist;
                if (scaledDist <= kOuterThreshold) {
                    if (kFactorA < scaledDist) {
                        coverFactor = kOne - (scaledDist - kFactorA) * kFactorB;
                    }
                } else {
                    coverFactor = kFactorB - (scaledDist - kOuterThreshold) * kFactorC;
                    if (coverFactor < 0.0f) coverFactor = 0.0f;
                }
            }
        }
        *outCoverFactor = coverFactor;

        // Handle random trigger if only one node found (decompiler artifact)
        if (numNodes == 1.4013e-45f) { // likely == 0.0f but decompiler shows denormal
            float randomVal = 0.0f;
            bool randomTrigger = getRandomBool(1) != 0;
            if (randomTrigger) {
                *outRandomValue = randomVal;
            }
        }

        // Sound propagation if flag0 set
        coverFactor = 0.0f;
        if (flag0 != 0) {
            computeSoundPropagation(nodeDistances, pos, (void*)(intptr_t)soundIdOrPtr, outPropagation);
        }
        *outMinDist = bestDist;

    exit:
        // Final adjustments based on component state
        uint compID = someComponentID;
        bool bModified = false;
        float factorA = coverFactor;
        float factorB = kOne;
        if ((flags & 4) == 0) {
            void* component = getComponentFromID(compID);
            if (component != nullptr) {
                if (getComponentFloat((void*)(intptr_t)anotherID, &factorB) && factorB >= 0.0f && factorB <= kOne && factorA >= 0.0f) {
                    bModified = true;
                }
            }
        } else {
            void* component = getComponentFromID(compID);
            if (component != nullptr) {
                bModified = true;
                getComponentFloat(0, &factorB);
                getComponentFloat((void*)(intptr_t)0x012056c0, &factorA);
                // Note: local_118, local_114 are from stack; approximated as factorB and factorA
                factorA = factorB * 0.0f + factorA; // identity with zero? Actually complex
                factorB = factorB * 0.0f + factorB;
            }
        }

        if (bModified) {
            *outCoverFactor = (*outCoverFactor) * factorB;
            if (flag0 == 0) {
                *outPropagation = factorA;
            } else {
                *outPropagation = (*outPropagation) * factorA;
            }
        }

        // Retrieve component state
        uint compID2 = someComponentID;
        *outComponentState = 0;
        void* component = getComponentFromID(compID2);
        if (component != nullptr) {
            *outComponentState = *(uint*)((char*)component + 0x280);
        }

        return true;
    }
};