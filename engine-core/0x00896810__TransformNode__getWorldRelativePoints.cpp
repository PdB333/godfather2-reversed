// FUNC_NAME: TransformNode::getWorldRelativePoints
// Function address: 0x00896810
// Computes two world-space points from local offsets relative to a parent transform.
// The object stores two local 4D vectors at offsets 0x30 and 0x40.
// The parent transform's world position is obtained via a vtable function at offset 0x1C.
// The global _DAT_00d5780c is likely 1.0f (homogeneous w component for parent position).
void __thiscall TransformNode::getWorldRelativePoints(TransformNode* this, float* outWorldPoints)
{
    float parentPosX, parentPosY, parentPosZ; // Parent world position extracted by vtable call

    // Call parent's getPosition function (vtable offset 0x1C)
    // First argument is the pointer stored at offset 0x00 (likely parent transform pointer)
    (*(void (__thiscall**)(void*, float*))(*((int*)this + 7)))(*((int*)this), &parentPosX);

    // Local vector 1: floats at this+0x30 (x,y,z,w)
    // Local vector 2: floats at this+0x40 (x,y,z,w)
    float* localVec1 = (float*)this + 0xc; // offset 0x30
    float* localVec2 = (float*)this + 0x10; // offset 0x40

    float parentW = _DAT_00d5780c; // global constant (e.g., 1.0f)

    // Compute world points: parent position added to local offsets
    outWorldPoints[0] = localVec1[0] + parentPosX;
    outWorldPoints[1] = localVec1[1] + parentPosY;
    outWorldPoints[2] = localVec1[2] + parentPosZ;
    outWorldPoints[3] = localVec1[3] + parentW;
    outWorldPoints[4] = localVec2[0] + parentPosX;
    outWorldPoints[5] = localVec2[1] + parentPosY;
    outWorldPoints[6] = localVec2[2] + parentPosZ;
    outWorldPoints[7] = localVec2[3] + parentW;
}