// FUNC_NAME: BaseObject::constructWithFlag
undefined4 __thiscall BaseObject::constructWithFlag(BaseObject* this, byte flag) {
    // Call base class initializer (likely sets vtable, member init)
    this->initBase();

    // If the lowest bit of flag is set, perform additional cleanup/destruction
    // (e.g., deallocate memory or release resources)
    if (flag & 1) {
        this->cleanUp();
    }

    return (undefined4)this;
}