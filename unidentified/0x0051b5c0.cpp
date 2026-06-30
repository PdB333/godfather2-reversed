// FUN_0051b5c0: GameObject::getPositionOrientation(float* outVec4)

void __thiscall GameObject::getPositionOrientation(float* outVec4)
{
    // +0xbc: Pointer to bone/skeleton transform (null if using local transform)
    void* skeletonTransform = *(void**)(this + 0xbc);
    
    if (skeletonTransform != nullptr) {
        // +0x30: Possibly offset to a bone index or parent transform
        // FUN_0056b420: Computes world transform from skeleton
        FUN_0056b420(this + 0x30, skeletonTransform, outVec4);
        return;
    }
    
    // Direct local transform stored at offset 0x60-0x6c (4 floats)
    // Typically: position (x,y,z) + orientation quaternion w? Or orientation scalar?
    outVec4[0] = *(float*)(this + 0x60);   // x
    outVec4[1] = *(float*)(this + 0x64);   // y
    outVec4[2] = *(float*)(this + 0x68);   // z
    outVec4[3] = *(float*)(this + 0x6c);   // w (or radius)
}