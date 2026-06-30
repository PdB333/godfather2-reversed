// FUNC_NAME: DeviceManager::configureDevice
void DeviceManager::configureDevice(void* device) {
    // Retrieve the singleton device manager instance
    void** vtable = (void**)FUN_009c8f80();
    // Build a command structure: { commandId = 2, subCommand = 0x10, flags = 0 }
    int cmdData[3];
    cmdData[0] = 2;         // command identifier
    cmdData[1] = 0x10;      // sub‑command or parameter
    cmdData[2] = 0;         // flags/reserved
    // Call the first virtual method on the manager (likely "processCommand")
    void (*processCmd)(void*, int*) = (void (*)(void*, int*))(*vtable)[0];
    processCmd(device, cmdData);
}