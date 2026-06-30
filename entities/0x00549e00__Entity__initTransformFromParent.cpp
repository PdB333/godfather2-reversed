// FUNC_NAME: Entity::initTransformFromParent
void __thiscall Entity::initTransformFromParent(int this)
{
    // Stack buffer for parent transform data (size 0x3C+ bytes)
    struct ParentTransformBuffer {
        float data[16]; // enough to cover offsets 0x3C
    } localBuf;

    // Initialization of stack fields (preparation for virtual call)
    localBuf.data[0] = 0.0f;                    // local_44 at offset 0x00? Actually corresponds to -0x44 from ebp
    localBuf.data[0] = 0.0f;                    // local_34 at offset 0x10? (mapping uncertain)
    localBuf.data[0] = 0.0f;                    // local_24 at offset 0x20? 
    localBuf.data[15] = DAT_00e2b1a4;          // local_14 at offset 0x3C

    // vtable at +0x10c, virtual function at offset 0x90 (index 36)
    // Gets parent world transform into localBuf (params: output buffer, source at +0x110, flag=1)
    void** vtable = *(void***)(this + 0x10c);
    typedef void (*GetTransformFunc)(void*, void*, int);
    GetTransformFunc func = (GetTransformFunc)(vtable[0x90/4]);
    func(&localBuf, (void*)(this + 0x110), 1);

    // Copy extracted fields from parent transform to local transform member
    // Fields at offsets from localBuf: uStack_2c (offset 0x24), uStack_28 (0x28), local_24 (0x2C)
    *(float*)(this + 0x40) = *((float*)&localBuf + 0x24/4);   // +0x40: field A
    *(float*)(this + 0x44) = *((float*)&localBuf + 0x28/4);   // +0x44: field B
    *(float*)(this + 0x48) = *((float*)&localBuf + 0x2C/4);   // +0x48: field C
    *(float*)(this + 0x4C) = DAT_00e2b1a4;                     // +0x4C: constant from global

    // Initialize additional component at +0x10 from a 12-byte local buffer
    // FUN_004b59d0 likely computes or copies quaternion/translation
    char localBuf2[12]; // auStack_5c
    FUN_004b59d0(localBuf2, (void*)(this + 0x10));
}