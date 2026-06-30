// FUNC_NAME: EARS_Object::constructor
// Address: 0x00476880
// This function initializes an EARS engine object, setting up its vtable and initializing two sub-objects.

class EARS_Object {
public:
    // Constructor for EARS_Object
    void __thiscall constructor() {
        // Set the primary vtable pointer at offset 0x00
        *(void**)this = &PTR_FUN_00e32ecc;

        // Set secondary function table pointers:
        // +0x3C (0xF * 4) - likely another vtable or function pointer table
        *(void**)((char*)this + 0x3C) = &PTR_LAB_00e32ee8;
        // +0x48 (0x12 * 4) - another table
        *(void**)((char*)this + 0x48) = &PTR_LAB_00e32ef8;

        // Initialize sub-object at offset +0x50 (0x14 * 4)
        // Two-stage initialization: base init then additional setup
        FUN_004086d0((char*)this + 0x50);
        FUN_00408310((char*)this + 0x50);

        // Initialize sub-object at offset +0x58 (0x16 * 4)
        FUN_004086d0((char*)this + 0x58);
        FUN_00408310((char*)this + 0x58);

        // Global engine initialization call (singleton or static)
        FUN_0046c640();
    }
};