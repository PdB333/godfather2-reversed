// FUNC_NAME: CBaseObject::clearReferenceCount
void __fastcall CBaseObject::clearReferenceCount(CBaseObject* this)
{
    // +0x8: reference count field, set to zero to indicate no references
    this->referenceCount = 0;
    return;
}