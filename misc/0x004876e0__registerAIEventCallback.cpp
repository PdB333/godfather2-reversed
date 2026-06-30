// FUNC_NAME: registerAIEventCallback
// Address: 0x004876e0
// Role: Registers a handler for a specific AI-related event (message ID 0x712)
// Calls: RegisterEventCallback (FUN_00483ba0) with message ID, handler function, and context
void __fastcall registerAIEventCallback(void* context)
{
    // Message ID 0x712, handler at FUN_00487620, context pointer passed along
    RegisterEventCallback(0x712, &handleAIEvent_712, context);
}