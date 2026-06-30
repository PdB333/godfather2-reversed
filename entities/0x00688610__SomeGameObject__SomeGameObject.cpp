// FUNC_NAME: SomeGameObject::SomeGameObject

// Constructor for a game object. Address: 0x00688610
// Initializes vtable and various fields.
// Parameters:
//   this - pointer to the object being constructed
//   someParam - parameter passed to base class constructor FUN_007268d0

SomeGameObject * __thiscall SomeGameObject::SomeGameObject(SomeGameObject *this, void *someParam)
{
    int uVar1;
    
    // Call base class constructor (likely)
    FUN_007268d0(someParam);
    
    uVar1 = DAT_00d58d0c;  // Some global value
    
    // Set virtual function table pointer (vtable at offset 0)
    *this = &PTR_FUN_00d58ce0;
    
    // Initialize function pointer tables or callback lists
    this[0xf] = &PTR_LAB_00d58cd0;  // +0x3C (15*4)
    this[0x12] = &PTR_LAB_00d58ccc; // +0x48
    this[0x14] = &PTR_LAB_00d58cc0; // +0x50
    
    // Initialize numeric fields
    this[0x50] = 0;  // +0x140
    this[0x51] = 0;  // +0x144
    this[0x52] = uVar1; // +0x148
    *(unsigned char *)((unsigned char *)this + 0x54) = 0; // +0x150? careful: offset in bytes
    this[0x53] = 0;  // +0x14C
    
    return this;
}