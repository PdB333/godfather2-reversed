// FUNC_NAME: RefCounted::release
void __fastcall RefCounted::release(RefCounted* this) {
    // Call release on the managed object with the current reference count
    FUN_008285c0(this->object, this->refCount);
    // Clear the weak flag or similar
    this->someFlag = 0;
    // If there are multiple references, perform additional cleanup
    if (this->refCount > 1) {
        FUN_009c8f10(this->object);
    }
}