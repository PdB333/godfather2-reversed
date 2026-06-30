// FUNC_NAME: BaseGameObject::Constructor
// Function at 0x006d9e60: Constructor for a class with multiple inheritance and optional cleanup.
// Sets up primary and secondary vtable pointers (offsets 0x00, 0x3C, 0x48, 0x50) then calls base constructor.
// If param_2 has bit0 set, calls a cleanup function with size 0x90 (possibly deleting or debugging).

class BaseGameObject {
public:
    void* vtable;                     // +0x00 primary vtable
    // padding/members up to +0x3C
    void* vtableSecondary1;           // +0x3C secondary vtable 1
    // more members...
    void* vtableSecondary2;           // +0x48 secondary vtable 2
    void* vtableSecondary3;           // +0x50 secondary vtable 3 (set twice)
};

void __thiscall BaseGameObject::Constructor(BaseGameObject* this, byte param_2) {
    // Set primary vtable
    this->vtable = &PTR_FUN_00e32b30;

    // Set secondary vtable pointers (multiple inheritance)
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00e32b50;   // vtable for base B1
    *(void**)((char*)this + 0x48) = &PTR_LAB_00e32b60;   // vtable for base B2
    *(void**)((char*)this + 0x50) = &PTR_LAB_00e32b64;   // vtable for base B3 (first assignment)
    *(void**)((char*)this + 0x50) = &PTR_LAB_00e32b54;   // re-assign vtable for base B3 (corrected? )

    // Call base class constructor (likely another EARS class)
    FUN_0046c640();   // probably BaseClass::Constructor(this)

    // If cleanup flag is set, call a function that takes this and object size (0x90)
    if ((param_2 & 1) != 0) {
        FUN_0043b960(this, 0x90);   // likely operator delete or debug deallocation
    }
}