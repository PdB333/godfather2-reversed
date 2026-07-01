// Xbox PDB: EARS_Vehicles_WhiteboxCar_RegisterBoneMods
// FUNC_NAME: InputDeviceManager::initJoyWindows

// 0x00875be0 - Initializes four joystick input windows (FL,FR,KL,KR) for calibration or filtering
void __thiscall InputDeviceManager::initJoyWindows(uint32_t *thisPtr)
{
    int iVar1;
    uint32_t uVar2;
    uint32_t *windowData;
    uint32_t local_14;
    char *windowNames[4];
    
    // Window identifiers: FrontLeft, FrontRight, RearLeft, RearRight (likely for 4-joystick configuration)
    windowNames[0] = "JO_window_FL";
    windowNames[1] = "JO_window_FR";
    windowNames[2] = "JO_window_KL"; // "KL" = HinterLinks? (German) or Rear Left
    windowNames[3] = "JO_window_KR"; // "KR" = Rear Right
    
    uVar2 = 0;
    windowData = thisPtr + 0x2f5; // Pointer to first window data block (748 bytes after this)
    do {
        local_14 = 0;
        // Virtual call at vtable+0x94: Retrieve configuration value associated with window name
        (*(thisPtr[0] + 0x94))(&local_14, windowNames[uVar2]);
        iVar1 = g_defaultJoyWindowValue; // 0x00d5780c - default calibration constant
        
        // Clear the first 7 ints of the window data block (indices -5 to +1)
        windowData[-2] = 0;
        windowData[-3] = 0;
        windowData[-4] = 0;
        windowData[-5] = 0;
        windowData[1] = 0;
        windowData[0] = 0;
        windowData[-1] = 0;
        
        // Set 4 consecutive ints to the default value (probably buffer or threshold)
        windowData[2] = iVar1;
        windowData[5] = iVar1;
        windowData[4] = iVar1;
        windowData[3] = iVar1;
        windowData[6] = 0; // Extra zero
        
        // Initialize window data block: address = windowData - 5, size = local_14 >> 2 (quarter of retrieved value)
        // Parameters: (void* buffer, uint32_t elementCount, uint32_t windowId, uint32_t flags...)
        initializeJoyWindowData(windowData - 5, local_14 >> 2, 9, 0, 0, 0, 0);
        
        uVar2 = uVar2 + 1;
        windowData = windowData + 0xc; // Move to next window (12 ints = 48 bytes per window)
    } while (uVar2 < 4);
}