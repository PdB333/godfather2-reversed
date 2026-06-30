// FUNC_NAME: EARS::Framework::GameManager::InitHandles
void __fastcall GameManager::InitHandles(GameManager *this)
{
    int handle1;
    int handle2;

    handle1 = CreateFirstHandle();                      // FUN_0060a380
    this->field_0x10 = handle1;                         // +0x10: handle to resource A
    handle2 = CreateSecondHandle(PTR_DAT_0110a37c);     // FUN_0060a2e0
    this->field_0x14 = handle2;                         // +0x14: handle to resource B
    InitSubsystem();                                    // FUN_006127d0
    return;
}