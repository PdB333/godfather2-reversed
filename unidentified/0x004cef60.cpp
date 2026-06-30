// FUN_004cef60: ObjectHandle::initHandle
int __thiscall ObjectHandle::initHandle(ObjectHandle *this, ObjectWithVTable *pObj, int resourceId)
{
    uint duplicatedId;
    ObjectWithVTable *localPObj;

    localPObj = pObj;
    // +8: likely AddRef or Retain
    pObj->vtable->vfunc8(pObj);
    if (resourceId == 0) {
        duplicatedId = 0;
    }
    else {
        duplicatedId = FUN_004265d0(resourceId, pObj);   // duplicate resource/ID
    }
    FUN_004cf330(pObj, duplicatedId);                   // internal setup
    this->m_pObj = pObj;                                 // +0x10
    // Another retain on the same object
    pObj->vtable->vfunc8(pObj);
    if (resourceId != 0) {
        duplicatedId = FUN_004265d0(resourceId, this->m_pObj);
        this->m_resourceId = duplicatedId;               // +0x14
        // +4: likely a method that takes two args (resourceId and a flag)
        pObj->vtable->vfunc4(resourceId, 0);
        // +0xC: finalize or maybe release
        pObj->vtable->vfuncC();
        return this;
    }
    this->m_resourceId = 0;                              // +0x14
    pObj->vtable->vfuncC();
    return this;
}