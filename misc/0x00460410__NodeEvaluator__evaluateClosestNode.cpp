// FUNC_NAME: NodeEvaluator::evaluateClosestNode

#include <cmath>

// Forward declarations
struct Vector3;
class ISpatialTransform {
public:
    virtual ~ISpatialTransform() = 0;
    virtual void getWorldMatrix(float* outMatrix) = 0; // vtable+0x1c
    int type;        // +0x0C
    float scale;     // +0x10
};

struct NodeEntry {
    void* nodeObject;   // +0x00 (8 bytes? actually pointer only)
    int nodeId;         // +0x04? but local_118 is at +0x24 of nodeObject, not from entry
};

// The output structure for the closest node result
struct NodeResult {
    Vector3 position;   // +0x00 (x,y,z)
    float distance;     // +0x0C
};

// Constants from the data segment
extern const float FLT_ZERO;              // DAT_00e2b1a4 (likely 0.0f)
extern const float HALF_WEIGHT;           // DAT_00e2cd54 (likely 0.5f)
extern const float NODE_SENTINEL;         // DAT_00e2b05c (likely 0.0f, used as "no result yet")

class NodeEvaluator {
public:
    // Virtual function table offsets:
    // +0xA4: void getReferencePosition(Vector3& outPos);
    // +0x90: void combineWithNodeTransform(const Vector3& nodePos, ... ); // unclear

    // Fields (offsets relative to this):
    // +0x218: void* baseDataPtr;       // pointer to some scene data
    // +0x21C: NodeEntry* nodeEntries;  // array of entries
    // +0x220: int numEntries;          // number of entries

    void* vtable; // first field

    int evaluateClosestNode(NodeResult& outResult) {
        // Zero out result by default
        outResult.position.x = 0.0f;
        outResult.position.y = 0.0f;
        outResult.position.z = 0.0f;
        outResult.distance = 0.0f;

        // Get a scale factor from the base data (at +0x104)
        float baseScale = *(float*)(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x218) + 0x104);

        int count = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x220);
        if (count != 0) {
            NodeEntry* entries = reinterpret_cast<NodeEntry*>(reinterpret_cast<char*>(this) + 0x21C); // Actually it's a pointer, not inline

            for (int i = 0; i < count; ++i) {
                // Each entry is 8 bytes? The code dereferences (entryBase + i*8) as a pointer.
                // But the struct might be simpler: two 4-byte values.
                NodeEntry entry;
                entry.nodeObject = reinterpret_cast<void*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(entries) + i * 8));
                entry.nodeId = *reinterpret_cast<int*>(reinterpret_cast<char*>(entries) + i * 8 + 4);

                int nodePtr = reinterpret_cast<int>(entry.nodeObject);
                ISpatialTransform* transform = *reinterpret_cast<ISpatialTransform**>(nodePtr + 0x20);
                int extraId = *reinterpret_cast<int*>(nodePtr + 0x24); // possibly unused

                if (transform != nullptr) {
                    if (transform->type == 2) {
                        // Simple case: use reference position directly scaled by the node's scale
                        Vector3 refPos;
                        (reinterpret_cast<void(__thiscall*)(NodeEvaluator*, Vector3&)>(vtable + 0xA4))(this, refPos);

                        // Candidate position is the reference position
                        // Candidate distance is scaled by node scale
                        Vector3 candidatePos = refPos;
                        float candidateDist = transform->scale * baseScale;

                        // Check if we should update output
                        if (outResult.distance == NODE_SENTINEL) {
                            outResult.position = candidatePos;
                            outResult.distance = candidateDist;
                        } else {
                            // Delegate to comparison/update function
                            compareAndUpdate(outResult, candidatePos, candidateDist);
                        }
                    } else {
                        // Complex case: get world transform from node, combine with reference, blend
                        // Call function FUN_0045cbe0 (unknown)
                        void (*unknownFunc)() = reinterpret_cast<void(*)()>(0x0045cbe0);
                        unknownFunc();

                        // Build a zero matrix? (DAT_00e2b1a4 used as zeros)
                        float matrix[16] = {};
                        // Set some values? In the code, they set auStack_90[0] = DAT_00e2b1a4, etc.
                        // The stored zero constant is repeatedly used as a 4x4 zero matrix.
                        // Call transform->getWorldMatrix
                        transform->getWorldMatrix(matrix); // Actually (**(code **)(*piVar3 + 0x1c))(&matrix, 0)

                        // Scale the matrix's position components by unaff_ESI (global scale)
                        Vector3 scaledPos;
                        scaledPos.x = matrix[12] * unaff_ESI; // these offsets guessed from fStack_f0 = fStack_cc * unaff_ESI etc.
                        scaledPos.y = matrix[13] * unaff_ESI;
                        scaledPos.z = matrix[14] * unaff_ESI;
                        // And also the direction? There are other components multiplied.

                        // Also get reference position? The call to vtable+0x90 happens later.
                        // The code calls (**(code **)(*unaff_EDI + 0x90))(&uStack_5c, &pfStack_124, 1);
                        // That seems to combine node transform with something.

                        // Perform vector operations: FUN_0045c230 (likely cross product or rotation)
                        // Two calls: one with &fStack_cc, another with &fStack_fc and &fStack_f0.
                        // This likely calculates the final candidate position and distance.

                        // Final candidate position is a weighted average of node and reference positions.
                        // Distance is Euclidean distance between node and reference times half.
                        Vector3 nodePos(matrix[12], matrix[13], matrix[14]);
                        Vector3 refPos;
                        (reinterpret_cast<void(__thiscall*)(NodeEvaluator*, Vector3&)>(vtable + 0xA4))(this, refPos);
                        Vector3 avgPos;
                        avgPos.x = (nodePos.x + refPos.x) * HALF_WEIGHT;
                        avgPos.y = (nodePos.y + refPos.y) * HALF_WEIGHT;
                        avgPos.z = (nodePos.z + refPos.z) * HALF_WEIGHT;
                        float diffX = nodePos.x - refPos.x;
                        float diffY = nodePos.y - refPos.y;
                        float diffZ = nodePos.z - refPos.z;
                        float dist = sqrt(diffX*diffX + diffY*diffY + diffZ*diffZ) * HALF_WEIGHT;

                        Vector3 candidatePos = avgPos;
                        float candidateDist = dist;

                        // Check sentinel
                        if (outResult.distance == NODE_SENTINEL) {
                            outResult.position = candidatePos;
                            outResult.distance = candidateDist;
                        } else {
                            compareAndUpdate(outResult, candidatePos, candidateDist);
                        }
                    }
                }
            }
        }
        return 1; // the return value seems to be always 1 (since uVar4 is set to CONCAT31(uVar5,1) after each iteration)
    }

    // Helper function to handle minimum comparison (FUN_004bd160)
    void compareAndUpdate(NodeResult& best, const Vector3& candidatePos, float candidateDist) {
        // The called function likely compares candidateDist to best.distance
        // and if candidateDist < best.distance, replaces best.
        reinterpret_cast<void(*)(NodeResult*, const Vector3&, float)>(0x004bd160)(&best, candidatePos, candidateDist);
    }

    // Fields
    // +0x000: vtable pointer
    // +0x218: baseDataPtr
    // +0x21C: nodeEntries pointer
    // +0x220: numEntries
};

// Define the global constants
const float FLT_ZERO = reinterpret_cast<const float&>(0x00e2b1a4);
const float HALF_WEIGHT = reinterpret_cast<const float&>(0x00e2cd54);
const float NODE_SENTINEL = reinterpret_cast<const float&>(0x00e2b05c); // likely 0.0f
```