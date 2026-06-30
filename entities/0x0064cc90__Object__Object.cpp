// FUNC_NAME: Object::Object
// Function at 0x0064cc90: Base class constructor initializes vtable pointer and zeros four fields
void __fastcall Object::Object(Object *this) {
    // Set vtable pointer to class-specific table
    this->vtable = &g_vtable_00e317c4; // +0x00

    // Zero out fields at offsets 0x60, 0x64, 0x68, 0x6C (likely flags/counters)
    this->field_0x60 = 0; // +0x60 (param_1[0x18])
    this->field_0x64 = 0; // +0x64 (param_1[0x19])
    this->field_0x68 = 0; // +0x68 (param_1[0x1a])
    this->field_0x6C = 0; // +0x6C (param_1[0x1b])
}