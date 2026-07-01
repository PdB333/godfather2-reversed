// FUNC_NAME: GameManager::GameManager
// Address: 0x009056d0
// Constructor for game manager class. Sets vtable pointers and calls base initialization.

void __thiscall GameManager::GameManager(GameManager *this) {
    // Set primary vtable pointer at offset 0x0
    this->vtable = (void **)&PTR_FUN_00d82630; // +0x0
    // Set secondary vtable pointer at offset 0x82 (520 bytes)
    this->field_0x82 = &PTR_LAB_00d8262c; // +0x82
    // Call base class constructor (likely EARSObject or similar)
    BaseClass::constructor((BaseClass *)this); // FUN_00905600
    // Additional initialization for this class
    extraInitialization(); // FUN_00412230
}