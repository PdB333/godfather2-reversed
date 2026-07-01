// FUNC_NAME: SomeObject::init
// Function address: 0x0088fec0
// This function appears to be an initializer for a simple object structure.
// It calls a sub-initializer with two fields (offsets +0x4 and +0x8) and
// zeros out a third field at offset +0xC.

// Forward declaration of the sub-initializer function
void __fastcall subInit(uint32_t field1, uint32_t field2);

// The object structure (offset sizes assumed 4 bytes each)
struct SomeObject {
    uint32_t field_0;  // +0x00 (likely vtable or other data)
    uint32_t field_4;  // +0x04 (first parameter to subInit)
    uint32_t field_8;  // +0x08 (second parameter to subInit)
    uint32_t field_C;  // +0x0C (initialized to 0 here)
};

void __thiscall SomeObject::init() {
    // Call the sub-initializer with the two stored values
    subInit(this->field_4, this->field_8);

    // Zero out the field at offset 0xC
    this->field_C = 0;
}