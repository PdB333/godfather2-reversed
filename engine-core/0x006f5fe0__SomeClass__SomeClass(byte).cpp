// FUNC_NAME: SomeClass::SomeClass(byte)
// Address: 0x006f5fe0
// Constructor for an object with two vtable pointers (likely multiple inheritance or base class + interface).
// param_1: this pointer
// param_2: flag indicating whether this is a heap-allocated object (if bit 0 set, calls deallocation function after setup).

undefined4* __thiscall SomeClass::SomeClass(undefined4* this, byte flag) {
    // Set vtable pointer at offset 0x00
    *this = &PTR_FUN_00d60710;
    
    // Set vtable pointer at offset 0x08 (second base/interface)
    this[2] = &PTR_LAB_00d6070c;
    this[2] = &PTR_LAB_00d60708;    // Overwrites previous? Possibly a decompilation artifact; likely intended for offset 0x04 and 0x08.
    
    // Reset global initialization flag/counter
    DAT_01129974 = 0;
    
    // Call shared initialization function
    FUN_0049c640();
    
    // If flag indicates heap allocation, call cleanup/deallocation function
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this);
    }
    
    return this;
}