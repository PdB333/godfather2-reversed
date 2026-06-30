// FUNC_NAME: EngineManager::activate
void EngineManager::activate(void)
{
    // uVar1: handle or result from first virtual function
    int handle = (*(int (__thiscall **)(int))(*(int *)0x01219a70 + 4))(0x01219a70);
    *(int *)0x01219a78 = convertHandle(handle);  // FUN_0060d740

    (*(void (__thiscall **)(int))(*(int *)0x01219a70 + 0x10))(0x01219a70);

    *(int *)0x01219a74 = (int)&g_currentManager;  // DAT_012058ec -> current manager pointer
    g_managerCounter++;  // DAT_012058f8
    g_currentManager = (int)&s_managerInstance;  // DAT_012058ec = &DAT_01219a70
    *(int *)0x01219a7c = g_managerCounter;  // store counter
}