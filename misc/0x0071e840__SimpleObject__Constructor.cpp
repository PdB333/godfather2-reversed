// FUNC_NAME: SimpleObject::Constructor
// Address: 0x0071e840
// This function initializes an object with a vtable pointer and stores a global reference at offset +0x08.
// It is called from 0x007116d0 (likely part of a larger initialization sequence).

class SimpleObject {
public:
    void **vtable;      // +0x00: virtual table pointer
    void *field_0x08;   // +0x08: pointer to some global data (DAT_00d5ccf8)
};

void __thiscall SimpleObject::Constructor(SimpleObject *this) {
    this->vtable = (void**)&PTR_LAB_00d61e58; // Set vtable to global table
    this->field_0x08 = (void*)DAT_00d5ccf8;   // Store global pointer
    return;
}