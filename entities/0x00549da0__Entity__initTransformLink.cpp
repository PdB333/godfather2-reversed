// FUNC_NAME: Entity::initTransformLink
void __thiscall Entity::initTransformLink(int esiParam /* passed via ESI register */) {
    // local buffer for result from virtual call (probably a 3-vector or quaternion)
    int local_result[3];

    // Call virtual method at vtable offset 0xa4 on object pointed to by m_pTransform (+0x10c)
    // This likely retrieves a transform matrix or orientation data.
    int* transformObj = *(int**)((int)this + 0x10c);
    (**(code**)(transformObj[0] + 0xa4))(local_result);

    // +0x40: store pointer to internal sub-structure at +0x110 (e.g., a matrix buffer)
    *(int*)((int)this + 0x40) = (int)this + 0x110;
    // +0x44: store the ESI parameter (maybe a resource handle or ID)
    *(int*)((int)this + 0x44) = esiParam;
    // +0x48: copy first element of virtual call result
    *(int*)((int)this + 0x48) = local_result[0];
    // +0x4c: store a global constant (likely an identity value)
    *(int*)((int)this + 0x4c) = DAT_00e2b1a4;
}