// FUNC_NAME: BaseGameObject::constructor
// Address: 0x0043e060
// Role: Base class constructor initializing vtable, name, and fields then calling a common init function.
class BaseGameObject {
public:
    void** vtable;                   // +0x00: virtual function table pointer
    const char* name;                // +0x04: object name string
    char unknownFlag;                // +0x0C: byte flag (initialized to 0)
    // ... fields at +0x10, +0x14, +0x18 ...
    int field_0x1c;                  // +0x1C: initialized to 0
    int field_0x20;                  // +0x20: initialized to 0xF

    // Constructor: param_2 is likely a pointer to a parent or creation context
    __thiscall BaseGameObject(void* param_2) {
        vtable = &PTR_FUN_00da9810;   // set base vtable
        name = "unknown";             // default name
        field_0x1c = 0;
        field_0x20 = 0xF;
        unknownFlag = 0;              // byte at +0x0C
        FUN_0043eeb0(param_2, 0, 0xFFFFFFFF); // common initialization (e.g., register with manager)
        vtable = &PTR_FUN_00da9828;   // switch to final vtable (derived class)
    }
};