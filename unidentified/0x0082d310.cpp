// FUN_0082d310: UnknownClass::UnknownClass
// Constructor for a class with two-stage initialization, setting vtable and secondary data pointer.

void __fastcall UnknownClass::UnknownClass(UnknownClass *this) {
    // Set the primary vtable pointer at +0x00
    *this = (UnknownClass *)&PTR_FUN_00d738c0;
    
    // Call base class constructor or early initialization (likely sets up core object fields)
    unknownBaseInit((int)this);
    
    // Set a secondary pointer at offset 0x30 (param_1[0xc])
    *(int *)((char *)this + 0x30) = (int)&PTR_LAB_00e32854;
    
    // Call second initialization function (may set up subclass-specific data)
    unknownSecondaryInit((int)this);
    
    return;
}