// FUNC_NAME: EARS::Framework::InitSubsystem
void EARS::Framework::InitSubsystem(void* context)
{
    // Initialize global state (engine-level setup)
    InitGlobalState();
    
    // Initialize per-context object (e.g., manager, session, or device)
    InitPerContext(context);

    return;
}