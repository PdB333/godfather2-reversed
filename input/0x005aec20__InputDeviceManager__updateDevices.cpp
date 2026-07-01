// FUNC_NAME: InputDeviceManager::updateDevices
void InputDeviceManager::updateDevices(int param_2)
{
    // unaff_ESI is this pointer (ECX)
    if (this != 0) {
        // Check if using primary input system (e.g., XInput)
        if (isUsingPrimaryInput()) {
            // Get the input manager object
            InputManager* inputMgr = getInputManager();
            // Call virtual function at offset 0x4c (likely processInput)
            inputMgr->processInput(this, param_2);
            // Process param_2 frames/devices
            for (int i = 0; i < param_2; i++) {
                processOneDevice();
            }
            finalizeUpdate(this);
            return;
        }
        // Check if using alternative input system (e.g., network/remote)
        if (isUsingNetworkInput()) {
            NetworkSession* session = getNetworkSession();
            int* deviceState = *(int**)(session + 0x50);
            if (deviceState == 0) {
                initializeNetworkSession();
            }
            // Check if input is not blocked and not paused
            if (((~(byte)(**(uint**)(session + 0x58) >> 0xf) & 1) == 0) &&
                !isInputBlocked()) {
                int* stateData = *(int**)(session + 0x50);
                // Store device state pointers
                *(int*)(this + 0x814) = *(int*)(stateData + 0x10);
                *(int*)(this + 0x818) = *(int*)(stateData + 0x14);
                // Get or create device buffer
                int* deviceBuffer = *(int**)(session + 0x4c);
                if (deviceBuffer == 0) {
                    deviceBuffer = (int*)allocMemory(0x4c, 0);
                    if (deviceBuffer != 0) {
                        deviceBuffer = createDeviceBuffer();
                    }
                }
                resetDeviceBuffer(deviceBuffer);
                int numDevices = *(int*)(stateData + 4);
                int maxDevices = numDevices;
                if (param_2 <= numDevices) {
                    maxDevices = param_2;
                }
                // Process each device
                for (int i = 0; i < numDevices; i++) {
                    int deviceData = DAT_0119cbbc; // default value
                    if (i < maxDevices) {
                        deviceData = getDeviceDataForIndex(i);
                    }
                    processDeviceInput(*(int*)(session + 0x58), 0,
                                       *(int*)(*(int*)(stateData + 8) + i * 4), deviceData, 0, 1);
                }
                // Process param_2 frames/devices
                for (int i = 0; i < param_2; i++) {
                    processOneDevice();
                }
                updateDeviceList(this);
                applyDeviceState(stateData + 0x18, *(int*)(session + 0x58), *(int*)(stateData + 0xc));
                notifyInputChange();
                cleanupDeviceBuffer();
                // Store updated state
                *(int*)(this + 0x814) = (int)stateData;
                *(int*)(this + 0x818) = maxDevices;
                return;
            }
            // If input blocked or paused, just process frames and finalize
            for (int i = 0; i < param_2; i++) {
                processOneDevice();
            }
            finalizeUpdate(this);
            return;
        }
    }
    // If this is null or no input system active, just process frames and finalize
    for (int i = 0; i < param_2; i++) {
        processOneDevice();
    }
    finalizeUpdate(this);
}