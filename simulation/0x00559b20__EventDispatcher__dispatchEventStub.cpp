// FUNC_NAME: EventDispatcher::dispatchEventStub
void __cdecl EventDispatcher::dispatchEventStub(uint param_1, uint param_2, uint param_3, uint param_4)
{
    // 0x00559b20 - Minimal event dispatch stub
    // Calls common initialization (FUN_00557e20) then full handler (FUN_00c0a110)
    FUN_00557e20(); // Initialize event context / internal state
    FUN_00c0a110(param_1, param_2, param_3, param_4); // Forward to actual event handler
}