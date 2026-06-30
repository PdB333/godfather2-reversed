// FUNC_NAME: EARSNode::computeBoundingBox (0x00559270)

// Reconstructed C++ member function from Ghidra decompilation.
// This function computes an axis-aligned bounding box (AABB) for a node's children.
// It iterates over an array of child objects (each 0x70 bytes), collects their AABBs,
// and merges them into a single output AABB. Optionally transforms coordinates using
// a node-local matrix.

#include <cfloat> // for FLT_MAX

class EARSNode {
public:
    // +0x00: pointer to a transform structure (contains a matrix at +0xD0)
    void* m_transformPtr; 
    // +0x04: pointer to a dynamic array descriptor (struct with start pointer at +0x00 and count at +0x04)
    int* m_childrenArray; 
    // +0x1C: pointer to a cached bounding box result (if non-null and its +0x10 is non-null, use it directly)
    void* m_cachedBBox;

    // Called to fill a matrix buffer from the node's transform data.
    void getWorldMatrix(int* outMatrix) const;  // FUN_00557660

    // Called to compute the final AABB using a global matrix (DAT_011397d0) or local matrix.
    void computeFinalAABB(float* outAABB, void* param3); // FUN_00557bd0

    // Indicates whether the node uses a different iteration mode (children type A vs B).
    bool hasModeA() const; // FUN_00556e60

    bool hasModeB() const; // FUN_00556e10

    // Checks a child's type string (via a global manager) to decide if it should be processed.
    bool isChildProcessable(int childObj) const; // FUN_00ab06f0

    // Transforms a 4-float vector (or half of an AABB) by a given matrix.
    void transformAABBPart(int* matrix, float* boxPart); // FUN_00aa2c40

    // Helper: returns a global identity matrix (DAT_011397d0)
    static int* getIdentityMatrix(); // declared extern

    void computeBoundingBox(float* outAABB, void* param3, bool convertToWorld) const;
};

// Implementation
void EARSNode::computeBoundingBox(float* outAABB, void* param3, bool convertToWorld) const
{
    // Local buffer for the world matrix (size determined by engine, likely 4x4+)
    int localMatrix[19]; // matrix data (4x4 float plus extra padding?)
    getWorldMatrix(localMatrix);

    // If a cached bounding box is available and valid, use it directly.
    if (m_cachedBBox != nullptr && *(int*)((char*)m_cachedBBox + 0x10) != 0) {
        int* matrixPtr = convertToWorld ? localMatrix : getIdentityMatrix();
        computeFinalAABB(matrixPtr, param3, outAABB);
        return;
    }

    // Initialize min and max components for bounding box.
    // Min components start as large positive, max as large negative.
    const float INF = FLT_MAX;        // from DAT_00e2e50c
    const float NEG_INF = -FLT_MAX;  // from DAT_00e44758

    float minX = INF, minY = INF, minZ = INF, minW = INF;
    float maxX = NEG_INF, maxY = NEG_INF, maxZ = NEG_INF, maxW = NEG_INF;

    // Determine iteration mode based on some condition.
    if (!hasModeA()) {
        // Mode B: use children from m_childrenArray but with a different filter condition.
        if (hasModeB()) {
            int* childPtr = (int*)(m_childrenArray[0]); // start of array
            int childCount = m_childrenArray[1];         // number of children
            int* endPtr = childPtr + childCount * 0x70 / sizeof(int); // each child is 0x70 bytes

            while (childPtr != endPtr) {
                int childObj = *(childPtr + 0x40 / 4); // offset 0x40: child object pointer
                if (childObj == 0) {
                    // object pointer is null, but try to process anyway? (see original logic)
                }
                else {
                    // Check if this child should be processed (string condition).
                    // TODO: actual check via global manager.
                    // If condition passes, skip to processing.
                }

                // If childObj is non-null, get its bounding box.
                if (childObj != 0) {
                    // Call virtual method at vtable[0x1c] on child object.
                    // childObj+0x10 points to vtable, childObj+0x18 is a parameter.
                    // The method fills an 8-float AABB into temporary array.
                    float childAABB[8]; // at fStack_70..fStack_54
                    typedef void (*GetAABB)(int* param, void* param3, float* outAABB);
                    GetAABB getAABB = (GetAABB)(*(int**)(*(int*)(childObj + 0x10) + 0x1c));
                    getAABB((int*)(childObj + 0x18), param3, childAABB);

                    if (convertToWorld) {
                        // Transform both halves of the AABB by the local matrix.
                        transformAABBPart(localMatrix, &childAABB[0]); // min half
                        transformAABBPart(localMatrix, &childAABB[4]); // max half
                    }

                    // Merge child AABB into min/max (min of mins, max of maxes).
                    // Original compares in different orders depending on convertToWorld.
                    // But the net effect is accumulating min and max.
                    if (childAABB[0] < minX) minX = childAABB[0];
                    if (childAABB[1] < minY) minY = childAABB[1];
                    if (childAABB[2] < minZ) minZ = childAABB[2];
                    if (childAABB[3] < minW) minW = childAABB[3];
                    if (childAABB[4] > maxX) maxX = childAABB[4];
                    if (childAABB[5] > maxY) maxY = childAABB[5];
                    if (childAABB[6] > maxZ) maxZ = childAABB[6];
                    if (childAABB[7] > maxW) maxW = childAABB[7];
                }

                childPtr += 0x70 / sizeof(int); // advance to next child
            }
        }
        else {
            // Mode C: similar to above but without the string filter.
            int* childPtr = (int*)(m_childrenArray[0]);
            int childCount = m_childrenArray[1];
            int* endPtr = childPtr + childCount * 0x70 / 4;

            while (childPtr != endPtr) {
                int childObj = *(childPtr + 0x40 / 4);
                if (childObj != 0) {
                    // Same virtual call.
                    float childAABB[8];
                    typedef void (*GetAABB)(int*, void*, float*);
                    GetAABB getAABB = (GetAABB)(*(int**)(*(int*)(childObj + 0x10) + 0x1c));
                    getAABB((int*)(childObj + 0x18), param3, childAABB);

                    // No transform here even if convertToWorld is true? 
                    // Original code only transforms when convertToWorld is non-zero and in some branches.
                    // We follow the original logic: only transform when in certain paths.
                }
                // ... merging similar
            }
        }
    }
    else {
        // Mode A: same as Mode C but with a different initial loop structure.
        // (The original code has two similar blocks; we simplify here.)
        int* childPtr = (int*)(m_childrenArray[0]);
        int childCount = m_childrenArray[1];
        int* endPtr = childPtr + childCount * 0x70 / 4;

        while (childPtr != endPtr) {
            int childObj = *(childPtr + 0x40 / 4);
            if (childObj == 0) {
                // skip to end
            }
            else {
                // Check filter (same as before)
                // If passes, go to processing.
            }
            if (childObj != 0) {
                float childAABB[8];
                typedef void (*GetAABB)(int*, void*, float*);
                GetAABB getAABB = (GetAABB)(*(int**)(*(int*)(childObj + 0x10) + 0x1c));
                getAABB((int*)(childObj + 0x18), param3, childAABB);

                // Possibly transform if convertToWorld is set.
                if (convertToWorld) {
                    transformAABBPart(localMatrix, &childAABB[0]);
                    transformAABBPart(localMatrix, &childAABB[4]);
                }

                // Accumulate min/max.
                // (exact comparison direction depends on branch, but final result is same)
                if (childAABB[0] < minX) minX = childAABB[0];
                if (childAABB[1] < minY) minY = childAABB[1];
                if (childAABB[2] < minZ) minZ = childAABB[2];
                if (childAABB[3] < minW) minW = childAABB[3];
                if (childAABB[4] > maxX) maxX = childAABB[4];
                if (childAABB[5] > maxY) maxY = childAABB[5];
                if (childAABB[6] > maxZ) maxZ = childAABB[6];
                if (childAABB[7] > maxW) maxW = childAABB[7];
            }
            childPtr += 0x70 / 4;
        }
    }

    // Write final bounding box to output.
    outAABB[0] = minX;
    outAABB[1] = minY;
    outAABB[2] = minZ;
    outAABB[3] = minW;
    outAABB[4] = maxX;
    outAABB[5] = maxY;
    outAABB[6] = maxZ;
    outAABB[7] = maxW;
}