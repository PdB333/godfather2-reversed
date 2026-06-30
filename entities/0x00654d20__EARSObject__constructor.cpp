// FUNC_NAME: EARSObject::constructor
class EARSObject {
public:
    // __thiscall: 'this' passed in ECX, allocFlag on stack
    EARSObject* __thiscall constructor(byte allocFlag);
};

EARSObject* __thiscall EARSObject::constructor(byte allocFlag) {
    // FUN_00654d40 - base class initializer (likely sets vtable, clears members)
    initBase();

    // If allocFlag has bit 0 set, the object was dynamically allocated
    // (via operator new). This block registers the object with the memory
    // manager or performs additional heap-specific setup.
    if ((allocFlag & 1) != 0) {
        registerAllocation(this);  // FUN_009c8eb0
    }

    return this;
}