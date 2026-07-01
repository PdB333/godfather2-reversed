// FUNC_NAME: SomeManager::constructor
// Address: 0x0084ac90
// Likely a constructor for a singleton manager class (e.g., InputManager, AudioDataManager).
// Sets a global instance pointer, vtable, and initializes several fields to defaults.

void __thiscall SomeManager::SomeManager(SomeManager *this)
{
    // Store this instance globally for singleton access
    g_pSomeManager = this;

    // Set vtable (RTTI pointer) to the class's virtual function table
    this->vtable = &PTR_FUN_00d74d3c;

    // +0x04: byte field, set to 1 (likely a flag indicating initialization or enabled)
    *(byte *)((int)this + 0x04) = 1;

    // +0x08: int field, initialized to 0
    this->field_0x08 = 0;

    // +0x0C: int field, initialized to 0
    this->field_0x0C = 0;

    // +0x10: int field, initialized to 0
    this->field_0x10 = 0;
}