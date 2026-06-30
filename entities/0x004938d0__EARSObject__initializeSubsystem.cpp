// FUNC_NAME: EARSObject::initializeSubsystem
void __fastcall initializeSubsystem(void* thisPtr)
{
    initializeGlobalEngineState();
    initializeMember(thisPtr);
    return;
}