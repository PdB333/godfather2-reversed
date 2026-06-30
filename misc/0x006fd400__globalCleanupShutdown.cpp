// FUNC_NAME: globalCleanupShutdown
void globalCleanupShutdown(void)
{
    // Global object pointer at 0x0112a9f4
    void* globalObject = *(void**)0x0112a9f4;
    if (globalObject != (void*)0) {
        // Call the first virtual function (vtable entry 0) with argument 1
        // This is likely a shutdown/cleanup method
        ((void (*)(int))(*((int**)globalObject)[0]))(1);
    }
}