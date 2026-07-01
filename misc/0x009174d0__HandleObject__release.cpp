// FUNC_NAME: HandleObject::release
void HandleObject::release() {
    // offset +0x04: reference count (set to 0 before releasing)
    this->refCount = 0;
    // offset +0x00: pointer/handle to be released
    closeHandle(this->handle);
    this->handle = nullptr; // +0x00 cleared
    this->flags = 0;        // +0x08 cleared
}