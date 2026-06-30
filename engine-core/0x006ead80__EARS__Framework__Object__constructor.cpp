// FUNC_NAME: EARS::Framework::Object::constructor
undefined4 __thiscall EARS::Framework::Object::constructor(EARS::Framework::Object *this, byte flags) {
    // Call base class initializer (likely EARS::Core::Object or similar)
    FUN_006eab20();

    // If low bit of flags is set, perform additional initialization (e.g., allocate memory of size 0x7c)
    if ((flags & 1) != 0) {
        // 0x7c = 124 bytes – could be a buffer or a derived sub-object
        FUN_0043b960(this, 0x7c);
    }

    return this;
}