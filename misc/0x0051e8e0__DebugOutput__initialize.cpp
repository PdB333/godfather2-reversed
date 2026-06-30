// FUNC_NAME: DebugOutput::initialize

void DebugOutput::initialize(void)
{
    // Call virtual functions through the object's vtable
    // Offset 0x4: presumably getHandle() or createOutput()
    int tHandle = (*(int (__thiscall **)(DebugOutput*))(*(uint32_t*)g_pSomePtr + 4))(g_pSomePtr);
    // Convert handle to internal representation
    g_debugHandle = convertHandle(tHandle);  // FUN_0060d740

    // Offset 0x10: presumably initializeDebug()
    (*(void (__thiscall **)(DebugOutput*))(*(uint32_t*)g_pSomePtr + 0x10))(g_pSomePtr);

    // Register this singleton into a global linked list
    g_prevHead = g_head;                   // _DAT_011252dc = DAT_012058ec
    g_nextId++;                            // DAT_012058f8++
    g_head = (DebugOutput*)&g_pSomePtr;    // DAT_012058ec = &PTR_PTR_011252d8
    g_debugId = g_nextId;                  // _DAT_011252e4 = DAT_012058f8
    return;
}