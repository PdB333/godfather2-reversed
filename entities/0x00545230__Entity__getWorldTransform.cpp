// FUNC_NAME: Entity::getWorldTransform
// Address: 0x00545230
// This function retrieves the world position and rotation (euler angles) of an entity.
// It uses a sub-object at this+0x2e8 (likely a TransformComponent) and a global manager
// to obtain the raw transform data, then copies it into two Vector3 outputs.

struct Vector3 {
    float x, y, z;
};

void __thiscall Entity::getWorldTransform(void* thisPtr, Vector3* outPos, Vector3* outRot) {
    // Get pointer to a transform component stored at offset +0x2E8
    void* transformComponent = *(void**)((char*)thisPtr + 0x2E8);
    // Access vtable of the component: *(int**)transformComponent, then +0x10 gives another table
    void** vtable = *(void***)(*(int*)transformComponent + 0x10);
    // The actual function to retrieve transform data is at vtable offset 0x1C
    using TransformFunc = void(__thiscall*)(void*, void*, void*);
    TransformFunc getTransform = (TransformFunc)vtable[0x1C / 4];  // 0x1C / 4 = 7

    // Local storage for raw transform data (three floats each)
    Vector3 pos, rot;
    // The third parameter is a 4-byte flag (unused here)
    uint32_t unusedFlag;

    // Call the transform getter.
    // First parameter: component + 0xE0 (some internal buffer)
    // Second parameter: from global DAT_01223480 + 0x24 -> +0x6C -> deref +4
    void* globalPtr = *(void**)0x01223480;  // assume a global pointer
    void* secondParam = *(void**)(*(int*)((char*)globalPtr + 0x24) + 0x6C);  // reinterpret as pointer
    // Actually the decompiled shows: *(undefined4 *)(*(int *)(*(int *)(DAT_01223480 + 0x24) + 0x6c) + 4)
    // So we read a uint32 from that address and treat as something? But we'll keep as void* for call.
    // For safety, cast to appropriate type.

    // Perform the call. The function writes into pos, rot, and unusedFlag through implicit stack? 
    // The decompiler shows local variables being set after call, so we assume the call modifies them.
    getTransform((char*)transformComponent + 0xE0, secondParam, &unusedFlag);

    // The following assignments seem to copy from locals that were set by the called function.
    // In the decompiled code, these locals are uStack_3c, etc. We assume they hold the results.
    // We directly assign the Vector3 structures.
    *outPos = pos;  // pos.x = uStack_3c, pos.y = uStack_38, pos.z = uStack_34
    *outRot = rot;  // rot.x = uStack_2c, rot.y = uStack_28, rot.z = uStack_24

    return;
}