// FUNC_NAME: AudioOutputManager::selectOutputDevice (0x0053d950)
void __fastcall AudioOutputManager::selectOutputDevice(int deviceIndex, int paramHandle)
{
    // deviceIndex passed in EAX, paramHandle passed in ECX (__fastcall)
    // Array of device descriptors at 0x01198e80, each 0x1B bytes
    // Global state at 0x0121be88 (static instance)
    // sCurrentDeviceObj (0x0121be98) and sNewDeviceObj (0x0121be9c)
    // sOutputHandle (0x0121bf2c), sDeviceIndex (0x0121bf30)
    // sActiveDevicePtr (0x012058e8), sInitHandle (0x0121bf34)

    // Store new device info
    DAT_0121be9c = (&DAT_01198e80)[deviceIndex * 0x1b];
    _DAT_0121bf2c = paramHandle;
    DAT_0121bf30 = deviceIndex;

    // If the current active output manager is the static instance at 0x0121be88,
    // release both previous device objects
    if (DAT_012058e8 == &DAT_0121be88) {
        FUN_0060a460(DAT_0121be9c);   // release newly set device object
        FUN_0060a460(DAT_0121be98);   // release previously active device object
    }

    // If an initialization handle is present, call setup with the active device object
    if (DAT_0121bf34 != 0) {
        int buffer[4] = { 0, 0, 0, 0 };  // 16-byte zeroed buffer
        FUN_0060add0(DAT_0121be98, DAT_0121bf34, buffer);  // initialize audio output
    }
}