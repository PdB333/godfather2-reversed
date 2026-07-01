// FUNC_NAME: GameEventManager::processEventLoop
void GameEventManager::processEventLoop(void* thisPtr) // likely __thiscall
{
    char isRunning; // byte
    int eventType; // 0 or 1

    // Initial setup: probably register event handlers or init the event system
    FUN_0046c710(thisPtr); // initEventManager?
    FUN_0043aff0(thisPtr, 0xbcab53d4); // registerEventHandler? (token constant)

    isRunning = FUN_0043b120(); // isEventQueueEmpty? (returns 0 if empty?)
    while (isRunning == '\0') {
        // Process next event
        FUN_0043b210(); // popNextEvent? (returns event handle)
        eventType = FUN_0043ab70(); // getEventType (returns 0 or 1)
        if (eventType == 0) {
            // Type 0: store data into global A (likely input/state)
            _DAT_00e52298 = *(undefined4*)(FUN_0043b210() + 8); // +8 offset: event payload
        }
        else if (eventType == 1) {
            // Type 1: store data into global B
            _DAT_00e5229c = *(undefined4*)(FUN_0043b210() + 8);
        }
        FUN_0043b1a0(); // processEvent (dispatch to handlers?)
        isRunning = FUN_0043b120(); // check again
    }
    // Loop ends when event queue empty (isRunning != 0)
}