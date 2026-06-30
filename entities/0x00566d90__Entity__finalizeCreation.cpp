// FUNC_NAME: Entity::finalizeCreation
void Entity::finalizeCreation(void) {
    // Read fields from object (offsets relative to this)
    // +0x34, +0x3C, +0x40, +0x44, +0x48: likely transformation data (e.g., position, rotation, scale)
    float field0x34 = *(float *)(this + 0x34);   // +0x34
    float field0x3C = *(float *)(this + 0x3C);   // +0x3C
    float field0x40 = *(float *)(this + 0x40);   // +0x40
    float field0x44 = *(float *)(this + 0x44);   // +0x44
    float field0x48 = *(float *)(this + 0x48);   // +0x48

    // Function pointer stored at +0x50
    void (*initCallback)(void *) = *(void (**)(void *))(this + 0x50);

    // Create temporary object using factory function
    // Order matches decompiled call: arg1 = +0x44, arg2 = +0x34, arg3 = +0x40, arg4 = +0x3C, arg5 = +0x48
    void *tempObject = createTemporaryObject(field0x44, field0x34, field0x40, field0x3C, field0x48);
    if (initCallback != nullptr) {
        initCallback(tempObject);
    }
    releaseTemporaryObject(tempObject);

    // Create a permanent object and store at +0x0C
    void *permanentObject = createPermanentObject();
    *(void **)(this + 0x0C) = permanentObject;
    if (permanentObject != nullptr) {
        // Call first virtual function of the permanent object (usually initialize or constructor)
        void (**vtable)(void) = *(void (***)(void))permanentObject;
        (*vtable)();
    }
    return;
}