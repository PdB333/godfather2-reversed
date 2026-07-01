// FUNC_NAME: GameManager::constructor
void __thiscall GameManager::constructor() {
    // Set base class vtable
    this->vtable = (void*)&PTR_FUN_00d82d2c; // +0x00: base vtable pointer

    // Call base constructor (likely sets up base members)
    GameManagerBase::constructor(); // FUN_00906d50

    // Initialize sub-object at offset 4
    ((SubObject*)&this->field_4)->initialize(); // FUN_009c8f10

    // Override vtable with derived class vtable
    this->vtable = (void*)&PTR_LAB_00d82940; // +0x00: derived vtable pointer

    // Global initialization flag
    g_gameManagerInitialized = 0; // DAT_01129888
}