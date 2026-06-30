// FUNC_NAME: GameManager::GameManager
GameManager* __thiscall GameManager::GameManager(GameManager* this, void* someParam)
{
    // Call base class constructor or initialization routine (param2 might be allocator/parent)
    BaseClassConstructor(someParam);  // FUN_0046c590

    // Store global pointer to this instance
    gGameManager = this;

    // Initialize virtual function table pointers and other fields
    // Offset 0x00: Primary vtable pointer
    *reinterpret_cast<void**>(this) = &GameManager_vtable_primary;  // PTR_FUN_00e3343c

    // Offset 0x3C (15*4 = 0x3C): Secondary vtable pointer
    this->field_0x3C = &GameManager_vtable_secondary1;  // PTR_LAB_00e33458

    // Offset 0x48 (18*4 = 0x48): Another vtable pointer
    this->field_0x48 = &GameManager_vtable_secondary2;  // PTR_LAB_00e33468

    // Offset 0x50 (20*4 = 0x50): Initially set to one pointer, then overwritten below
    this->field_0x50 = &GameManager_vtable_temp;  // PTR_LAB_00e33470

    // Offset 0x60 (24*4 = 0x60): Some integer/pointer from global DAT_00e2b1a4
    this->field_0x60 = DAT_00e2b1a4;

    // Offset 0x64 (25*4 = 0x64): Same value as field_0x60
    this->field_0x64 = DAT_00e2b1a4;

    // Offset 0x50 (overwritten now) – final assignment
    this->field_0x50 = &GameManager_vtable_final;  // PTR_LAB_00e3346c

    // Offset 0x70 (0x1c bytes): Boolean flag set to 1 (true) – marks object as initialized
    this->field_0x70 = 1;  // *(undefined1 *)(param_1 + 0x1c) = 1

    // Offsets 0x68 and 0x6C: Zero-initialized fields
    this->field_0x68 = 0;
    this->field_0x6C = 0;

    // Further initialization via another function
    OtherInitialization(someParam);  // FUN_00481190

    return this;
}