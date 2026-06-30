// FUNC_NAME: ControllerManager::initializeControllerSlots
void ControllerManager::initializeControllerSlots(ControllerManager* this, ControllerSlots* slotData) {
    // Local variables from stack reconstruction
    uint systemHash;
    uint slotId;
    uint registerFlag;
    void* instance;
    uint messageHandle;
    uint dataHandle;

    // Preliminary setup - register default system?
    initializeBaseSystem(); // FUN_006905a0
    
    // Get initial registration ID?
    registerFlag = getInitializationFlag(); // FUN_00691a70
    
    // Create an instance of something (maybe a class factory)
    instance = createInstance(0, &classFactory_0x690ce0); // FUN_0049a700
    // Call virtual function at vtable+4 (index 1) on this
    vtableDispatch(this, 1); // (**(code **)(*this + 4))()
    
    // Register system with a hash ID (0xebc77d43)
    registerSystem(0xebc77d43, slotData); // FUN_00690530
    
    // Get a singleton instance of class 0x???
    instance = getSingleton(0); // FUN_0049a640
    
    // Dispatch vtable+4 on this again with argument:
    vtableDispatch(this, 1); // (**(code **)(*this + 4))()
    
    // Log/debug call with hash and params
    debugLog(0x1d8e854d, this, 0xc); // FUN_00497960 (but args: hash, this, some int)
    
    // Branch based on a value (likely unaff_EDI, possibly a member or global)
    if (unaff_EDI == 4) {
        // Path for EDI=4
        registerSystem(0x62b07722, slotData); // FUN_00690530
        registerSystem(0xd177df7c, slotData);
        registerSystem(0x54a314df, slotData);
    } else {
        // Other path
        registerSystem(0x3ddc7637, slotData);
        registerSystem(0x2938c6cc, slotData);
        // Release/reference counting on this and slotData
        releaseObject(this, 0xebc77d43, 0xed41087b); // FUN_004979c0
        if (slotData != nullptr) {
            releaseObject(slotData, 0xebc77d43, 0xed41087b);
        }
        // Create another instance
        instance = createInstance(0, &classFactory_0x690ce0); // FUN_0049a700
        // Dispatch vtable+4 with argument 0x20
        vtableDispatch(this, 1, 0x20);
        // Log
        debugLog(0xed41087b, this, 0x20);
        // Initialize something with hash and size?
        initializeSystem(0xed41087b, 0x10); // FUN_006903d0
    }
    
    // Common path: create default slot data
    instance = createInstance(0, &classFactory_0x690d60); // FUN_0049a700
    vtableDispatch(this, 1, 0x16);
    debugLog(0x6ef11ea8, this, 0x16);
    
    if (slotData != nullptr) {
        // Create a message, serialize it, and dispatch on slotData
        messageHandle = createMessage(); // FUN_00496470
        serializeMessage(&messageHandle, &messageSchema_0x690e00, 1); // FUN_00496780
        // Virtual call on slotData: vtable+4, argument 0x11
        vtableDispatch(slotData, 1, 0x11, messageHandle);
        debugLog(0x6ef11ea8, slotData, 0x11);
    }
    
    // Setup another slot
    instance = createInstance(0, &classFactory_0x690d60, 2, 3); // FUN_0049a700 (with extra args)
    vtableDispatch(this, 1, 0x17, instance);
    debugLog(0xbe16155b, this, 0x17);
    
    if (slotData != nullptr) {
        messageHandle = createMessage();
        serializeMessage(&messageHandle, &messageSchema_0x690e00, 2);
        vtableDispatch(slotData, 1, 0x12, messageHandle);
        debugLog(0xbe16155b, slotData, 0x12);
    }
    
    // Retrieve two types of data from a global manager and pass to slotData
    uint deviceManagerPtr = (uint)globals.deviceManager; // _DAT_00d5c968
    int device0 = getDeviceByIndex(deviceManagerPtr, 0); // FUN_00496830
    vtableDispatch(slotData, 6, 2, device0); // vtable+0x18 (index 6)
    
    int device1 = getDeviceByType(deviceManagerPtr, 0); // FUN_00496880
    vtableDispatch(slotData, 6, 3, device1);
    
    return;
}