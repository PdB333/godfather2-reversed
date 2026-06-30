// FUNC_NAME: GameObject::initialize
undefined4 __thiscall GameObject::initialize(byte flags) {
    char isValid;

    // Base initialization (likely calls base class constructor)
    baseConstructor();

    // If the low bit of flags is set, perform additional validation
    if ((flags & 1) != 0) {
        isValid = validateObject(this);
        if (isValid == '\0') {
            // If validation fails, call a cleanup function via global engine vtable
            // g_Engine is at DAT_012234ec, offset +4 points to a method table
            // This call likely corresponds to engine->release(this, 0)
            (**(code **)(**(int **)(g_Engine + 4) + 4))(this, 0);
        }
    }
    return this;
}