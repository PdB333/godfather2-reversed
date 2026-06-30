// FUNC_NAME: EARSRefObject::EARSRefObject
void __thiscall EARSRefObject::EARSRefObject(void *this, void *sourceObj, uint32_t handleId)
{
    // +0x00: vtable pointer (base class)
    *(uint32_t *)this = &g_vtable_EARSRefObject_base;  // PTR_LAB_00e414e0
    // +0x08: store the handle identifier
    *(uint32_t *)((char *)this + 8) = handleId;
    // Retrieve the reference-counted object associated with this handle
    // FUN_00621530 returns a pointer to a RefCountedObject (e.g., a resource)
    RefCountedObject *refObj = (RefCountedObject *)FUN_00621530(handleId);
    // Increment the reference count at offset +0x12 (short)
    *(short *)((char *)refObj + 0x12) = *(short *)((char *)refObj + 0x12) + 1;
    // +0x10: store pointer to the reference-counted object
    *(RefCountedObject **)((char *)this + 0x10) = refObj;
    // +0x04: copy first 4 bytes from source object (likely a vtable or identifier)
    *(uint32_t *)((char *)this + 4) = *(uint32_t *)sourceObj;
    // Zero-initialize many fields:
    // +0x0c, +0x14, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x2c, +0x30, +0x34, +0x38, +0x3c, +0x40, +0x44 (byte)
    *(uint32_t *)((char *)this + 0x0c) = 0;  // field3
    *(uint32_t *)((char *)this + 0x14) = 0;  // field5
    *(uint32_t *)((char *)this + 0x18) = 0;  // field6
    *(uint32_t *)((char *)this + 0x1c) = 0;  // field7
    *(uint32_t *)((char *)this + 0x28) = 0;  // field10
    *(uint32_t *)((char *)this + 0x24) = 0;  // field9
    *(uint32_t *)((char *)this + 0x20) = 0;  // field8
    *(uint32_t *)((char *)this + 0x2c) = 0;  // field11
    *(uint32_t *)((char *)this + 0x38) = 0;  // field14
    *(uint32_t *)((char *)this + 0x3c) = 0;  // field15
    *(uint32_t *)((char *)this + 0x40) = 0;  // field16
    *(char *)((char *)this + 0x44) = 0;      // field17 (single byte)
    *(uint32_t *)((char *)this + 0x30) = 0;  // field12
    // Finally set the derived class vtable
    *(uint32_t *)this = &g_vtable_EARSRefObject_derived;  // PTR_LAB_00e35680
}