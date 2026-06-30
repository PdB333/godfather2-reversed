// FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x00716ce0
// Destructor pattern: sets vtable to derived class, cleans up member at offset 0x10, then sets vtable to base class
void __fastcall SomeClass::~SomeClass(undefined4 *this)
{
    // Set vtable to derived class's vtable (ensures virtual calls during destruction)
    *this = (undefined4 *)&PTR_FUN_00d61adc;

    // If member pointer at offset 0x10 (this[4]) is non-null, destroy it
    if (this[4] != 0) {
        // Call destructor for the member located at this+0x10
        FUN_004daf90(this + 4);
    }

    // Set vtable to base class's vtable (post-destruction cleanup)
    *this = (undefined4 *)&PTR_LAB_00d61acc;
    return;
}