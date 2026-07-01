//FUNC_NAME: SomeClass::constructor (0x007ebff0)
// Role: Constructor for a class that initializes vtable pointers and zeroes fields.
// Likely part of EARS engine or game object hierarchy.

class SomeClass : public BaseClass {
public:
    // Constructor
    SomeClass(void* param_2) : BaseClass(param_2) {
        // Set vtable pointer
        this->vtable = &PTR_FUN_00d6ff90;

        // Set interface pointers at offsets 0x3C and 0x48
        this->interface1 = &PTR_LAB_00d6ff80;  // +0x3C
        this->interface2 = &PTR_LAB_00d6ff7c;  // +0x48

        // Zero out fields
        this->field_0x50 = 0;                  // +0x50 (4 bytes)
        this->field_0x54 = 0;                  // +0x54 (2 bytes)
        this->field_0x56 = 0;                  // +0x56 (2 bytes)
        this->field_0x58 = 0;                  // +0x58 (4 bytes)
    }

private:
    // Vtable pointer at +0x00
    void** vtable;

    // Interface pointers
    void* interface1;   // +0x3C
    void* interface2;   // +0x48

    // Fields
    int field_0x50;     // +0x50
    short field_0x54;   // +0x54
    short field_0x56;   // +0x56
    int field_0x58;     // +0x58
};