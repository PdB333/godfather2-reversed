// FUNC_NAME: SomeDerivedClass::SomeDerivedClass
void __fastcall SomeDerivedClass::SomeDerivedClass(SomeDerivedClass *this)
{
    // Set vtable pointer at offset 0
    *(void **)this = &PTR_FUN_00d744c4; // vtable for SomeDerivedClass

    // Initialize additional function pointers at offsets 0x3C and 0x48
    *(void **)((char *)this + 0x3C) = &PTR_LAB_00d744b4; // likely a virtual method or callback
    *(void **)((char *)this + 0x48) = &PTR_LAB_00d744b0; // another virtual method or callback

    // Call base class constructor or initializer
    FUN_0046c640(); // likely BaseClass::BaseClass() or some initialization routine
}