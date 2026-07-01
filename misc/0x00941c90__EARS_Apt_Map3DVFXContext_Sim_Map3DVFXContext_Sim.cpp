// Xbox PDB: EARS_Apt_Map3DVFXContext_Sim_Map3DVFXContext_Sim
// FUNC_NAME: VFXResourceHandle::constructor
VFXResourceHandle* __thiscall VFXResourceHandle::constructor(VFXResourceHandle* thisPtr)
{
    // Allocate a new VFXResource object (12 bytes, 16-byte alignment)
    VFXResource* resource = (VFXResource*)engineAlloc(0xC, 0x10);
    if (resource != nullptr) {
        resource = (VFXResource*)VFXResource::initialize(resource, 0xFFFFFFFF); // +0x00: vtable? +0x04: refCount
    }

    // Store resource pointer in handle
    thisPtr->m_pResource = resource; // +0x00

    // Increment reference count on the resource (offset +0x04)
    resource->m_refCount++;

    // Look up hash for the resource type string "rc_vfx"
    int resourceId = stringHash("rc_vfx");
    thisPtr->m_nResourceId = resourceId; // +0x04

    // Register this handle with the global VFX manager
    VFXResourceManager::registerHandle(g_pVFXManager, g_unknown); // DAT_00d5e288, _DAT_00d5c458

    return thisPtr;
}