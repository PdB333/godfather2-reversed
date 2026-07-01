// FUNC_NAME: SimManager::SimManager
void __fastcall SimManager::SimManager(int this)
{
    FUN_00924360(this);
    FUN_00923590(this);
    *(int *)(this + 0x50) = 4;         // +0x50: state/type field (4 = SIM_STATE_INIT)
    *(int *)(this + 0x68) = *(int *)0x01205214; // +0x68: pointer to global data table
    *(int *)(this + 0x64) = *(int *)0x00d87274; // +0x64: pointer to config singleton
    FUN_004c3ae0();
}