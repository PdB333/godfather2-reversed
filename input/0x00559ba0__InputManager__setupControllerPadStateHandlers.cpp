// FUNC_NAME: InputManager::setupControllerPadStateHandlers
void InputManager::setupControllerPadStateHandlers(void)
{
    // Structure used to register handlers for controller pad events.
    // Offsets: +0x00: data pointer (e.g., state table), +0x04: padConnectHandler, +0x08: padDisconnectHandler, +0x0C: padInputHandler
    struct PadStateHandlers {
        void* data;          // +0x00
        code* connectHandler;   // +0x04
        code* disconnectHandler; // +0x08
        code* inputHandler;      // +0x0C
    } handlers;

    // Initialize for controller slot 0 (index 0x1e = 30?) with first set of handlers.
    handlers.data = (void*)&LAB_00559a20;          // likely static pad state data
    handlers.connectHandler = FUN_00559b20;         // connect callback
    handlers.disconnectHandler = FUN_00559a40;      // disconnect callback
    handlers.inputHandler = FUN_00559ac0;            // input processing callback

    // Register handlers for (previousState=0x1e, nextState=0xffffffff) – possibly "connected" state
    FUN_00a708f0(&handlers, 0x1e, 0xffffffff);      // registerPadStateHandlers(padState, prevState, nextState)

    // Reinitialize for another controller slot (index -1 = all?) with alternative handlers.
    handlers.data = (void*)&LAB_00559a20;           // same data pointer
    handlers.connectHandler = FUN_00559b50;          // different connect callback
    handlers.disconnectHandler = FUN_00559a70;       // different disconnect callback
    handlers.inputHandler = FUN_00559af0;            // different input callback

    // Register handlers for (previousState=0xffffffff, nextState=0x1e) – possibly "disconnected" state
    FUN_00a708f0(&handlers, 0xffffffff, 0x1e);
    return;
}