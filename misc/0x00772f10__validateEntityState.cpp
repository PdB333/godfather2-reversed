// FUNC_NAME: validateEntityState
void __fastcall validateEntityState(int entity)
{
    // +0xB0: state/status field
    int state = *(int*)(entity + 0xB0);
    if (state != 0 && state != 0x48) // 0x48 = valid initialized state
    {
        // Invalid state; report error
        FUN_00625050(0xB47BB605, 0);
    }
}