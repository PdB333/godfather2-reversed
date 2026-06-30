// FUNC_NAME: AudioDataManager::initialize
void __thiscall AudioDataManager::initialize(void *this, void *unusedParam2, uint sampleRate, uint bufferSize, void *unusedParam5, int *sequenceCounter, const char *debugName)
{
    char *tempBuffer;
    uint someConstant;
    int iVar3;
    int *piVar4;

    g_audioSampleRate = sampleRate;
    g_audioBufferSize = bufferSize;
    someFunction();
    tempBuffer = g_currentDebugContext;
    g_currentDebugContext = &g_debugBuffer;  // +0x0? (DAT_0119d0d0)
    g_debugBufferPtr = &g_debugBuffer;       // global DAT_0120568c

    if (g_mutexHandle == 0) {
        iVar3 = allocateMemory(200, 0);      // FUN_005c4410
        if (iVar3 == 0) {
            g_mutexHandle = 0;
        } else {
            g_mutexHandle = createMutex();   // FUN_005c3070
        }
        initMutexSystem();                   // FUN_005c31d0
    }

    piVar4 = (int *)getProfilerObject(g_mutexHandle);  // FUN_005c3df0
    if (piVar4 != NULL) {
        (*(void (__thiscall **)(const char *, uint))(piVar4[0] + 8))(debugName, 0);  // virtual call: setName(debugName, 0)
    }

    g_logMode = g_defaultLogMode;           // DAT_00f17628 = DAT_00e2b118
    *sequenceCounter += 1;
    *(int *)((char *)this + 0x14) = *sequenceCounter;  // this->sequenceNum = *sequenceCounter

    someConstant = g_globalConstant;        // DAT_011260b4
    piVar4 = (int *)(*(int *)(g_logSystem + 0x14));     // current stack pointer in log system
    **(int **)(g_logSystem + 0x14) = (int)&s_logEntryVtable1;  // PTR_LAB_0112611c
    *piVar4 = *piVar4 + 4;
    *(int *)*piVar4 = *sequenceCounter;
    *piVar4 = *piVar4 + 4;
    *(uint *)*piVar4 = someConstant;
    *piVar4 = *piVar4 + 4;

    processLogEntry(g_logSystem + 0x14, debugName);   // FUN_005c5c40

    *(int *)((char *)this + 0x14) = 0;  // clear sequence number
    someConstant = g_globalConstant;
    piVar4 = (int *)(*(int *)(g_logSystem + 0x14));
    **(int **)(g_logSystem + 0x14) = (int)&s_logEntryVtable1;
    *piVar4 = *piVar4 + 4;
    *(int *)*piVar4 = 0;
    *piVar4 = *piVar4 + 4;
    *(uint *)*piVar4 = someConstant;
    *piVar4 = *piVar4 + 4;

    piVar4 = (int *)(*(int *)(g_logSystem + 0x14));
    **(int **)(g_logSystem + 0x14) = (int)&s_logEntryVtable2;  // PTR_LAB_011260e0
    *piVar4 = *piVar4 + 4;
    *(int *)*piVar4 = *sequenceCounter;
    *piVar4 = *piVar4 + 4;

    g_debugBufferPtr = NULL;             // DAT_0120568c = 0
    g_currentDebugContext = tempBuffer;  // restore previous context

    switch (g_audioMode) {               // DAT_01205698
    case 0:
        g_logMode = g_logMode0;          // DAT_00e445a4
        break;
    case 1:
    case 2:
        g_logMode = g_logMode1or2;       // DAT_00e445a0
        break;
    case 3:
        g_logMode = g_logMode3;          // DAT_00e2b294
        break;
    }
}