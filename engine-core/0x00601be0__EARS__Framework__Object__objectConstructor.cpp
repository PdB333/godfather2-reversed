// FUNC_NAME: EARS::Framework::Object::objectConstructor
void __thiscall EARS::Framework::Object::objectConstructor(EARS::Framework::Object* this, byte flags) {
    // Call base initialization (likely sets vtable, refcount = 0, etc.)
    baseInit();
    // If flag bit 0 is set, perform additional setup (e.g., allocate memory, increment refcount)
    if ((flags & 1) != 0) {
        additionalSetup(this);
    }
}