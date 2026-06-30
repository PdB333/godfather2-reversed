// FUNC_NAME: BaseObject::constructor

class BaseObject {
public:
    // Offset +0x00: vtable pointer (4 bytes)
    // Offset +0x04: subobject first (size unknown, likely 12 bytes)
    // Offset +0x10: subobject second (size unknown)
    // Constructor initializes two embedded subobjects and calls a static init

    void __fastcall constructor() {
        // Initialize first subobject at offset 0x04
        FUN_004bc640(reinterpret_cast<int>(this) + 4);
        // Initialize second subobject at offset 0x10
        FUN_004bc6d0(reinterpret_cast<int>(this) + 0x10);
        // Static initialization call with null argument (likely sets global state or registers)
        FUN_004bc740(0);
    }
};