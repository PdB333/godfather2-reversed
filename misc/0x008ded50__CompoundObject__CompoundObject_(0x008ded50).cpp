// FUNC_NAME: CompoundObject::CompoundObject (0x008ded50)
// Constructor for a class with multiple inheritance (sets up several vtable pointers).
// Called from multiple derived class constructors (e.g., FUN_008dea90, FUN_008decb0, etc.)

void __thiscall CompoundObject::CompoundObject(CompoundObject *this) {
    // Set main vtable pointer (offset +0x00)
    *this = &PTR_FUN_00d7f470;
    // Set secondary vtable pointers for additional interfaces (offsets in multiples of 4)
    this[0xf] = &PTR_LAB_00d7f460;  // +0x3C
    this[0x12] = &PTR_LAB_00d7f45c; // +0x48
    this[0x14] = &PTR_LAB_00d7f458; // +0x50
    this[0x15] = &PTR_LAB_00d7f3f8; // +0x54
    this[0x16] = &PTR_LAB_00d7f390; // +0x58
    // Call common initialization routine (likely base class constructor or member setup)
    CompoundObject::initialize();
}