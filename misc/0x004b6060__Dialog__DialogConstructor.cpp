// FUNC_NAME: Dialog::DialogConstructor
// Reconstructed constructor for a dialog/UI element object.
// Initializes vtable pointers, stores parameters, and calls an external initialization function.

class Dialog {
public:
    // Constructor (__thiscall)
    // param_2: some ID/identifier
    // param_3: some parameter
    // param_4: pointer to a byte that receives result from FUN_004b6140
    void *initialize(Dialog *this, int param_2, int param_3, unsigned char *param_4) {
        // Store parameters at offsets +4 and +8
        this->field_1 = param_2;   // +0x04
        this->field_2 = param_3;   // +0x08

        // Set vtable pointer to base class or function table
        this->vtable = (void *)&PTR_FUN_00e358b8;  // +0x00

        // Set another vtable/function pointer (later overwritten)
        this->field_3 = (void *)&PTR_FUN_00e2f19c; // +0x0C

        // Flag/setting: 1
        this->field_4 = 1;                          // +0x10

        // Another flag
        this->field_5 = 0;                          // +0x14

        // Overwrite field_3 with label pointer
        this->field_3 = (void *)&PTR_LAB_00e35940;  // +0x0C (final value)

        // Zero out fields for data
        this->field_6 = 0;                          // +0x18
        this->field_7 = 0;                          // +0x1C
        this->field_8 = 0;                          // +0x20
        this->field_9 = 0;                          // +0x24

        // Byte field at offset +0x28
        *(unsigned char *)((int)this + 0x28) = 0;

        // External initialization, returns a byte result
        unsigned char result = FUN_004b6140();
        *param_4 = result;                          // store result to caller's pointer

        return this;  // return this pointer (implicit in __thiscall)
    }
};