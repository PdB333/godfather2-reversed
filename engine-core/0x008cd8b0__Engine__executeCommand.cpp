// FUNC_NAME: Engine::executeCommand

void __thiscall Engine::executeCommand(void *this, int param1)
{
    // Engine singleton retrieved via a static getter
    Engine *engine = getEngineInstance();
    
    // Command parameters: type = 2, size = 0x10, flags = 0
    struct CommandParams params;
    params.type = 2;      // +0x00: command type
    params.size = 0x10;   // +0x04: data size
    params.flags = 0;     // +0x08: flags
    
    // Call virtual function at offset 0 of engine object
    (*(void (**)(void *, CommandParams *))engine->vtable[0])(this, &params);
}