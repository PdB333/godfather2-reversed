// FUNC_NAME: initializeEngineSubsystem
void initializeEngineSubsystem(uint32_t param_1)
{
    void** vtablePtr;
    uint32_t output[3]; // 12-byte output buffer

    vtablePtr = (void**)getSingletonInstance(); // FUN_009c8f80
    output[0] = 0;
    output[1] = 0;
    output[2] = 0;

    // Call first virtual function (likely an init method) on the singleton
    ((void (*)(uint32_t, uint32_t*))(*vtablePtr))(param_1, output);
}