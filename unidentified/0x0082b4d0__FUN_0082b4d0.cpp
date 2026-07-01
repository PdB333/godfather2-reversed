// FUNC_NAME: SomeClass::SomeClass
void __fastcall SomeClass::SomeClass(SomeClass* this) {
    // Set primary vtable pointer at offset 0x00
    this->vtable = (void*)0x00d73844; // vtable for SomeClass
    // Call base class constructor (likely first base)
    BaseClass1::BaseClass1(this); // FUN_0082b490
    // Set secondary vtable pointer at offset 0x30 (0xc * 4)
    this->base2Vtable = (void*)0x00e32854; // vtable for BaseClass2
    // Call second base class constructor
    BaseClass2::BaseClass2(this); // FUN_00821f60
}