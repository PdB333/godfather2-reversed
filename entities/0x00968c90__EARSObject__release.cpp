//FUNC_NAME: EARSObject::release
int __thiscall EARSObject::release(byte shouldFree) {
    // Destroy sub-object at offset +0x8
    destroySubObject(*(void**)(this + 0x8));
    if (shouldFree & 1) {
        freeObject(this);
    }
    return this;
}