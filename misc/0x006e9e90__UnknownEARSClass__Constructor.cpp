// FUNC_NAME: UnknownEARSClass::Constructor
// Address: 0x006e9e90
// Role: Constructor for an EARS-derived class with multiple inheritance; sets up vtables and initializes member pointers.

void __fastcall UnknownEARSClass::Constructor(UnknownEARSClass* this) {
    // Set virtual function table for primary class
    this->vtable = &PRIMARY_VTABLE; // +0x00: PTR_FUN_00d5fcd8
    // Set vtables for secondary base classes
    this->vtable2 = &SECONDARY_VTABLE_1; // +0x3C (offset 15)
    this->vtable3 = &SECONDARY_VTABLE_2; // +0x48 (offset 18)
    this->vtable4 = &SECONDARY_VTABLE_3; // +0x50 (offset 20)

    // Call base class constructor
    BaseClassConstructor(this); // FUN_006e9760

    // Notify some global manager of object creation
    notifyObjectCreation(&GLOBAL_OBJECT_COUNTER); // FUN_004086d0

    // Release previously allocated components (likely cleanup during reinitialization)
    if (this->componentA != nullptr) { // +0x98 (offset 38)
        freeMemory(&this->componentA); // FUN_004daf90
    }
    if (this->componentB != nullptr) { // +0x64 (offset 25)
        freeMemory(&this->componentB); // FUN_004daf90
    }

    // Update vtable for secondary base class to a different one (runtime type adjustment)
    this->vtable4 = &SECONDARY_VTABLE_4; // +0x50: PTR_LAB_00e32854

    // Finalize initialization (e.g., enable self-references)
    finalizeConstruction(); // FUN_0046c640
}