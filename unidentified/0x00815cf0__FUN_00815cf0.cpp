// FUNC_NAME: SomeManager::SomeManager
void __fastcall SomeManager::SomeManager(SomeManager *this)
{
    // Store this pointer in global singleton
    g_pSomeManager = this;

    // Set vtable pointer
    this->vtablePtr = &SomeManager_vtable;

    // Initialize members to 0
    this->field_0x04 = 0;   // +0x04
    this->field_0x08 = 0;   // +0x08
    this->field_0x0C = 0;   // +0x0C
    this->field_0x10 = 0;   // +0x10
    this->field_0x14 = 0;   // +0x14
    this->field_0x18 = 0;   // +0x18
    this->field_0x1C = 0;   // +0x1C

    // Set reference count (or some state) to 2
    this->field_0x1C = this->field_0x1C + 1;
    this->field_0x1C = this->field_0x1C + 1;
}