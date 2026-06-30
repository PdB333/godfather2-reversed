// FUNC_NAME: EARSObject::Constructor
// Address: 0x0046b400
// Role: Constructor for an EARS engine base object. Sets the vtable pointer and invokes a base class initializer.

class EARSObject {
public:
    void** vtable; // +0x00 Virtual function table pointer
    // Additional members follow...
};

__thiscall EARSObject* EARSObject::Constructor() {
    // Set virtual table to this class's vtable (at 0x00e326b4)
    this->vtable = &PTR_FUN_00e326b4;
    // Call base class constructor (likely EARSObjectBase::Constructor at 0x0043e2e0)
    FUN_0043e2e0(this);
    return this;
}