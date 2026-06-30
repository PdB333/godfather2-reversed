// FUNC_NAME: EARSObject::EARSObject

class EARSObject : public BaseClass {
public:
    // vtable at +0x00
    // second vtable at +0x14
    EARSObject(byte allocFlag);
};

EARSObject::EARSObject(byte allocFlag) {
    // Set vtable pointer
    this->vtable = &PTR_LAB_00d65250;
    // Set second vtable pointer (possibly an interface or derived vtable)
    *(void**)((char*)this + 0x14) = &PTR_LAB_00d6524c;

    // Call base class constructor
    BaseClass::BaseClass();

    // If the low bit of allocFlag is set, perform additional initialization
    // (e.g., allocate heap memory, register in a manager, or handle dynamic allocation)
    if (allocFlag & 1) {
        // FUN_00624da0(this) - likely a post-construction hook or memory deletion callback
        // In EA EARS engine, this may be a function that marks the object as self-owned
        postConstructionCallback(this);
    }
}