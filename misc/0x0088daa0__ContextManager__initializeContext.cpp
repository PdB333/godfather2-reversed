// FUNC_NAME: ContextManager::initializeContext
void __thiscall ContextManager::initializeContext(int contextId)
{
    byte i = 0;
    g_activeContextId = contextId; // global context identifier
    if (*(int *)(this + 0x7c) != 0) { // +0x7c: numSlots
        do {
            processSlot(contextId);
            i = i + 1;
        } while ((uint)i < *(uint *)(this + 0x7c));
    }
    finalizeContextSetup(); // FUN_0088cf50
    postContextInit(contextId); // FUN_00890300
}