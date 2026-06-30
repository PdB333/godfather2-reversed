// FUNC_NAME: GlobalObject::constructor
// Address: 0x00455b70 - Class constructor setting up vtable and initializing base objects

void GlobalObject::constructor(GlobalObject* this) {
    // Set up the vtable for this object (first base class)
    this->vtablePtr1 = &vtable_0x00e319ac;
    // Set up second vtable pointer for multiple inheritance
    this->vtablePtr2 = &vtable_0x00e319b0;

    // Initialize base subobject at offset 0x8C (relative to this? or absolute addresses)
    FUN_004086d0(&DAT_0120ea8c);  // Likely initializes member/base at address 0x0120ea8c
    FUN_004086d0(&DAT_0120ea84);  // Another subobject
    FUN_004086d0(&DAT_01206940);  // Another subobject

    // More initialization calls
    FUN_00408310(&DAT_0120ea8c);
    FUN_00408310(&DAT_0120ea84);

    // Static initialization (no this pointer)
    FUN_004083d0();

    // Switch to a different vtable (possibly for overridden methods in final class)
    this->vtablePtr1 = &vtable_0x00e319c0;

    // Reset a global flag indicating creation status
    DAT_01223454 = 0;

    return;
}