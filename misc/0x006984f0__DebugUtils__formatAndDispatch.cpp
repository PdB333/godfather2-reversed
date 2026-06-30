// FUNC_NAME: DebugUtils::formatAndDispatch
void DebugUtils::formatAndDispatch(SomeData* pSource, SomeConfig* pConfig) // in_EAX, unaff_ESI
{
    // pConfig[1] is a flag; if zero, just free source and return
    if (pConfig->field_4 == 0) {
        freeBuffer(pSource->field_0, pSource->field_4); // FUN_004dba00
        return;
    }

    // Allocate a formatted buffer using global format string (+0xE36EF4)
    char* tempBuf1;
    int   tempLen1;
    formatString(&tempBuf1, &tempLen1, &DAT_00e36ef4, 1, pSource->field_0, pSource->field_4); // FUN_004dbf70

    // Second formatting using pConfig's own format string
    char* tempBuf2;
    int   tempLen2;
    formatString(&tempBuf2, &tempLen2, pConfig->formatStr, pConfig->formatLen, tempBuf1, tempBuf1len); // FUN_004dbf70

    if (tempBuf2 != nullptr) {
        // Invoke callback stored in local_4 (actually passed via stack? assumed from regs)
        ((void (*)(char*))local_callback)(tempBuf2);
    }

    flushOutput(); // FUN_004dd3c0

    // Free first buffer
    freeBuffer(tempBuf1, tempBuf1len); // FUN_004dba00
    if (tempBuf1 != nullptr) {
        ((void (*)(char*))cleanup_callback)(tempBuf1); // additional cleanup? pcStack_14
    }
}