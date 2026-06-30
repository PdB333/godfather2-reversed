// FUNC_NAME: createResourceWithParams
// Address: 0x006d0290
// Description: Creates a resource with type=2, size=0x10, flags=0 via the global resource manager.

void createResourceWithParams(uint32_t param_1)
{
    // Get global resource manager singleton
    // FUN_009c8f80 returns pointer to an object with a vtable at offset 0
    uint32_t* pMgr = reinterpret_cast<uint32_t*>(FUN_009c8f80());

    // Creation parameters (local stack)
    struct CreationParams {
        uint32_t type;   // +0x00
        uint32_t size;   // +0x04
        uint32_t flags;  // +0x08
    } params = {2, 0x10, 0};

    // Call vtable[0] (virtual function) with this = pMgr, args = (param_1, &params)
    // This is a __thiscall method: virtual void createResource(uint32_t id, CreationParams* pParams);
    typedef void (__thiscall* CreateFunc)(void*, uint32_t, CreationParams*);
    CreateFunc func = reinterpret_cast<CreateFunc>(*reinterpret_cast<uint32_t*>(*pMgr));
    func(pMgr, param_1, &params);
}