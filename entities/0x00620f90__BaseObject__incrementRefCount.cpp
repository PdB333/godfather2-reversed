// FUNC_NAME: BaseObject::incrementRefCount
int __fastcall BaseObject::incrementRefCount(BaseObject* this_)
{
    // +0x18: reference count (int32)
    int& refCount = *(int*)((char*)this_ + 0x18);
    ++refCount;
    return refCount;
}