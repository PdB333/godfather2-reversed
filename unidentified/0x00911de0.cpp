// Function at 0x00911de0: Initialization wrapper that triggers two key subsystem initializations.
void initGameSubsystems(void)
{
    // Calls to core initialization routines
    initCoreSystems();   // 0x0090d130
    initAudioVisual();   // 0x005c1740
}