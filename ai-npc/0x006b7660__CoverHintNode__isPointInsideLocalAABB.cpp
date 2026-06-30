// FUNC_NAME: CoverHintNode::isPointInsideLocalAABB
// Address: 0x006b7660
// Role: Checks if a world point is inside the cover hint node's local axis-aligned bounding box
//       after transforming the point by the node's world-to-local matrix (at offset +0x60).

bool __thiscall CoverHintNode::isPointInsideLocalAABB(CoverHintNode* this, const float* worldPos)
{
    // Copy the world point (Ghidra shows as undefined4 but it's float[3])
    float inputX = worldPos[0];
    float inputY = worldPos[1];
    float inputZ = worldPos[2];

    // Global constant (likely related to transform, e.g. w component or scale)
    float unknown = g_TransformConstant; // _DAT_00d5780c

    float localPoint[3]; // local_20, local_1c, local_18

    // Transform world point to local space using matrix at this+0x60
    // FUN_0056b420: assumed void __fastcall(float* matrix, float* input, float* output)
    TransformWorldToLocal((float*)((uintptr_t)this + 0x60), &inputX, localPoint);

    // Compare each axis against global min/max bounds (likely pre-defined AABB extents)
    if (g_AABBMIN <= localPoint[0] && localPoint[0] <= g_AABBMAX &&
        g_AABBMIN <= localPoint[1] && localPoint[1] <= g_AABBMAX &&
        g_AABBMIN <= localPoint[2] && localPoint[2] <= g_AABBMAX)
    {
        return true;
    }
    return false;
}