// FUNC_NAME: EARSObject::constructor

// Global type manager (some EA engine structure)
extern char* DAT_01223410;

// Base class initialization function (FUN_0047d700)
void __thiscall EARSObject::init(EARSObject* this);

// Constructor with copy/init flag
EARSObject* __thiscall EARSObject::constructor(EARSObject* this, byte flags) {
    // Call base class init
    this->init();

    // If flag bit 0 is set, call the clone/init function from the type manager
    if (flags & 1) {
        // Offset 0x2d4 in the type manager points to a vtable-like structure
        int* vtable = *(int**)(DAT_01223410 + 0x2d4);
        // The second entry (offset 0x4) is a function taking this and an int parameter
        (*(void (__thiscall**)(EARSObject*, int))(vtable + 1))(this, 0);
    }

    return this;
}