// FUNC_NAME: Engine::sendCommand
// Function address: 0x004a72e0
// Sends a command (ID 0xB0) with parameters {2, 16, 0} to the engine singleton.
// The command function is the first virtual method of the engine object returned by FUN_009c8f80.
void Engine::sendCommand()
{
    // Get the engine singleton (pointer to object with vtable) – likely from a global or thread-local storage
    void** enginePtr = reinterpret_cast<void**>(FUN_009c8f80());
    // Command parameters: (2, 16, 0) – exact meaning depends on command ID 0xB0
    int commandParams[3];
    commandParams[0] = 2;
    commandParams[1] = 0x10;
    commandParams[2] = 0;

    // Call the first virtual function (vtable[0]) on the engine object
    // Signature: void (__thiscall*)(void* self, int commandId, void* params)
    typedef void (__thiscall *EngineCommandFunc)(void*, int, void*);
    EngineCommandFunc func = reinterpret_cast<EngineCommandFunc>(enginePtr[0]);
    func(enginePtr, 0xB0, commandParams);
}