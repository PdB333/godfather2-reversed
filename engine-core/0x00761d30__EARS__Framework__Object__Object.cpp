// FUNC_NAME: EARS::Framework::Object::Object
void* __thiscall EARS::Framework::Object::Object(EARS::Framework::Object* this, byte flags) {
    // Call base class initialization (likely a global constructor registration or vtable setup)
    ::FUN_00761b90();

    // If the low bit is set, perform cleanup or destructor-like operation
    if ((flags & 1) != 0) {
        this->release(); // FUN_00624da0 likely a release/destructor
    }

    return this;
}