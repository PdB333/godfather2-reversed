// FUNC_NAME: SomeBaseClass::~SomeBaseClass
// Destructor: releases owned pointer at offset +0x04, then sets vtable to base destructor stub.
void __thiscall SomeBaseClass::~SomeBaseClass(uint* this)
{
    // Check if the owned pointer at offset 0x04 is non-null
    if (this[1] != 0) {
        // Call a deallocation/release function on the pointer's address (likely to free memory)
        // FUN_004daf90 is probably MemoryManager::deallocate or similar
        MemoryManager::deallocate(&this[1]);
    }
    // Set vtable pointer to the base class's destructor vtable stub (global symbol)
    // This ensures the object is treated as its base type for further destruction
    this[0] = (uint)&PTR_LAB_00e2f0c0;
}