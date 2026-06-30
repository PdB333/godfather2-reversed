// FUNC_NAME: SingletonManager::staticInit
void SingletonManager::staticInit()
{
    // Call factory function from vtable at offset 0x4
    int result = (*(int (**)(void))(*(int**)g_singletonVTable)[1])();  // +0x4

    // Allocate or create singleton instance using result
    g_singletonInstance = allocateMemory(result);  // FUN_0060d740

    // Call second vtable function at offset 0x10
    (*(void (**)(void))(*(int**)g_singletonVTable)[4])();  // +0x10

    // Assign global reference
    g_someGlobal1 = DAT_012058ec;  // store address of vtable pointer
    g_refCount = g_refCount + 1;   // increment global counter
    g_someGlobal2 = g_refCount;    // assign count as ID
}