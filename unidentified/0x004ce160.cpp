// FUN_NAME: SimObject::SimObject
void __thiscall SimObject::SimObject(SimObject *this) {
    // Set vtable pointer to this class's vtable (at 0x00e36c60)
    this->vtable = (void **)&PTR_FUN_00e36c60;
    // Call base class constructor / initialization sequence
    this->constructSub1(); // FUN_004ce530
    this->constructSub2(); // FUN_004cebd0
    this->constructSub3(); // FUN_004083d0
}