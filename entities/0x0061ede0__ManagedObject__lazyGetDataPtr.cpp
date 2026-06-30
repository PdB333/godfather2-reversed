// FUNC_NAME: ManagedObject::lazyGetDataPtr
uint32_t * __thiscall ManagedObject::lazyGetDataPtr(ManagedObject *this) {
    if (*(char *)((int)this + 0x23) == '\0') {
        ManagedObject::initInternal(this);
    }
    return *(uint32_t **)this; // return the first 4-byte field (e.g., a data pointer or interface)
}