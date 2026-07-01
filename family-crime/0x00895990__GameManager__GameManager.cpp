// FUNC_NAME: GameManager::GameManager
void __thiscall GameManager::GameManager(GameManager* this)
{
    // Set vtable pointer at offset 0
    this->vtable = (void**)&PTR_FUN_00d779e4;
    // Set member at offset 0x3C (60 bytes) – possibly a function table or event handler
    *(void**)((unsigned char*)this + 0x3C) = (void*)&PTR_LAB_00d779d4;
    // Set member at offset 0x48 (72 bytes) – similar purpose
    *(void**)((unsigned char*)this + 0x48) = (void*)&PTR_LAB_00d779d0;
    // Initialize global synchronization primitive or reference counter
    FUN_004086d0(&DAT_01218048);
    FUN_00408310(&DAT_01218048);
    // General engine subsystem initialization
    FUN_0046c640();
}