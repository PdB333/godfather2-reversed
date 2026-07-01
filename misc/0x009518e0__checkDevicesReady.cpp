// FUNC_NAME: checkDevicesReady
bool checkDevicesReady(bool bUpdateIfNotReady)
{
    // Global pointers to two device objects (e.g., video and audio)
    // Offsets: +0x12 = bool ready flag, vtable+0x2c = virtual update()
    int* pDevice1 = DAT_0112fee4;  // likely video device
    int* pDevice2 = DAT_011305b4;  // likely audio device

    if (bUpdateIfNotReady) {
        // If device1 is not ready, call its update routine
        if (*(char*)(pDevice1 + 0x12) != 0) {
            (**(code**)(*pDevice1 + 0x2c))();  // virtual update()
        }
        // If device2 is not ready, call its update routine
        if (*(char*)(pDevice2 + 0x12) != 0) {
            (**(code**)(*pDevice2 + 0x2c))();  // virtual update()
        }
    }

    // Return true only if both devices are ready (zero at +0x12)
    return (*(char*)(pDevice1 + 0x12) == 0) && (*(char*)(pDevice2 + 0x12) == 0);
}