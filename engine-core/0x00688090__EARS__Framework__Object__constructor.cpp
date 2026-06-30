// FUNC_NAME: EARS::Framework::Object::constructor
EARS::Framework::Object* __thiscall EARS::Framework::Object::constructor(EARS::Framework::Object* this, byte allocateFlag)
{
    // Set vtable pointer for primary base class at offset 0x00
    *this = &PTR_FUN_00d58b70;

    // Set vtable pointers for additional base classes (multiple inheritance)
    // Offset 0x3C (this + 0x0F) - secondary vtable pointer 1
    this->field_0x0F = &PTR_LAB_00d58b60;
    // Offset 0x48 (this + 0x12) - secondary vtable pointer 2
    this->field_0x12 = &PTR_LAB_00d58b5c;
    // Offset 0x50 (this + 0x14) - secondary vtable pointer 3
    this->field_0x14 = &PTR_LAB_00d58b58;
    // Offset 0x54 (this + 0x15) - secondary vtable pointer 4
    this->field_0x15 = &PTR_LAB_00d58af8;
    // Offset 0x58 (this + 0x16) - secondary vtable pointer 5
    this->field_0x16 = &PTR_LAB_00d58a90;

    // Call base class constructor (likely for first base class)
    baseConstructor();

    // If the allocateFlag's low bit is set, this object was heap-allocated;
    // free it with size 0x180 to prevent memory leak on construction failure.
    if ((allocateFlag & 1) != 0)
    {
        operatorDelete(this, 0x180);
    }

    return this;
}