// FUNC_NAME: Engine::setConfig
void __thiscall Engine::setConfig(void* this) {
    // Retrieve vtable from global factory
    void** vtable = (void**)FUN_009c8f80();
    // Local config struct: {2, 16, 0}
    int config[3];
    config[0] = 2;    // e.g., mode index
    config[1] = 0x10; // e.g., width or flag (16)
    config[2] = 0;    // e.g., depth or reserved
    // Call first virtual function
    typedef void (__thiscall *ConfigFunc)(void*, int*);
    ((ConfigFunc)vtable[0])(this, config);
}