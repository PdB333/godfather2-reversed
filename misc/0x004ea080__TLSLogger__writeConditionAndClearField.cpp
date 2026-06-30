// FUNC_NAME: TLSLogger::writeConditionAndClearField
void TLSLogger::writeConditionAndClearField(void* object) {
    // Read thread-local storage: FS:[0x2C] points to TLS array, offset 0x34 holds a flag value
    uintptr_t tlsArray = *(uintptr_t*)__readfsdword(0x2C); // FS:[0x2C] is pointer to TLS array
    int32_t tlsFlag = *(int32_t*)(tlsArray + 0x34);       // +0x34: per-thread conditional flag

    // Clear a field in the object based on TLS flag
    // Object has two fields: +0x04 and +0x9C (4 + 0x98)
    int32_t* fieldToClear = (int32_t*)((uintptr_t)object + (tlsFlag != 0 ? 0x9C : 4));
    *fieldToClear = 0;

    // Select the appropriate log context (dual-context system, e.g., normal vs debug)
    LogContext* logContext;
    if (tlsFlag != 0) {
        logContext = (LogContext*)DAT_012068e8; // debug/alternate context
    } else {
        logContext = (LogContext*)DAT_01206880; // default context
    }

    // Append to the log buffer: first a static format label, then the boolean value
    // logContext->writePointer (+0x14) is a pointer to the next free slot
    *(uint32_t*)(logContext->writePointer) = (uint32_t)&PTR_LAB_01124be4; // pointer to static label
    logContext->writePointer += 4;
    *(uint32_t*)(logContext->writePointer) = (uint32_t)(tlsFlag != 0);
    logContext->writePointer += 4;
}