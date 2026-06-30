// FUNC_NAME: registerCommandHandler
void registerCommandHandler(void)
{
    // Registers a command handler for ID 0x7ff (likely a console command or input binding)
    // The handler function is at address 0x00483e20 (compiled as LAB_00483e20)
    registerCommandCallback(0x7ff, (void*)0x00483e20);
}