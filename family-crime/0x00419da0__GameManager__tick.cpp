// FUNC_NAME: GameManager::tick
void __thiscall GameManager::tick(void* timeInfo, int skipVirtualCallFlag) // param_2 = timeInfo (struct with time data), param_3 = flag to skip virtual call
{
    // DAT_00e2a850: target frame duration (maybe minimum delta time)
    // unaff_FS_OFFSET + 0x2c: TLS pointer; then offset 8 -> pointer to high-res timer data; offset 0x6c + timeInfo->field_0x18 -> actual elapsed time
    if (DAT_00e2a850 < *(float*)(*(int*)(**(int**)(*(int*)(__readfsdword(0x2C)) + 8) + 0x6C + *(int*)((char*)timeInfo + 0x18))))
    {
        FUN_00419760(timeInfo, skipVirtualCallFlag); // early return for frame limiter / late update
        return;
    }

    if ((char)skipVirtualCallFlag == '\0')
    {
        // Call virtual function at vtable offset 0x3c on object pointed to by this+0x4
        (**(code**)(**(int**)((char*)this + 4) + 0x3C))();
    }

    FUN_00419370(); // update input / controller state
    FUN_00417560(); // update game logic / physics
    char cVar1 = FUN_004166b0(); // some condition (e.g., save game ready)
    if ((cVar1 != '\0') && ((DAT_011f7430 & 1) != 0))
    {
        FUN_00614a50(); // perform auto-save or checkpoint
    }
    FUN_00418c50(); // render / UI update
    FUN_0060c8d0(0, DAT_01205334, 0xC, 0, 0, 0, 1); // memory pool allocation or audio buffer
    FUN_0060cb70(5, DAT_01205338, 0, DAT_0120533c, 0, 0xFFFF); // register resource / prefetch
    if (DAT_0120587e != '\0')
    {
        // Call virtual function at vtable offset 0xE4 on global audio manager
        (**(code**)(*DAT_01205750 + 0xE4))(DAT_01205750, 0xB4, 0); // e.g., play sound or fade
    }
    return;
}