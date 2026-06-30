// FUNC_NAME: GodfatherGameManager::sendEvent
void GodfatherGameManager::sendEvent(int param2, int param3) {
    // Build event structure on stack
    // Field layout: [type(2)] [param2] [flags(0)] [cmd(3)] [data(param3)]
    int eventBlock[5];
    eventBlock[0] = 2;       // +0x00: event type constant
    eventBlock[1] = param2;  // +0x04: first argument
    eventBlock[2] = 0;       // +0x08: flags (unused)
    eventBlock[3] = 3;       // +0x0C: command ID (3)
    eventBlock[4] = param3;  // +0x10: second argument

    // Get the global event dispatcher singleton
    void** dispatcher = (void**)FUN_009c8f80();
    // Call the first virtual method on the dispatcher, passing a pointer
    // to the command ID field (offset +0x0C)
    ((void (*)(void*, int*))(*dispatcher))(this, &eventBlock[3]);
}