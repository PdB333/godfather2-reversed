// FUNC_NAME: PlayerWallCoverSM::exitCover
void __fastcall PlayerWallCoverSM::exitCover(int this)
{
    // Notify state machine manager (g_stateMachineManager) about state exit
    (*(void (__thiscall*)())(*(int*)g_stateMachineManager + 0x28))();

    // Clear cover flags: bits 0 and 1 in uint16 at this+0x68
    *(uint16*)(this + 0x68) &= 0xFFFC;

    // Finalize cover transition (calls helper function)
    FUN_005c1880();
}