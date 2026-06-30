// FUNC_NAME: EARSObject::constructor
EARSObject* EARSObject::constructor() {
    // Call the second virtual function (vtable offset +4) – typically a post-construction initializer
    (*(void(__thiscall**)(EARSObject*))(this->vtable + 1))(this);
    return this;
}