// FUNC_NAME: Transform::clone
undefined4* __thiscall Transform::clone(Transform* this, uint ownerId, bool addToRegistry)
{
    // local allocation parameters: size=0x60, flags=2, alignment=0x10, unknown=0
    uint allocParams[3] = {2, 0x10, 0};
    Transform* src = (Transform*)MemoryManager::allocate(0x60, allocParams);
    if (src == (Transform*)0x0) {
        src = (Transform*)0x0;
    } else {
        src->field_0x4c = 0;          // +0x4C: unknown
        src->field_0x50 = (uint)this; // +0x50: store this pointer (source)
        src->field_0x4c = ownerId;    // +0x4C: overwritten with owner ID
        // Record allocation in global linear allocator buffer at g_allocator+0x14
        int* allocPtr = (int*)(DAT_01206880 + 0x14);
        **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_011250a4; // vtable? 
        *allocPtr = *allocPtr + 4;
        *(undefined4**)*allocPtr = src;
        *allocPtr = *allocPtr + 4;
        *(undefined4*)*allocPtr = ownerId;
        *allocPtr = *allocPtr + 4;
        *(undefined4*)*allocPtr = (uint)this;
        *allocPtr = *allocPtr + 4;
    }
    // Copy the 16 dwords (0x40 bytes) from source (this) into the new block
    uint v0, v1, v2, v3;
    v0 = this->m[0];  // Assuming this is a 4x4 matrix stored as 16 floats (dwords)
    v1 = this->m[1];
    v2 = this->m[2];
    v3 = this->m[3];
    src->m[0] = v0;
    src->m[1] = v1;
    src->m[2] = v2;
    src->m[3] = v3;
    // ... repeat for m[4]..m[15]
    // (For brevity, assume full copy block)
    // ... (the decompiler shows copy of 16 dwords from this to src)
    // After copy, record allocation in another pool (aligned copy destination)
    int* allocPtr = (int*)(DAT_01206880 + 0x14);
    **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_011250cc;
    *allocPtr = *allocPtr + 4;
    *(undefined4**)*allocPtr = src;
    *allocPtr = *allocPtr + 4;
    void* alignedDest = (void*)((*allocPtr) + 0x13 & 0xfffffff0);
    *allocPtr = (int)alignedDest;
    memcpy(alignedDest, src, 0x40); // copy matrix to aligned buffer
    *allocPtr = *allocPtr + 0x40;
    // Set new block's reference/index fields
    src->refCount = -1; // +0x10
    src->flags = 0;     // +0x11
    src->next = 0;      // +0x12
    // If requested, register the clone in another list
    if (addToRegistry != 0) {
        int* allocPtr = (int*)(DAT_01206880 + 0x14);
        **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_011250e0;
        *allocPtr = *allocPtr + 4;
        *(undefined4*)*allocPtr = ownerId;
        *allocPtr = *allocPtr + 4;
        *(undefined4**)*allocPtr = src;
        *allocPtr = *allocPtr + 4;
        *(undefined4*)*allocPtr = 0xffffffff;
        *allocPtr = *allocPtr + 4;
    }
    return src;
}