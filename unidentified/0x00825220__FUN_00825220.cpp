// FUNC_NAME: SomeClass::SomeClass
// Constructor: Initializes object with a scaled value from a source object.
// Calls base class constructor (FUN_008334a0), sets vtable pointer, and
// computes field at +0x4c as product of source's field +0x4c and a float scale.
// Offsets:
//   +0x00 : vtable pointer (PTR_LAB_00d73448)
//   +0x4c : float field (index 0x13)

__thiscall SomeClass* SomeClass::SomeClass(SomeClass* source, float scale) {
    // Base class constructor (likely sets up initial vtable and fields)
    FUN_008334a0(); // assumed to take this implicitly

    // Override vtable to derived class vtable
    this->vtable = (SomeClassVTable*)&PTR_LAB_00d73448;

    // Initialize field at offset 0x4c with scaled value from source
    this->field_0x4c = *(float*)((uint8_t*)source + 0x4c) * scale;

    return this;
}