// FUNC_NAME: FatalErrorHandler::handleFatalError
void __fastcall FatalErrorHandler::handleFatalError(FatalErrorHandler* this, unsigned int errorCode)
{
    // +0x50: pointer to crash recovery context (jmp_buf + error code storage)
    CrashRecoveryContext* recovery = *(CrashRecoveryContext**)((char*)this + 0x50);
    if (recovery != NULL)
    {
        // +0x44: error code field in recovery context
        recovery->errorCode = errorCode;
        // +0x4: jmp_buf buffer (after possibly a signature or flags)
        longjmp(&recovery->jumpBuffer, 1);
    }
    // No recovery context: call virtual function at vtable offset 0x28 (slot 10)
    // This is typically a cleanup/abort handler
    (*(void (__thiscall**)(FatalErrorHandler*))(*(void**)((char*)this + 0x10) + 0x28))(this);
    _exit(1);
}