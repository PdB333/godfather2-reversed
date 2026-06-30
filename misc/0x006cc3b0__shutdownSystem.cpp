// FUNC_NAME: shutdownSystem
void shutdownSystem(void)
{
    // Global flag indicating if the subsystem is initialized
    if (g_initialized) {
        // Local struct to pass to the reset function
        // The struct layout (guessed):
        //   +0x00: uint32 (copied from g_someValue)
        //   +0x04: uint32 (cleared to 0)
        //   +0x08: uint8  (cleared to 0)
        struct {
            uint32 field0;  // +0x00
            uint32 field4;  // +0x04
            uint8  field8;  // +0x08
        } localStruct;

        localStruct.field0 = g_someValue;  // DAT_0112a820
        localStruct.field4 = 0;
        localStruct.field8 = 0;

        // Call the subsystem-specific reset/release function
        resetSubsystem(&localStruct, 0);

        // Mark subsystem as uninitialized
        g_initialized = false;
    }
    return;
}