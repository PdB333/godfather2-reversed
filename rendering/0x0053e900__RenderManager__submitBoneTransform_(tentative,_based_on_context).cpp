// FUNC_NAME: RenderManager::submitBoneTransform (tentative, based on context)
void __thiscall RenderManager::submitBoneTransform(void* this, EntrySlot* pSlot) {
    // pSlot->flags +0x28: active flag (0x01)
    if (*(char*)(pSlot + 0x28) != 0x01)
        return;

    // pSlot->boneIndex +0x20: index into bone array; pSlot->boneArrayBase +0x10
    BoneData* pBone = (BoneData*)(*(signed char*)(pSlot + 0x20) + (int)(pSlot + 0x10));
    if (pBone == nullptr)
        return;

    // Bone type check: 0x07 = hidden/unused
    if (*(char*)(pBone + 0xD8) == 0x07)
        return;

    // Copy bone transformation matrix (16 floats) from bone structure in a specific order
    // Offsets: +0xE0 .. +0xF8 (first 7), then +0x11C (last row/column?), then +0xFC .. +0x118 (remaining 8)
    struct Matrix4x4 {
        float m[4][4];
    } localMatrix;

    localMatrix.m[0][0] = *(float*)(pBone + 0xE0);
    localMatrix.m[0][1] = *(float*)(pBone + 0xE4);
    localMatrix.m[0][2] = *(float*)(pBone + 0xE8);
    localMatrix.m[0][3] = *(float*)(pBone + 0xEC);
    localMatrix.m[1][0] = *(float*)(pBone + 0xF0);
    localMatrix.m[1][1] = *(float*)(pBone + 0xF4);
    localMatrix.m[1][2] = *(float*)(pBone + 0xF8);
    localMatrix.m[3][3] = *(float*)(pBone + 0x11C); // last element
    localMatrix.m[1][3] = *(float*)(pBone + 0xFC);
    localMatrix.m[2][0] = *(float*)(pBone + 0x100);
    localMatrix.m[2][1] = *(float*)(pBone + 0x104);
    localMatrix.m[2][2] = *(float*)(pBone + 0x108);
    localMatrix.m[2][3] = *(float*)(pBone + 0x10C);
    localMatrix.m[3][0] = *(float*)(pBone + 0x110);
    localMatrix.m[3][1] = *(float*)(pBone + 0x114);
    localMatrix.m[3][2] = *(float*)(pBone + 0x118);

    // Retrieve rendering context ID from this->contextManager +0x4 -> +0x6C -> +4
    uint32_t contextId = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(this + 4) + 0x6C) + 4);

    // Call virtual method on pBone->object (vtable) at offset 0x1c
    // This likely sets a shader constant or submits the transform
    char outputBuffer[32]; // destination buffer for the call
    void* pObject = *(void**)(pBone + 0x10);
    (*(void(__thiscall**)(void*, Matrix4x4*, uint32_t, char*))(*(uint32_t*)pObject + 0x1C))
        (pObject, &localMatrix, contextId, outputBuffer);

    // Call next method to finalize or apply the transform (e.g., submit draw call)
    char someBuffer[12];
    FUN_0053ea50(this, someBuffer);
}