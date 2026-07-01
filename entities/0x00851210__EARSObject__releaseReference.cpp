// FUNC_NAME: EARSObject::releaseReference
void EARSObject::releaseReference(EARSObject* obj)
{
    // Check if the object is valid and has no remaining references (refCount == 0)
    if (obj != nullptr && obj->refCount == 0) {
        // Delete the object when reference count reaches zero
        FUN_009e7450(obj); // likely operator delete or EARSObject::destroy
    }
}