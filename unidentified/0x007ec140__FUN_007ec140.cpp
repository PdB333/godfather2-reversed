// FUNC_NAME: SomeClass::constructor
// Address: 0x007ec140
// Likely constructor for an object with embedded sub-object at offset 0x50 (0x14 * 4).
// Sets up vtable at +0x00, function table at +0x3C (0xF * 4), and another at +0x48 (0x12 * 4).
// Calls two initialization functions on sub-object at offset 0x50, then a global init.
// If param_2 has bit 0 set, calls custom deallocation with size 0x60 (used for error handling or placement).
// +0x00: vtable pointer
// +0x3C: unknown function table pointer
// +0x48: unknown function table pointer
// +0x50: embedded sub-object (size unknown, likely 0x10 = 0x60 - 0x50 = 16 bytes)

__thiscall SomeClass* SomeClass::constructor(SomeClass* this, byte param_2)
{
    // Set vtable to base class vtable
    this[0].vtable = (void**)&PTR_FUN_00d6ff90;   // +0x00
    
    // Set two function table pointers
    this[0xF].someTable = (void**)&PTR_LAB_00d6ff80;  // +0x3C
    this[0x12].anotherTable = (void**)&PTR_LAB_00d6ff7c; // +0x48
    
    // Initialize embedded sub-object at offset +0x50
    SubObject* subObj = (SubObject*)(this + 0x14); // offset 0x14 * sizeof(uint) = 0x50
    FUN_004086d0(subObj);  // probably subObj->init()
    FUN_00408310(subObj);  // probably subObj->setup()
    
    // Global initialization call
    FUN_0046c640();  // possibly engine-wide init
    
    // If the flag indicates self-allocation, attempt cleanup (likely failure rollback)
    if ((param_2 & 1) != 0) {
        // Custom sized deallocation
        FUN_0043b960(this, 0x60); // operator delete or deinit
    }
    
    return this;
}