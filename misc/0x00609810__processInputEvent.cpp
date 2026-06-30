// FUNC_NAME: processInputEvent
void processInputEvent(uint keyCode)
{
    // Compute flags from keyCode: bit1 from (keyCode>>3)&2, bit0 from (keyCode&0xf)!=0
    uint flags = (keyCode >> 3 & 2) | (uint)((keyCode & 0xf) != 0);

    // Look up device entry if device count is valid (< 0x1000)
    // g_deviceTable is an array of 0x38-byte structures, g_deviceCount is the number of entries
    DeviceEntry* deviceEntry = nullptr;
    if (g_deviceCount < 0x1000) {
        deviceEntry = &g_deviceTable[g_deviceCount];
    }

    // If device type is 0x1a (26) or 0x1d (29), set an additional flag (bit2)
    if (deviceEntry != nullptr) {
        int deviceType = *(int*)((char*)deviceEntry + 8); // +0x08: device type field
        if (deviceType == 0x1a || deviceType == 0x1d) {
            flags |= (keyCode >> 3 & 4);
        }
    }

    // Dispatch to the global input manager's vtable method at offset 0xac
    // Arguments: this=g_inputManager, arg1=1, arg2=&g_eventData, arg3=flags, arg4=g_someGlobal1, arg5=g_someGlobal2, arg6=g_someGlobal3
    (**(code**)(*(int*)g_inputManager + 0xac))(g_inputManager, 1, &g_eventData, flags, g_someGlobal1, g_someGlobal2, g_someGlobal3);
}