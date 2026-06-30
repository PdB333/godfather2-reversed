// FUNC_NAME: GameManager::~GameManager

void __fastcall GameManager::destructor(GameManager* this)
{
    int someMember;

    // Set primary vtable (destructor)
    this->vtable = (void**)&PTR_FUN_00e3a7a8;
    this->secondaryVtable = (void**)&PTR_LAB_00e3a840; // +0x04

    // Free large member at offset 0x11C
    heapFree(this->field_0x11C); // +0x47

    // If another object exists at +0x0C, call its destructor via vtable+4
    if (this->field_0x0C != nullptr) {
        (**(code**)(*this->field_0x0C + 4))(this);
    }

    // Global subsystem cleanup
    managerCleanup();
    audioCleanup();

    // Free member at +0x08
    someMember = this->field_0x08;
    if (someMember != 0) {
        operatorDelete(someMember);
        heapFree(someMember);
    }

    // Free and nullify member at +0x20, clear +0x24
    if (this->field_0x20 != 0) {
        this->field_0x24 = 0;
        heapFree(this->field_0x20);
        this->field_0x20 = 0;
    }

    // Call destructor of object at +0x28 via vtable+0x0C
    (**(code**)(*this->field_0x28 + 0x0C))();

    // More subsystem cleanup
    physxCleanup();
    renderCleanup();
    inputCleanup();

    // Switch to different secondary vtable before purecall
    this->secondaryVtable = (void**)&PTR_LAB_00e3a844; // +0x04
    g_gameManagerSingleton = 0; // DAT_012234b8

    // Set primary vtable to purecall to prevent double deletion
    this->vtable = (void**)&PTR___purecall_00e3a738;
}