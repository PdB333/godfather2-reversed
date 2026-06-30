// FUNC_NAME: Entity::computeBoundingBox
// Address: 0x00558db0
// This function computes an axis-aligned bounding box (AABB) from a set of bone positions,
// scales it by a global factor, adds an offset, and then calls a setter function.
// It iterates over a string of bone indices (null-terminated) stored in the skeleton data,
// retrieves each bone's position via a virtual function on the model, and computes min/max in 4D.
// The output bounding box center is stored to a pointer passed via EDI (parameter not declared).
// Then the adjusted extents are passed to another function (likely to set the bbox on the entity).

float g_bboxScale = 0.5f; // DAT_00e2cd54 (scale factor, likely 0.5 to average)
float g_initialMin = 3.402823e+38f; // DAT_00e2e50c (FLT_MAX)
float g_initialMax = -3.402823e+38f; // DAT_00e44758 (-FLT_MAX)
float g_fixedW = 0.0f; // DAT_00e2b1a4 (constant for fourth dimension, e.g., time or zero)

struct SkeletonData {
    char pad_0x00[0x04];
    char boneIndices; // +0x04: null-terminated string of bone indices
    float offset; // +0x0C: translation offset to apply
};

class IModel {
public:
    virtual void getBonePosition(int boneIdx, float* outPos) = 0; // vtable+0xA4
    // Returns position as 3 floats (x,y,z) in outPos[0..2]
};

// The function uses EDI as an implicit output pointer (set by caller)
void Entity::computeBoundingBox(SkeletonData* pSkeleton, IModel* pModel, float* pOutCenter) {
    // pOutCenter is set via EDI, not a C++ parameter
    // pThis (param_1) is unused in this function (could be the owning entity)

    char cBoneIdx = pSkeleton->boneIndices;
    char* pIdx = &pSkeleton->boneIndices;

    // Initialize min/max for x,y,z,w
    float minX = g_initialMin;
    float minY = g_initialMin;
    float minZ = g_initialMin;
    float minW = 0.0f; // local_14
    float maxX = g_initialMax;
    float maxY = g_initialMax;
    float maxZ = g_initialMax;
    float maxW = 0.0f; // local_24

    float scale = g_bboxScale;
    while (cBoneIdx > '\0') {
        int boneParam = cBoneIdx * 4; // index * sizeof(float)
        float pos[3]; // local_3c, fStack_38, fStack_34 (x,y,z)
        // Virtual call: get bone position (presumably world space)
        pModel->getBonePosition(boneParam, pos);

        // Update min/max for x,y,z
        if (pos[0] < minX) minX = pos[0];
        if (pos[1] < minY) minY = pos[1];
        if (pos[2] < minZ) minZ = pos[2];
        if (pos[0] > maxX) maxX = pos[0];
        if (pos[1] > maxY) maxY = pos[1];
        if (pos[2] > maxZ) maxZ = pos[2];
        // For w component, we ensure the bbox includes the fixed value g_fixedW
        if (g_fixedW <= minW) minW = g_fixedW;
        if (maxW <= g_fixedW) maxW = g_fixedW;

        // Advance to next bone index
        pIdx++;
        cBoneIdx = *pIdx;
    }

    // Compute center as (max+min)*scale (scale = 0.5f effectively)
    pOutCenter[0] = (maxX + minX) * scale;
    pOutCenter[1] = (maxY + minY) * scale;
    pOutCenter[2] = (maxZ + minZ) * scale;
    pOutCenter[3] = (maxW + minW) * scale;

    // Compute adjusted extents: (max - center) + offset
    // These are passed to a setter function to finalize the bbox
    float extents[4];
    extents[0] = (maxX - pOutCenter[0]) + pSkeleton->offset;
    extents[1] = (maxY - pOutCenter[1]) + pSkeleton->offset;
    extents[2] = (maxZ - pOutCenter[2]) + pSkeleton->offset;
    extents[3] = (maxW - pOutCenter[3]) + pSkeleton->offset;

    // Call setter function (likely to store the bbox on the entity)
    FUN_00a66880(extents);
}