// FUNC_NAME: getScreenDimensions

void getScreenDimensions(int* outData)
{
    int* pWindowHandle;
    int* pDeviceData;
    int globalValue;

    // Check if the window manager is valid and not a sentinel value
    pWindowHandle = *(int**)(DAT_012233a0 + 4);
    if ((pWindowHandle != (int*)0) && (pWindowHandle != (int*)0x1f30))
    {
        // Get the rendering device or display object
        pDeviceData = (int*)FUN_00471610();  // likely getRenderDevice()
        globalValue = _DAT_00d5780c;        // global constant (e.g., screen height or bit depth)

        outData[0] = *(pDeviceData + 0x30 / 4);  // +0x30: likely width or left
        outData[1] = *(pDeviceData + 0x34 / 4);  // +0x34: temporarily stored but overwritten
        outData[2] = *(pDeviceData + 0x38 / 4);  // +0x38: likely height or right
        outData[3] = globalValue;                 // +0x00: global constant
        outData[1] = 0;                          // Force second element to 0 (unknown reason)
        return;
    }

    // Fallback: zero out all output
    outData[0] = 0;
    outData[1] = 0;
    outData[2] = 0;
    outData[3] = 0;
}