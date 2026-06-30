// FUNC_NAME: runGameStartupInit
// Function at 0x00420ff0: Part of the game's startup sequence. Calls two initialization routines.
void runGameStartupInit(void)
{
    // Call first initialization function (address 0x00421010)
    initEngineSubsystem1();

    // Call second initialization function (address 0x009c8eb0)
    initEngineSubsystem2();
}