// FUNC_NAME: Session::Session
// Function address: 0x008e86c0
// This is a constructor for a session object (likely derived from NetSession or similar).
// It sets up virtual function table pointers for multiple base classes and then performs cleanup
// of child objects before reassigning vtables to base class pointers.
// Offsets: 0x0 = vtable ptr, 0x3C (0xF*4) = base1 vtable, 0x48 (0x12*4) = base2 vtable,
// 0x50 (0x14*4) = base3 vtable, 0x54 (0x15*4) = base4 vtable, 0x58 (0x16*4) = base5 vtable,
// 0x180 (0x60*4) = base6 vtable. Cleanup at +0x194 (0x65*4) and +0x19C (0x67*4) likely pointers.

void __thiscall Session::constructor(Session *this)
{
    // Set most-derived vtable
    this->vfptr = (SessionVtbl *)&PTR_FUN_00d80998;          // +0x00
    this->baseVtbl1 = (SessionBase1Vtbl *)&PTR_LAB_00d80988;  // +0x3C (offset 0xF)
    this->baseVtbl2 = (SessionBase2Vtbl *)&PTR_LAB_00d80984;  // +0x48 (offset 0x12)
    this->baseVtbl3 = (SessionBase3Vtbl *)&PTR_LAB_00d80980;  // +0x50 (offset 0x14)
    this->baseVtbl4 = (SessionBase4Vtbl *)&PTR_LAB_00d80920;  // +0x54 (offset 0x15)
    this->baseVtbl5 = (SessionBase5Vtbl *)&PTR_LAB_00d808b8;  // +0x58 (offset 0x16)
    this->baseVtbl6 = (SessionBase6Vtbl *)&PTR_LAB_00d80898;  // +0x180 (offset 0x60)

    // Cleanup child objects before constructing base classes
    if (this->childObject1 != (void *)0x0) {                   // +0x19C (offset 0x67)
        FUN_004daf90(this->childObject1);                     // operator delete or destructor
    }
    if (this->childObject2 != (void *)0x0) {                   // +0x194 (offset 0x65)
        FUN_004daf90(this->childObject2);
    }

    // Reassign vtables to base class versions (construction chain)
    this->baseVtbl6 = (SessionBase6Vtbl *)&PTR_LAB_00d71bdc;  // +0x180
    this->vfptr = (SessionVtbl *)&PTR_FUN_00d80008;           // +0x00
    this->baseVtbl1 = (SessionBase1Vtbl *)&PTR_LAB_00d7fff8;  // +0x3C
    this->baseVtbl2 = (SessionBase2Vtbl *)&PTR_LAB_00d7fff4;  // +0x48
    this->baseVtbl3 = (SessionBase3Vtbl *)&PTR_LAB_00d7fff0;  // +0x50
    this->baseVtbl4 = (SessionBase4Vtbl *)&PTR_LAB_00d7ff90;  // +0x54
    this->baseVtbl5 = (SessionBase5Vtbl *)&PTR_LAB_00d7ff28;  // +0x58

    // Call common initialization (likely base class constructor or setup)
    FUN_0046ea20();
    return;
}