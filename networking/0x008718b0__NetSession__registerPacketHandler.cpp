// FUNC_NAME: NetSession::registerPacketHandler
void __fastcall NetSession::registerPacketHandler(int thisPtr)
{
    // this+0x4: handler ID (int)
    // this+0x8: handler data buffer (void*)
    // &DAT_00e54120: static callback table or function pointer array
    // 1: enable flag (likely 1 = start, 0 = stop)
    FUN_00851440(*(int*)(thisPtr + 4), (void*)(thisPtr + 8), &DAT_00e54120, 1);
}