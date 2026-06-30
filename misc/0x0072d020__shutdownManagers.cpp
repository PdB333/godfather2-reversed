// FUNC_NAME: shutdownManagers
// Function address: 0x0072d020
// Cleanup function that calls a common release routine on multiple global manager instances.
void shutdownManagers(void)
{
    // Release each global manager or singleton in a fixed order.
    // The called function (FUN_00408310) is likely a specialized deallocator or destructor
    // that handles ref counting or cleanup for these objects.
    releaseManager(&DAT_0112adb8);  // +0x0: audio manager?
    releaseManager(&DAT_0112ade8);  // +0x30: input device manager?
    releaseManager(&DAT_0112ada8);  // +0x60: font manager?
    releaseManager(&DAT_0112adc0);  // +0x90: stream manager?
    releaseManager(&DAT_0112ade0);  // +0xc0: camera manager?
    releaseManager(&DAT_0112adc8);  // +0xf0: entity data manager?
    releaseManager(&DAT_0112adf8);  // +0x120: collision cache?
    releaseManager(&DAT_0112ad9c);  // +0x150: traffic manager?
    releaseManager(&DAT_0112e0fc);  // +0x180: player manager?
    releaseManager(&DAT_0112adf0);  // +0x1b0: building manager?
    releaseManager(&DAT_0112ae00);  // +0x1e0: NPC manager?
    releaseManager(&DAT_0112add8);  // +0x210: dialog tree manager?
}