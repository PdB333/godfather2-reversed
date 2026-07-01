// FUNC_NAME: EARS::Framework::Object::constructor
// Address: 0x008a9090
// Role: Constructor for a base object with multiple inheritance support.
// Sets up vtable pointers, initializes fields, and calls base constructor.

class Object {
public:
    // Vtable pointers (offset 0 and offset 10 are vtable pointers for base and derived)
    void* vtable;          // +0x00: first vtable (base class)
    // Unknown fields at +0x04, +0x08
    int field_0x04;        // +0x04
    int field_0x08;        // +0x08
    // Pointer to sub-object (offset 10) stored at +0x14
    void* subObjectPtr;    // +0x14: points to this + 0x28 (offset 10)
    int field_0x18;        // +0x18: set to 0
    int field_0x1C;        // +0x1C
    int field_0x20;        // +0x20
    int field_0x24;        // +0x24: set to 1
    void* secondVtable;    // +0x28: second vtable pointer (derived class)
    int field_0x2C;        // +0x2C
    void* callbackFunc;    // +0x30: function pointer (set to 0x008a8910)
    int field_0x34;        // +0x34: set to 0

    // Constructor
    // param_2: flag indicating whether to allocate memory (non-zero = allocate)
    Object* constructor(int param_2) {
        void* allocatedMem = nullptr;
        if (param_2 != 0) {
            allocatedMem = FUN_00481610(); // Allocate memory (e.g., operator new)
        }
        FUN_0064d390(0, 1); // Some initialization routine

        // Set base vtable
        this->vtable = &PTR_LAB_00e317dc;
        this->field_0x18 = 0;

        // Call base class constructor
        FUN_00454a10(allocatedMem);

        this->field_0x24 = 1;

        // Override vtable with derived class vtable
        this->vtable = &PTR_LAB_00d79cec;
        this->secondVtable = &PTR_LAB_00d79bc0;
        this->callbackFunc = &LAB_008a8910;
        this->field_0x34 = 0;

        // Set sub-object pointer to point to the second vtable field
        this->subObjectPtr = &this->secondVtable;

        return this;
    }
};